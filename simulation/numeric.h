#ifndef NUMERIC_H
#define NUMERIC_H
#include <functional>
/*
 * Computes the numeric integral over the interval (a,b) 
 * of function f using n subdivisions.
 * The integral is computed using the quadrature method.
 */
double integrate(std::function<double (double)> f, double a, double b, int n);
#endif
