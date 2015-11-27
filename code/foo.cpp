#include <functional>
#include <random>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

using namespace std;

int main() {
  default_random_engine e;
  char *seed;
  int s;

  seed = getenv("SEED");
  if(seed) {
    istringstream(seed) >> s; 
    e.seed(s);
  } else {
    e.seed(12);
  }

  auto gen = bind(uniform_real_distribution<double>{0.0, 1.0}, default_random_engine{});

  for(int i=0; i<5; ++i) cout << gen() << endl;
}
