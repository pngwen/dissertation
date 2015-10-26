#include <iostream>
#include "motor.h"

using namespace std;

int main()

{
  const double INCR=.00001;
  Motor m;

  m.setLoad(0);
  m.setVoltage(12);

  for(double t=0; t<10; t+=INCR) {
    cout << t << "\t"
         << m.getCurrent() << "\t"
         << m.getVelocity() << "\t"
         << m.getAngle() << endl;
    m.run(INCR);
  }

  return 0;
}
