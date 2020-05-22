
#ifndef ROBOT_CONTROLLER_H
#define ROBOT_CONTROLLER_H

#include "HardwareSimulator.h"
#include "TouchSensor.h"
#include "BeaconSensor.h"
#include "Motor.h"
#include "Clock.h"

class RobotController {
 public:
  RobotController( HardwareSimulator &, int );
  virtual void runControlLoop() = 0;

 protected:
  int type;
  TouchSensor leftTouchSensor;
  TouchSensor rightTouchSensor;
  BeaconSensor theBeaconSensor;
  Motor leftMotor;
  Motor rightMotor;
  Clock theClock;

};

#endif // ROBOT_CONTROLLER_H
