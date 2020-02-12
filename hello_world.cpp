#include <algorithm>
#include <iostream>
#include <vector>

#include "app_config.h"
#include <math.h>

#ifdef USE_MYMATH
#include "MathFunctions.h"
#endif

int main(int argc, char **argv) {
  std::cout << "hello world " << C4wd_VERSION_MAJOR << "." << C4wd_VERSION_MINOR
            << "\n";
  if (argc < 2) {
    // report version
    std::cout << argv[0] << " Version " << C4wd_VERSION_MAJOR << "."
              << C4wd_VERSION_MINOR << std::endl;
    std::cout << "Usage: " << argv[0] << " number" << std::endl;
    return 1;
  }
  const double inputValue = std::stod(argv[1]);

#ifdef USE_MYMATH
  const double out = xk::squart(inputValue);
#else
  const double out = sqrt(inputValue);
#endif

  std::cout << "inputValue=" << inputValue << ", squart=" << out << "\n";
  std::vector<int> arr1 = {4, 5, 8, 3, 1};
  std::vector<int> arr2;
  auto x2 = [&arr2](auto n) { arr2.push_back(n * 2); };
  std::for_each(arr1.begin(), arr1.end(), x2);
  std::for_each(arr2.begin(), arr2.end(),
                [](int n) { std::cout << n << "\n"; });
}
