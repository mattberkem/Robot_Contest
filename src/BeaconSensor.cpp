
#include <cassert>
#include "BeaconSensor.h"

BeaconSensor::BeaconSensor( HardwareSimulator & hardwareSimulatorDesired,
			    int typeDesired )
  : theHardwareSimulator( hardwareSimulatorDesired ), type( typeDesired )
{
}

BeaconSensor::~BeaconSensor()
{
}

bool BeaconSensor::detect()
{
  unsigned char portValue;

  assert( type == HardwareSimulator::PURSUING ||
	  type == HardwareSimulator::EVADING );

  if ( type == HardwareSimulator::PURSUING )
    portValue = theHardwareSimulator.getPursuingRobotInputPort( 0 );
  else // type == EVADING
    portValue = theHardwareSimulator.getEvadingRobotInputPort( 0 );

  portValue &= 0x01;

  if ( portValue != 0 )
    return true;
  else
    return false;


}
