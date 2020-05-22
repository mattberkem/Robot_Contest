
#ifndef ROBOT_CONTEST_SIMULATOR_H
#define ROBOT_CONTEST_SIMULATOR_H

#include "HardwareSimulator.h"
#include "UserInterface.h"
#include "RobotController.h"

class RobotContestSimulator {

 public:
  RobotContestSimulator();
  ~RobotContestSimulator();
  void runSimulation();
  void setUpTeams();
  void setContestPlayers( int, int );

 private:
  HardwareSimulator theHardwareSimulator;
  UserInterface theUserInterface;
  RobotController * pursuingRobotControllerPtr;
  RobotController * evadingRobotControllerPtr;

};

#endif // ROBOT_CONTEST_SIMULATOR_H
