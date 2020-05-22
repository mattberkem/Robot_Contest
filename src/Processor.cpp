
#include "Processor.h"

Processor::Processor()
{
  timeStep = 0;
}

Processor::~Processor()
{
}

void Processor::setOutputPort( unsigned short portNumber,
			       unsigned char portValueDesired )
{
  outputPortList[ portNumber ].setPortValue( portValueDesired );
}

unsigned char Processor::getInputPort( unsigned short portNumber )
{
  return inputPortList[ portNumber ].getPortValue();
}

unsigned char Processor::getOutputPort( unsigned short portNumber )
{
  return outputPortList[ portNumber ].getPortValue();
}

void Processor::incrementTimeStep()
{
  timeStep++;
}

long Processor::getTimeStep()
{
  return timeStep;
}

void Processor::resetTimeStep()
{
  timeStep = 0;
}

void Processor::connectInputDevice( ProcessorInputDevice * inputDevicePtr,
				    unsigned char inputMask,
				    unsigned short portNumber )
{
  inputPortList[ portNumber ].connectDevice( inputDevicePtr, inputMask );
}



void Processor::connectOutputDevice( ProcessorOutputDevice * outputDevicePtr,
				     unsigned char outputMask,
				     unsigned short portNumber )
{
  outputPortList[ portNumber ].connectDevice( outputDevicePtr,  outputMask );
}

void Processor::outputToDevices()
{
  outputPortList[ 0 ].outputToDevices();
  outputPortList[ 1 ].outputToDevices();
}

void Processor::readInDevices()
{
  inputPortList[ 0 ].readInDevices();
  inputPortList[ 1 ].readInDevices();
}
