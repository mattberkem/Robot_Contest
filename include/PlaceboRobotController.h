
#ifndef PLACEBO_ROBOT_CONTROLLER_H
#define PLACEBO_ROBOT_CONTROLLER_H

#include "RobotController.h"

class PlaceboRobotController : public RobotController {
 public:
  PlaceboRobotController( HardwareSimulator &, int );
  virtual void runControlLoop();

};


#endif // PLACEBO_ROBOT_CONTROLLER_H
