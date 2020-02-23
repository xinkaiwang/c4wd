#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <wiringpp.h>

using namespace wiringpp;

int main(void) {
  //   PinOut out(WpPin(6));
  //   PinIn in(WpPin(5), PullMode::PULL_DOWN);
  //   for (;;) {
  //     out.SetValue(true);
  //     std::cout << "pin5="<< in.GetValue() << "\n";
  //     std::this_thread::sleep_for(std::chrono::milliseconds(500));
  //     out.SetValue(false);
  //     std::cout << "pin5="<< in.GetValue() << "\n";
  //     std::this_thread::sleep_for(std::chrono::milliseconds(500));
  //   }

  //   PinOut out(WpPin(6));
  //   for (;;) {
  //     out.Toggle();
  //     std::this_thread::sleep_for(std::chrono::milliseconds(500));
  //   }

  //   // need sudo
  //   PwmOut pwm(WpPin(1));
  //   float val = 0.0f;
  //   for (;;) {
  //     val += 0.1f;
  //     if (val > 1.0) {
  //       val = 0.0;
  //     }
  //     pwm.SetValue(val);
  //     std::this_thread::sleep_for(std::chrono::milliseconds(100));
  //   }

  std::cout << "step1\n";
  ClockOut clock(WpPin(7));

  std::cout << "step2\n";
  clock.SetFrequency(10000);
  std::cout << "step3\n";

  for (;;) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  std::cout << "step4\n";

  std::vector<int> buf(100);
  int *head = &buf[0];
  auto p = __sync_fetch_and_add(&head, 1);

  return 0;
}
