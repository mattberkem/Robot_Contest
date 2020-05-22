/*
Omar Morales
Kurt Neiderhauser
Jason Havey
Andrew Fager
Jason McKellar
*/


#include <cassert>
#include "MoralesRobotController.h"

MoralesRobotController::MoralesRobotController( HardwareSimulator &
						hardwareSimulatorDesired,
						int typeDesired )
  : RobotController( hardwareSimulatorDesired, typeDesired )
{
	state = 0;
	sleeper = 0;
}


void MoralesRobotController::runControlLoop()
{
  assert( type == HardwareSimulator::PURSUING ||
	  type == HardwareSimulator::EVADING );
 if(sleeper==0)
 {
  if ( type == HardwareSimulator::PURSUING )
  {

		if(state==0)
		{
			leftMotor.setVoltage( .8 );
			rightMotor.setVoltage( -.8 );
			state=1;
		}
	    if(state==1)
		{
			leftMotor.setVoltage( 9.5 );
			rightMotor.setVoltage( 7.5 );
			//			sleep=5;
			sleeper=5;
			state=2;
		}
		if(state==2)
		{
			if ( theBeaconSensor.detect() )
			{
				leftMotor.setVoltage( 9.5 );
				rightMotor.setVoltage( 7.5 );
			}
			else	//search -- if we cant see them, turn
			{		//if we are hitting a wall, we can't see them
				leftMotor.setVoltage( 9.5 );
				rightMotor.setVoltage( 3 );
			}
		}
  }
  else
  {
		if(state==0)
		{
			leftMotor.setVoltage( .8 );
			rightMotor.setVoltage( -.8 );
			state=1;
		}
	    if(state==1)
		{
			leftMotor.setVoltage( 9.5 );
			rightMotor.setVoltage( 7.5 );
			//			sleep=5;
			sleeper=5;
			state=2;
		}
		if(state==2)
		{
			if ( theBeaconSensor.detect() )
			{
				leftMotor.setVoltage( 9.5 );
				rightMotor.setVoltage( 7.5 );
			}
			else	//search -- if we can see them, turn
			{		//if we are hitting a wall, we'll slowly turn
				leftMotor.setVoltage( 3 );
				rightMotor.setVoltage( 9.5 );
			}
		}
	}

  }
  else sleeper--;

}

