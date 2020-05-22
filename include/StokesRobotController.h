// Modified by Scott Stokes, Adam Jones, and Jason Schenk

#ifndef STOKES_ROBOT_CONTROLLER_H
#define STOKES_ROBOT_CONTROLLER_H

#include "RobotController.h"

class StokesRobotController : public RobotController {
 public:
  StokesRobotController( HardwareSimulator &, int );
  virtual void runControlLoop();

 private:
  // These data members added by our Team
  int chaseCount;
  int backCount;
  int lTurnCount;
  int rTurnCount;

};


#endif // STOKES_ROBOT_CONTROLLER_H
