
#ifndef DOUGLAS_ROBOT_CONTROLLER_H
#define DOUGLAS_ROBOT_CONTROLLER_H

#include "RobotController.h"

class DouglasRobotController : public RobotController {
 public:
  DouglasRobotController( HardwareSimulator &, int );
  virtual void runControlLoop();

 private:

  //the following variable are for the 
	//psuedo-random number generator
  long double c;
	unsigned long s;
	double x[5];
  int rnd1, rnd2;

	//captures the voltages from random variables
	double left, right;
	//time when new movement should be initialized
	double time;
	//switches on for 0.5 seconds when touch sensors
	//detect a wall or another robot
	bool touched;

	int i; // added this since you use it in constructor and in control loop


};


#endif // DOUGLAS_ROBOT_CONTROLLER_H
