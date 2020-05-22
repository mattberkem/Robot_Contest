
#ifndef MOTOR_H
#define MOTOR_H

#include "HardwareSimulator.h"

class Motor {

 public:
  Motor( HardwareSimulator &, int, int );
  ~Motor();
  void setVoltage( double );

 private:
  HardwareSimulator & theHardwareSimulator;
  int type;
  int side;

};

#endif // MOTOR_H
