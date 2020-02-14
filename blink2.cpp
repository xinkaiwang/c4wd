#include <iostream>
#include <chrono>
#include <thread>
#include <wiringpp.h>

using namespace wiringpp;

int main(void) {
  PinOut out(WpPin(6));
  PinIn in(WpPin(5), PullMode::PULL_DOWN);

  for (;;) {
    out.SetValue(true);
    std::cout << "pin5="<< in.GetValue() << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    out.SetValue(false);
    std::cout << "pin5="<< in.GetValue() << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  return 0;
}
