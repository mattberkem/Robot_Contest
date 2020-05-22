
#include <cassert>
#include "PlaceboRobotController.h"

PlaceboRobotController::PlaceboRobotController( HardwareSimulator &
						hardwareSimulatorDesired,
						int typeDesired )
  : RobotController( hardwareSimulatorDesired, typeDesired )
{
}

void PlaceboRobotController::runControlLoop()
{
  assert( type == HardwareSimulator::PURSUING ||
	  type == HardwareSimulator::EVADING );

  if ( type == HardwareSimulator::PURSUING ) {

    if ( theBeaconSensor.detect() ) {
      leftMotor.setVoltage( 2.0 );
      rightMotor.setVoltage( 2.0 );
    }
    else {
      leftMotor.setVoltage( 0.5 );
      rightMotor.setVoltage( -0.5 );
    }
	
  }
  else { // type == EVADING
    // drive forward for 0.5 seconds, turn for 0.5 seconds, and repeat
    if ( fmod( theClock.getTime(), 1.0 ) < 0.5 ) {
      leftMotor.setVoltage( 2.0 );
      rightMotor.setVoltage( 2.0 );
    }
    else {
      leftMotor.setVoltage( 0.5 );
      rightMotor.setVoltage( -0.5 );
    }
  }

}
