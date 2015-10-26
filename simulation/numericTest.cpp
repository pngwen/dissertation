#include <iostream>
#include "numeric.h"

using namespace std;

int main()

{
  const double INCR=0.1;
  double y, dy;

  y=dy=0;
  for(double t=0; t<10; t+=INCR) {
    cout << t << "\t" << y<< endl;
    dy = integrate([](double t)->double{return 2.0;}, 0, INCR, 100);
    y+=dy;
  }

  return 0;
}
