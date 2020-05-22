
#ifndef BEACON_SENSOR_H
#define BEACON_SENSOR_H

#include "HardwareSimulator.h"

class BeaconSensor{

 public:
  BeaconSensor( HardwareSimulator &, int );
  ~BeaconSensor();
  bool detect();

 private:
  HardwareSimulator & theHardwareSimulator;
  int type;


};

#endif // BEACON_SENSOR_H
