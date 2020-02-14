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
PinOut::PinOut(WpPin pin) : pin_{pin} {
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
PinIn::PinIn(WpPin pin) : pin_{pin} { pinMode(pin_.GetWpPin(), INPUT); }

PinIn::PinIn(WpPin pin, PullMode pullMode) : pin_{pin} {
  pinMode(pin_.GetWpPin(), INPUT);
  pullUpDnControl(pin_.GetWpPin(), static_cast<int>(pullMode));
}

bool PinIn::GetValue() const { return digitalRead(pin_.GetWpPin()); }

} // namespace wiringpp