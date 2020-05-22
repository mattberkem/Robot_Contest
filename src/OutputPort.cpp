
#include <cassert>
#include "OutputPort.h"

OutputPort::OutputPort()
{
  numDevices = 0;
  value = 0;
}

OutputPort::~OutputPort()
{
}

// This approach would need more work to be robust. It is assumed that
// the mask consists of contiguous 1's, but this is never checked. The
// programmer should make sure this is true until a check is added.
void OutputPort::connectDevice( ProcessorOutputDevice * devicePtr,
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

void OutputPort::outputToDevices()
{
  unsigned char temp;


  // take the port value and perform bitwise AND with the connection
  // mask to get the appropriate (but left shifted) value to output to
  // the device. Then, shift it to the right so that the bits are in
  // the right place.
  for ( int i = 0; i < numDevices; i++ ) {
    temp = ( value & connectionMask[ i ] ) >>
      findShiftAmount( connectionMask[ i ] );

    (*deviceList[ i ]).setOutputPortValue( temp );


  }
}

short OutputPort::findShiftAmount( unsigned char mask )
{
  assert( mask != 0 );

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

void OutputPort::setPortValue( unsigned char valueDesired )
{
  value = valueDesired;
}

unsigned char OutputPort::getPortValue()
{
  return value;
}
