
#ifndef CLOCK_H
#define CLOCK_H

#include "HardwareSimulator.h"

class Clock {
 public:
  Clock( HardwareSimulator &, int );
  ~Clock();
  double getTime();

 private:
  HardwareSimulator & theHardwareSimulator;
  int type;

};

#endif // CLOCK_H
