/* 
 * A C++ port of the ninja chaising particle filter example.
 */
#include <functional>
#include <random>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct particle {
  double v;
  double u;
  double z;
  double w;
};

int main() {
  double x = 0.1;  //initial actual state
  double x_N = 1;  //noise covariance in the system
  double x_R = 1;  //noise covariance in the measurement
  int t = 75;      //duration of the chase (iterations)
  int n = 10;      //the number of particles
  double v = 2;    //the variance of the initial estimate
  double z;	   //observation
  auto randn = bind(normal_distribution<double>, default_random_engine);
  auto randd = bind(uniform_real_distribution<double>{0.0, 1.0}, default_random_engine{});
  vector<particle> x_P(n);

  //make random guess for each particle
  for(int i=0; i< n; i++) {
    x_P[i].v = x + sqrt(v) * randn();
  }

  //run the simulation this many times
  for(t; t; t--) {
    x = 0.5 * x + 25.0 * x / (1+x*x) + 8 * cos(1.2 * (t-1))
        + sqrt(x_N) * randn();
    z = (x*x) / 20.0 + sqrt(x_R) * randn();


    //do the particle filter
    for(auto itr = x_P.begin(); itr!=x_P.end(); itr++) {
      itr->u = 0.5 * itr->v + itr->v/(1+itr->v * itr->v)
               + 8 * cos(1.2 *(t-1)) + sqrt(itr->v) * randn();
      itr->z = itr->u * itr->u / 20.0;
      itr->w = (1.0/sqrt(2.0 * M_PI * x_R)) * exp(-((z - itr->z)
             * (z-itr->z) / (2 * x_R)));
    }
  }

  return 0;
}
