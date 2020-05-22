
#ifndef TOUCH_SENSOR_H
#define TOUCH_SENSOR_H

#include "HardwareSimulator.h"

class TouchSensor {

 public:
  TouchSensor( HardwareSimulator &, int, int );
  ~TouchSensor();
  bool detect();

 private:
  HardwareSimulator & theHardwareSimulator;
  int type;
  int side;
					 

};

#endif // TOUCH_SENSOR_H
