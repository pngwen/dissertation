#include <iostream>
#include "motor.h"

using namespace std;

int main()

{
  const double INCR=.001;
  Motor m;

  m.setLoad(0);
  m.setVoltage(24);

  cout << "t\t" << "current\t" << "velocity\t" << "angle" << endl;
  for(double t=0; t<=0.5; t+=INCR) {
    cout << t << "\t"
         << m.getCurrent() << "\t"
         << m.getVelocity() << "\t"
         << m.getAngle() << endl;
    m.run(INCR);
  }

  //Withdraw voltage and coast for 10 seconds
  m.setVoltage(0);
  for(double t=0.5; t<=1.0; t+=INCR) {
    cout << t << "\t"
         << m.getCurrent() << "\t"
         << m.getVelocity() << "\t"
         << m.getAngle() << endl;
    m.run(INCR);
  }
  return 0;
}
