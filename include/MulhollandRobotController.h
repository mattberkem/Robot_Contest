
#ifndef MULHOLLAND_ROBOT_CONTROLLER_H
#define MULHOLLAND_ROBOT_CONTROLLER_H

#include "RobotController.h"

class MulhollandRobotController : public RobotController {
 public:
  MulhollandRobotController( HardwareSimulator &, int );
  virtual void runControlLoop();

 private:
  double sleep;
  bool hasTurned;
  int loopCount;

};


#endif // MULHOLLAND_ROBOT_CONTROLLER_H
