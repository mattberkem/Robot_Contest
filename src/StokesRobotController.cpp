
#include <cassert>
#include "StokesRobotController.h"

StokesRobotController::StokesRobotController( HardwareSimulator &
					      hardwareSimulatorDesired,
					      int typeDesired )
  : RobotController( hardwareSimulatorDesired, typeDesired )
{
  chaseCount = backCount = lTurnCount = rTurnCount = 0;
}

void StokesRobotController::runControlLoop()
{
  assert( type == HardwareSimulator::PURSUING ||
          type == HardwareSimulator::EVADING );

	// Our algorithm for checking sensors
	if ( leftTouchSensor.detect() ) {
		backCount = 5;
		rTurnCount = 5;
	} else if ( rightTouchSensor.detect() ) {
		backCount = 5;
		lTurnCount = 5;
	}

	if ( type == HardwareSimulator::PURSUING &&
	     theBeaconSensor.detect() == true ) {
		backCount = lTurnCount = rTurnCount = 0;
		chaseCount = 3;
	}

  if ( type == HardwareSimulator::PURSUING ) {

    // If beacon is detected, drive forward, otherwise, rotate
    if ( theBeaconSensor.detect() ) {
      leftMotor.setVoltage(9.525);
      rightMotor.setVoltage(9.525);
    }
    else {
      if ( chaseCount == 0 ) {
	leftMotor.setVoltage(2.25);
	rightMotor.setVoltage(0);
      } else {
	leftMotor.setVoltage(9.525);
	rightMotor.setVoltage(9.525);
	chaseCount--;
      }
    }
        
  }
  else { // type == EVADING
    // drive forward for 0.5 seconds, turn for 0.5 seconds, and repeat
    if ( theBeaconSensor.detect() ) {
      leftMotor.setVoltage( 0 );
      rightMotor.setVoltage( -9.525 );
    }
    else if ( backCount ) { // Go backward
      leftMotor.setVoltage(-4.95);
      rightMotor.setVoltage(-4.95);
      backCount--;
    } else if ( lTurnCount ) { // Turn left
      leftMotor.setVoltage(-0.975);
      rightMotor.setVoltage(0.975);
      lTurnCount--;
    } else if ( rTurnCount ) { // Turn right
      leftMotor.setVoltage(0.975);
      //      itsRightMotor.setVoltage(-0.975);
      rightMotor.setVoltage(-0.975);
      rTurnCount--;
    } else { //Robot should go forward unless a Touch Sensor detects something.
      leftMotor.setVoltage(9.525);
      rightMotor.setVoltage(9.525);
    }
  }

}
