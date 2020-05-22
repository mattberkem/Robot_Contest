
#ifndef INPUT_PORT_H
#define INPUT_PORT_H

#include "ProcessorInputDevice.h"

class InputPort {

 public:
  InputPort();
  ~InputPort();
  void connectDevice( ProcessorInputDevice *, unsigned char );
  void readInDevices();
  unsigned char getPortValue();

 private:
  unsigned char value;
  ProcessorInputDevice * deviceList[ 8 ];
  unsigned char connectionMask[ 8 ];
  short numDevices;
  short findShiftAmount( unsigned char );

};

#endif // INPUT_PORT_H
