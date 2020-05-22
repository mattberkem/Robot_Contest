
#include <cmath>
#include "Vector.h"
#include "HWBeaconSensor.h"

#define M_PI		3.14159265358979323846

HWBeaconSensor::HWBeaconSensor( Robot & sensingRobotDesired,
				Robot & emittingRobotDesired )
  : sensingRobot( sensingRobotDesired ),
    emittingRobot( emittingRobotDesired )
{
}

HWBeaconSensor::~HWBeaconSensor()
{
}

bool HWBeaconSensor::detect() const
{
  Vector sensingRobotState( sensingRobot.numStates );
  Vector emittingRobotState( emittingRobot.numStates );
  double angle;

  sensingRobotState = sensingRobot.getState();
  emittingRobotState = emittingRobot.getState();

  angle = acos(
	       ( ( emittingRobotState(1) - sensingRobotState(1) ) *
		 cos( sensingRobotState(3) ) +
		 ( emittingRobotState(2) - sensingRobotState(2) ) *
		 sin( sensingRobotState(3) ) ) /
	       sqrt( ( emittingRobotState(1) - sensingRobotState(1) ) *
		     ( emittingRobotState(1) - sensingRobotState(1) ) +
		     ( emittingRobotState(2) - sensingRobotState(2) ) *
		     ( emittingRobotState(2) - sensingRobotState(2) ) )
	       );

  return (angle < 15.0*M_PI/180.0);
    
}

unsigned char HWBeaconSensor::getInputPortValue() const
{
  if ( detect() )
    return 1;
  else
    return 0;
}
