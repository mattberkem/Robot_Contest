
#include <cassert>

#include "MulhollandRobotController.h"

MulhollandRobotController::MulhollandRobotController( HardwareSimulator &
						      hardwareSimulatorDesired,
						      int typeDesired )
  : RobotController( hardwareSimulatorDesired, typeDesired )
{
	sleep = 0;
	loopCount = 0;
	hasTurned = true;
}

void MulhollandRobotController::runControlLoop()
{
  assert( type == HardwareSimulator::PURSUING ||
	  type == HardwareSimulator::EVADING );

  if ( type == HardwareSimulator::PURSUING ) {
	if (sleep != 0)
		sleep -= .1;
	else
	{
		//persuing algorithm - Josh Leavitt
		if(rightTouchSensor.detect() && leftTouchSensor.detect())
		{
			//Both hit so backup.
			rightMotor.setVoltage(-9);
			leftMotor.setVoltage(-9);
			sleep = .1;
		}
		else if(rightTouchSensor.detect())
		{
			rightMotor.setVoltage(-8);
			leftMotor.setVoltage(-4);
			sleep = .1;
		}
		else if(leftTouchSensor.detect())
		{
			rightMotor.setVoltage(-4);
			leftMotor.setVoltage(-8);
		}
			//Look for other robot
		if(!theBeaconSensor.detect())
		{
			//Every 1 seconds make a forward turn.
			if((loopCount % 10) == 0 )
			{
				leftMotor.setVoltage(8);
				rightMotor.setVoltage(3);
				sleep = .1;
			}
			//If not detected turn right
			else
			{
				leftMotor.setVoltage(5);
				rightMotor.setVoltage(-5);
			}
		}
		else
		{	
			//If detected, full speed ahead
			rightMotor.setVoltage(9);
			leftMotor.setVoltage(9);
		}
	}
  }
  else { // type == EVADING
	//evading algorithm - Broc Going
	int spinVoltage = 5;		//voltage used for spinning (+,-)
	int forwardVoltage = 5;		//voltage used for forward motion
	int backSlowVoltage = -3;	//voltage used for slow side when backing
	int backFastVoltage = -6;	//voltage used for fast side when backing
	double spinTime = .1;		//sleep time for spin
	double backTime = .1;		//sleep time for backing up
	double forwardTime = .5;	//sleep time for going forward

	if (sleep != 0)	//if in sleep mode
		sleep -= .1;
	else			//if not in sleep mode
	{
		//reaction if beacon is detected
		if (theBeaconSensor.detect() || !hasTurned)	//spin for .1 sec
		{
			if (loopCount%2 == 0)	//if on even time through, spin right
			{
				leftMotor.setVoltage(spinVoltage);
				rightMotor.setVoltage(-spinVoltage);
			}
			else				//if on odd time through, spin left
			{
				leftMotor.setVoltage(-spinVoltage);
				rightMotor.setVoltage(spinVoltage);
			}
			hasTurned = true;	//record turn
			sleep = spinTime;
		}
		//reaction if left touch sensor or both touch sensors activated
		else if (leftTouchSensor.detect())	//back and turn left
		{
			leftMotor.setVoltage(backSlowVoltage);
			rightMotor.setVoltage(backFastVoltage);
			sleep = backTime;
		}
		//reaction if just right touch sensor activated
		else if (rightTouchSensor.detect())	//back and turn right
		{
			leftMotor.setVoltage(backFastVoltage);
			rightMotor.setVoltage(backSlowVoltage);
			sleep=backTime;
		}
		//action if no sensor triggered and turned last time through
		else
		{
			leftMotor.setVoltage(forwardVoltage);
			rightMotor.setVoltage(forwardVoltage);
			hasTurned = false;	//record forward motion
			sleep=forwardTime;
		}
	}
  }
  loopCount++;
}
