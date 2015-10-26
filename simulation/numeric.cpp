#include "numeric.h"

double
integrate(std::function<double (double)> f, double a, double b, int n) {
  double result = 0;

  // compute the sum of the segments
  for(int k = 1; k<n; k++) {
    result += f(a + k*((b-a)/n));
  }

  //compute the rest of the result
  result += (f(b) + f(a))/2.0;
  result *= (b-a) / n;

  return result;
}
