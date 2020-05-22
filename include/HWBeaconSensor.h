
#ifndef HW_BEACON_SENSOR_H
#define HW_BEACON_SENSOR_H

#include "ProcessorInputDevice.h"
#include "Robot.h"

class HWBeaconSensor : public ProcessorInputDevice {

 public:
  HWBeaconSensor( Robot &, Robot & );
  ~HWBeaconSensor();
  bool detect() const;
  virtual unsigned char getInputPortValue() const;

 private:
  Robot & sensingRobot;
  Robot & emittingRobot;


};

#endif // HW_BEACON_SENSOR_H
