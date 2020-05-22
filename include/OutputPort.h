
#ifndef OUTPUT_PORT_H
#define OUTPUT_PORT_H

#include "ProcessorOutputDevice.h"

class OutputPort {

 public:
  OutputPort();
  ~OutputPort();
  void connectDevice( ProcessorOutputDevice *, unsigned char );
  void outputToDevices();
  void setPortValue( unsigned char );
  unsigned char getPortValue();

 private:
  unsigned char value;
  ProcessorOutputDevice * deviceList[ 8 ];
  unsigned char connectionMask[ 8 ];
  short numDevices;
  short findShiftAmount( unsigned char );

};

#endif // OUTPUT_PORT_H
