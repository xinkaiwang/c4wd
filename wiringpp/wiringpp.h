#pragma once

#include <utility>

namespace wiringpp {

template <class T, class TAG> class AliasTo final {
public:
  explicit AliasTo(T value) : value_(std::move(value)) {}
  T &ToBaseType() { return value_; }
  const T &ToBaseType() const { return value_; }

private:
  T value_;
};

#define WpCreateAlias(X, T)                                                    \
  struct X##Tag {};                                                            \
  using X = wiringpp::AliasTo<T, X##Tag>

class WpPin;
class BcmPin;
class PhysPin;

bool InitWiringPi();

class WpPin {
public:
  explicit WpPin(int value);

  //   static const bool initated = InitWiringPi();
  int GetWpPin() const;

private:
  int value_;
};

// no need sudo
class PinOut {
public:
  explicit PinOut(const WpPin &pin);

  PinOut(const PinOut &other) = delete;
  PinOut(PinOut &&other) = delete;
  PinOut &operator=(const PinOut &) = delete;
  PinOut &operator=(PinOut &&) = delete;

public:
  void SetValue(bool value);
  bool GetValue() const;
  bool Toggle();

private:
  const WpPin pin_;
  bool value_;
};

enum class PullMode { PULL_OFF = 0, PULL_DOWN = 1, PULL_UP = 2 };

// no need sudo
class PinIn {
public:
  explicit PinIn(const WpPin &pin);
  PinIn(const WpPin &pin, PullMode pullMode);

  PinIn(const PinIn &other) = delete;
  PinIn(PinIn &&other) = delete;
  PinIn &operator=(const PinIn &) = delete;
  PinIn &operator=(PinIn &&) = delete;

public:
  bool GetValue() const;

private:
  const WpPin pin_;
};

// (require sudo)
// On Raspberry Pi, only WpPin 1 supports hardware PWM (BMC_GPIO 18, Phys 12)
class PwmOut {
public:
  explicit PwmOut(const WpPin &pin);

  // range from [0.0f, 1.0f]
  void SetValue(float val);

private:
  const WpPin pin_;
};

// On Raspberry Pi, only WpPin 7 supports hardware PWM (BMC_GPIO 4, Phys 7)
class ClockOut {
public:
  explicit ClockOut(const WpPin &pin);

  // range from [4.7k, 19.2M] (Hz)
  void SetFrequency(int frq);

private:
  const WpPin pin_;
};

enum class InterruptLevel {
  INT_EDGE_SETUP = 0,
  INT_EDGE_FALLING = 1,
  INT_EDGE_RISING = 2,
  INT_EDGE_BOTH = 3
};

// This is a wrapper for wiringPi wiringPiISR()
// wiringPiISR() is using sys mode 'gpio', so it's kind of slow, but it does not
// require root.
class Interrupt {
  Interrupt(const WpPin &pin, const InterruptLevel interruptLevel);

private:
  const WpPin pin_;
};

} // namespace wiringpp