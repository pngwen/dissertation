/* Implementation of the motor simulation class.
 * Author: Robert Lowe
 */
#include "numeric.h"
#include "motor.h"

//updates the simulation when running from the present state for t seconds
void
Motor::run(double t) {
  double di;
  double dw;
  double da;
  double dt;
  double totalTime;

  //limit dt to at most 0.001, otherwise the motors act crazy
  if(t <= 0.001) {
    dt = t; 
  } else {
    dt = 0.001;
  }

  //iterate over the simulation time frame at .001 second intervals
  for(totalTime=0; totalTime <t; totalTime+=dt) {
    //Limit things so we don't over extend our time
    if(totalTime+dt > t) {
      dt = t-totalTime;
    }

    //compute the deltas
    di=integrate(
        [this] (double t) -> double { return (vs - r*is - km *w) / l; },
        totalTime, totalTime+dt, 100);
    dw=integrate(
        [this] (double t) -> double { return -f/j * w + km/j*is - 1.0/j * ml; },
        totalTime, totalTime+dt, 100);
    da=integrate([this](double t) -> double { return w; }, totalTime, totalTime+dt, 100);

    //update the values
    is += di;
    w += dw;
    a += da;
  }
}
