/* File: motor.h
 * Purpose: Class definition for a simulation of a dc motor.
 *          The simulation is based on Kirchhoff's law and assuming constant flux.
 *           The model input parameters are:
 *             F - Motor Friction ((N*M)/(Rad*S)
 *             R - Motor Resistance (Ohms)
 *             L - Motor Inductance (H)
 *             KM - Motor constant (NM/A)
 *             J - Total motor inertia. (KgM^2)
 *           These parameters are all in SI units.  These are intended to remain
 *           constant, but can be altered to simulate differences in motor operation
 *           characteristics.
 *
 *           The intended control parameters are:
 *             vs - Supply Voltage
 *             ml - Load Torque
 *           These variables are used to compute the following output parameters:
 *             a - shaft angle in radians
 *             w - shaft angular velocity
 *             i - motor current draw.
 * Author: Robert Lowe rlowe8@utk.edu
 */
#ifndef MOTOR_H
#define MOTOR_H
#include "numeric.h"

class Motor
{
public:
  Motor(double f=0.005, 
        double r=7,
        double l=0.02,
        double km=0.05,
        double j=.0001):f(f), r(r), l(l), km(km), j(j), vs(0), ml(0), w(0), a(0), is(0) {}

  //Model Parameters
  void setFriction(double f) {this->f = f;}
  double getFriction() { return f; }
  void setResistance(double r) { this->r = r; }
  double getResistance() { return r; }
  void setInductance(double l) { this->l = l; }
  double getInductance() { return l; }
  void setKM(double km) { this->km = km; }
  double getKM() { return km; }
  void setInertia(double j) { this->j = j; }
  double getInertia() { return j; }

  //control parameters
  void setVoltage(double vs) { this->vs = vs; }
  double getVoltage() { return vs; }
  void setLoad(double ml) { this->ml = ml; }
  double getLoad() { return ml; }

  //output parameters
  double getCurrent() { return is; }
  double getVelocity() { return w; }
  double getAngle() { return a; }
  
  //simulation functions
  
  //run for t seconds
  void run(double t);

private:
  double f;        //Motor Friction
  double r;        //Motor Resistance
  double l;        //Motor inductance
  double km;       //Motor constant
  double j;        //Motor's total moment of inertia
  double vs;       //The supply voltage
  double ml;       //The motor's load torque
  double w;        //angular velocity of the shaft
  double a;        //Current shaft displacement
  double is;       //The current drawn by the motor
};

#endif
