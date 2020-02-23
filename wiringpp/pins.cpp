#include "wiringpp.h"

#include <iostream>
#include <wiringPi.h>

namespace wiringpp {

bool InitWiringPi() {
  wiringPiSetup();
  std::cout << "InitWiringPi()\n";
  return true;
}

// struct TAG {};
// using WIP = wiringpipp::AliasTo<int, TAG>;

// ******************* WpPin ***********************
WpPin::WpPin(int val) : value_{val} {
  // Hack: this is the simple trick to make sure wiringPiSetup() always get
  // called before everything.
  static int inited = InitWiringPi();
}
int WpPin::GetWpPin() const { return value_; }

// ******************* PinOut ***********************
// explicit
PinOut::PinOut(const WpPin &pin) : pin_{pin} {
  pinMode(pin_.GetWpPin(), OUTPUT);
  value_ = digitalRead(pin_.GetWpPin());
}

void PinOut::SetValue(bool value) {
  digitalWrite(pin_.GetWpPin(), value ? HIGH : LOW);
  value_ = value;
}

bool PinOut::GetValue() const { return value_; }

bool PinOut::Toggle() {
  bool newValue = !value_;
  digitalWrite(pin_.GetWpPin(), newValue ? HIGH : LOW);
  value_ = newValue;
  return newValue;
}

// ******************* PinIn ***********************
// explicit
PinIn::PinIn(const WpPin &pin) : pin_{pin} { pinMode(pin_.GetWpPin(), INPUT); }

PinIn::PinIn(const WpPin &pin, PullMode pullMode) : pin_{pin} {
  pinMode(pin_.GetWpPin(), INPUT);
  pullUpDnControl(pin_.GetWpPin(), static_cast<int>(pullMode));
}

bool PinIn::GetValue() const { return digitalRead(pin_.GetWpPin()); }

// ******************* PwmOut ***********************
PwmOut::PwmOut(const WpPin &pin) : pin_{pin} {
  if (pin.GetWpPin() != 1) {
    throw std::runtime_error("Only pin1 supports PWM out");
  }
  pinMode(pin_.GetWpPin(), PWM_OUTPUT);
}

void PwmOut::SetValue(float val) {
  val = val >= 1.0 ? 1.0 : val;
  val = val <= 0 ? 0 : val;
  int outVal = static_cast<int>(1024 * val);
  pwmWrite(pin_.GetWpPin(), outVal);
}

// ******************* ClockOut ***********************
ClockOut::ClockOut(const WpPin &pin) : pin_{pin} {
  if (pin.GetWpPin() != 7) {
    throw std::runtime_error("Only pin7 supports CLOCK");
  }
  pinMode(pin_.GetWpPin(), GPIO_CLOCK);
}

void ClockOut::SetFrequency(int feq) {
  // range from [4.7k, 19.2M] (Hz)
  gpioClockSet(pin_.GetWpPin(), feq);
}

} // namespace wiringpp