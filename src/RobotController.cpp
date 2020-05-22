
#include "RobotController.h"

RobotController::RobotController( HardwareSimulator &
				  hardwareSimulatorDesired,
				  int typeDesired )
  : leftTouchSensor( hardwareSimulatorDesired, typeDesired,
		     HardwareSimulator::LEFT ),
  rightTouchSensor( hardwareSimulatorDesired, typeDesired,
		    HardwareSimulator::RIGHT ),
  theBeaconSensor(  hardwareSimulatorDesired, typeDesired ),
  leftMotor( hardwareSimulatorDesired, typeDesired,
	     HardwareSimulator::LEFT ),
  rightMotor( hardwareSimulatorDesired, typeDesired,
	      HardwareSimulator::RIGHT ), type( typeDesired ),
  theClock( hardwareSimulatorDesired, typeDesired )
{
}
