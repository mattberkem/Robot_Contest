
#include <cassert>
#include "TouchSensor.h"

TouchSensor::TouchSensor( HardwareSimulator & hardwareSimulatorDesired,
			  int typeDesired, int sideDesired )
  : theHardwareSimulator( hardwareSimulatorDesired ), type( typeDesired ),
    side( sideDesired )
{
}

TouchSensor::~TouchSensor()
{
}

bool TouchSensor::detect()
{
  unsigned char portValue;

  assert( type == HardwareSimulator::PURSUING ||
	  type == HardwareSimulator::EVADING );

  assert( side == HardwareSimulator::PURSUING ||
	  side == HardwareSimulator::EVADING );

  if ( type == HardwareSimulator::PURSUING )
    portValue = theHardwareSimulator.getPursuingRobotInputPort( 0 );
  else // type == EVADING
    portValue = theHardwareSimulator.getEvadingRobotInputPort( 0 );

  if ( side == HardwareSimulator::RIGHT )
      portValue &= 0x02;
  else // side == LEFT
      portValue &= 0x04;

  if ( portValue != 0 )
    return true;
  else
    return false;
}
