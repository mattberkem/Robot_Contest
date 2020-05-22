
#include <cassert>
#include "Clock.h"

Clock::Clock( HardwareSimulator & hardwareSimulatorDesired,
	      int typeDesired )
  : theHardwareSimulator( hardwareSimulatorDesired ), type( typeDesired )
{
}

Clock::~Clock()
{
}

double Clock::getTime()
{
  long time;

  assert( type == HardwareSimulator::PURSUING ||
	  type == HardwareSimulator::EVADING     );

  if ( type == HardwareSimulator::PURSUING )
    time = theHardwareSimulator.getPursuingProcessorTime();
  else
    time = theHardwareSimulator.getEvadingProcessorTime();

  return static_cast< double >( time ) * 0.1;
}
