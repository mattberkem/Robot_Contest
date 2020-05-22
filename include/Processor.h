
#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "OutputPort.h"
#include "InputPort.h"

class Processor {

 public:
  Processor();
  ~Processor();
  void setOutputPort( unsigned short, unsigned char );
  unsigned char getInputPort( unsigned  short );
  unsigned char getOutputPort( unsigned  short );
  void incrementTimeStep();
  long getTimeStep();
  void resetTimeStep();
  void connectInputDevice( ProcessorInputDevice *, unsigned char,
			   unsigned short );
  void connectOutputDevice( ProcessorOutputDevice *, unsigned char,
			    unsigned short);
  void outputToDevices();
  void readInDevices();
    

 private:
  OutputPort outputPortList[ 2 ];
  InputPort inputPortList[ 2 ];
  long timeStep;

};

#endif // PROCESSOR_H
