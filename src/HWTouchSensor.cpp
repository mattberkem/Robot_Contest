#include <cmath>

#include "HWTouchSensor.h"

HWTouchSensor::HWTouchSensor( Robot & sensingRobotDesired,
			      Robot & otherRobotDesired,
			      PlayingField & field,
			      double forwardOffsetDesired,
			      double rightOffsetDesired )
  : sensingRobot( sensingRobotDesired ),
    otherRobot( otherRobotDesired ),
    walls( field )
{
  // don't allow the sensor to be behind the robot
  if ( forwardOffsetDesired > 0.0 )
    forwardOffset = forwardOffsetDesired;
  else
    forwardOffset = -forwardOffsetDesired;

    rightOffset = rightOffsetDesired;
}

HWTouchSensor::~HWTouchSensor()
{
}

bool HWTouchSensor::detect() const
{
  Vector sensingRobotState( sensingRobot.numStates );
  Vector otherRobotState( otherRobot.numStates );
  Vector touchLocation( 2 );

  sensingRobotState = sensingRobot.getState();
  otherRobotState = otherRobot.getState();

  touchLocation(1) = sensingRobotState( 1 ) +
    forwardOffset * cos( sensingRobotState( 3 ) ) +
    rightOffset * sin( sensingRobotState( 3 ) );

  touchLocation(2) = sensingRobotState( 2 ) +
    forwardOffset * sin( sensingRobotState( 3 ) ) -
    rightOffset * cos( sensingRobotState( 3 ) );

  return ( detectWall( touchLocation )                   ||
	   detectRobot( touchLocation, otherRobotState )    );

}

bool HWTouchSensor::detectWall( Vector & touchPosition ) const
{
  return ( touchPosition( 2 ) < walls.getBottomWallLocation() ||
	   touchPosition( 2 ) > walls.getTopWallLocation()    ||
	   touchPosition( 1 ) < walls.getLeftWallLocation()   ||
	   touchPosition( 1 ) > walls.getRightWallLocation()     );
}

bool HWTouchSensor::detectRobot( Vector & touchPosition,
			       Vector & otherRobotState ) const
{
  return ( sqrt( ( otherRobotState( 1 ) - touchPosition( 1 ) ) *
		 ( otherRobotState( 1 ) - touchPosition( 1 ) ) +
		 ( otherRobotState( 2 ) - touchPosition( 2 ) ) *
		 ( otherRobotState( 2 ) - touchPosition( 2 ) ) )
	   < otherRobot.getRadius() );

}

unsigned char HWTouchSensor::getInputPortValue() const
{
  if ( detect() )
    return 1;
  else
    return 0;
}
