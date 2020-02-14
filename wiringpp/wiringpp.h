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
class Pin;

bool InitWiringPi();

class WpPin {
public:
  explicit WpPin(int value);

  //   static const bool initated = InitWiringPi();
  int GetWpPin() const;

private:
  int value_;
};

class PinOut {
public:
  explicit PinOut(WpPin pin);

  PinOut(const PinOut &other) = delete;
  PinOut(PinOut &&other) = delete;
  PinOut &operator=(const PinOut &) = delete;
  PinOut &operator=(PinOut &&) = delete;

public:
  void SetValue(bool value);
  bool GetValue() const;
  bool Toggle();

private:
  WpPin pin_;
  bool value_;
};

enum class PullMode { PULL_OFF = 0, PULL_DOWN = 1, PULL_UP = 2 };

class PinIn {
public:
  explicit PinIn(WpPin pin);
  PinIn(WpPin pin, PullMode pullMode);

  PinIn(const PinIn &other) = delete;
  PinIn(PinIn &&other) = delete;
  PinIn &operator=(const PinIn &) = delete;
  PinIn &operator=(PinIn &&) = delete;

public:
  bool GetValue() const;

private:
  WpPin pin_;
};

} // namespace wiringpp