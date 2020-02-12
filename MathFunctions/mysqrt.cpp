#include "MathFunctions.h"

namespace xk {

double squart(double Y) {
  double x = 1;
  for (int i = 0; i < 10; i++) {
    x = x + (Y - x * x) / (2 * x);
  }
  return x;
}

} // namespace xk
