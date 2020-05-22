
#include <cassert>
#include "InputPort.h"

InputPort::InputPort()
{
  numDevices = 0;
  value = 0;
}

InputPort::~InputPort()
{
}

// This approach would need more work to be robust. It is assumed that
// the mask consists of contiguous 1's, but this is never checked. The
// programmer should make sure this is true until a check is added.
void InputPort::connectDevice( ProcessorInputDevice * devicePtr,
			   unsigned char mask )
{
  unsigned char currentMask = 0;

  assert( numDevices < 9 );

  // Build up the current total mask from the individual masks
  for ( int i = 0; i < numDevices; i++ )
    currentMask |= connectionMask[ i ];

  // Make sure there is room for the device at the desired location
  assert( ( mask & currentMask ) == 0 );

  // add the device
  deviceList[ numDevices ] = devicePtr;
  connectionMask[ numDevices ] = mask;
  numDevices++;
}

void InputPort::readInDevices()
{
  unsigned char temp;

  // set value to the result of reading in all input devices. we have
  // to shift the values returned by the devices the appropriate number
  // and then mask them before assigning them to value
  // Example:
  //   value initially 1010 1101, connection mask is 0011 1100
  //   temp gets assigned 0000 0010 after the call to getInputPortValue()
  //   in the first step, value becomes 1000 0001 = 1010 1101 & ~0011 1100
  //   in the next step, value becomes 1000 1001 = 1000 0001 | 0000 1000
  for ( int i = 0; i < numDevices; i++ ) {
    temp = (*deviceList[ i ]).getInputPortValue();
    // set bits corresponding to connection mask to all be 0
    value &= ~connectionMask[ i ];
    // now, OR with the values just read in after shifting and masking
    value |= ( temp << findShiftAmount( connectionMask[ i ] ) ) &
      connectionMask[ i ];
  }
}

unsigned char InputPort::getPortValue()
{
  return value;
}

short InputPort::findShiftAmount( unsigned char mask )
{
  assert( static_cast< short >( mask ) != 0 );

  if ( ( mask & 0x01 ) != 0 )
    return 0;
  if ( ( mask & 0x02 ) != 0 )
    return 1;
  if ( ( mask & 0x04 ) != 0 )
    return 2;
  if ( ( mask & 0x08 ) != 0 )
    return 3;
  if ( ( mask & 0x10 ) != 0 )
    return 4;
  if ( ( mask & 0x20 ) != 0 )
    return 5;
  if ( ( mask & 0x40 ) != 0 )
    return 6;
  else
    return 7;
}
