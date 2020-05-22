
#include <cmath>
#include "Motor.h"

Motor::Motor( HardwareSimulator & hardwareSimulatorDesired,
	      int typeDesired, int sideDesired )
  : theHardwareSimulator( hardwareSimulatorDesired ), type( typeDesired ),
    side( sideDesired )
{
}

Motor::~Motor()
{
}

void Motor::setVoltage( double value )
{
  unsigned char portValue;

  if ( fabs( value ) <= 9.525 )
    portValue = static_cast< unsigned char>( floor( fabs( value ) / 0.075 ) );
  else
    portValue = 0x7f;

  if ( value < 0.0 )
    portValue |= 0x80;

  if ( type == HardwareSimulator::PURSUING &&
       side == HardwareSimulator::RIGHT )
    theHardwareSimulator.setPursuingRobotOutputPort( 0, portValue );
  else if ( type == HardwareSimulator::PURSUING &&
	    side == HardwareSimulator::LEFT )
    theHardwareSimulator.setPursuingRobotOutputPort( 1, portValue );
  else if ( type == HardwareSimulator::EVADING &&
	    side == HardwareSimulator::RIGHT )
    theHardwareSimulator.setEvadingRobotOutputPort( 0, portValue );
  else // type == EVADING && side == LEFT
    theHardwareSimulator.setEvadingRobotOutputPort( 1, portValue );

}
