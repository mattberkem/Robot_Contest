/*
Omar Morales
Kurt Neiderhauser
Jason Havey
Andrew Fager
Jason McKellar
*/


#ifndef MORALES_ROBOT_CONTROLLER_H
#define MORALES_ROBOT_CONTROLLER_H

#include "RobotController.h"


class MoralesRobotController : public RobotController {
 public:
  MoralesRobotController( HardwareSimulator &, int );
  virtual void runControlLoop();

 private:
  int state;
  int sleeper;

};


#endif // MORALES_ROBOT_CONTROLLER_H
