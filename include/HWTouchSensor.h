
#ifndef HW_TOUCH_SENSOR_H
#define HW_TOUCH_SENSOR_H

#include "ProcessorInputDevice.h"
#include "Vector.h"
#include "Robot.h"
#include "PlayingField.h"

class HWTouchSensor : public ProcessorInputDevice {
 public:
  HWTouchSensor( Robot &, Robot &, PlayingField &, double, double );
  ~HWTouchSensor();
  bool detect() const;
  virtual unsigned char getInputPortValue() const;

 private:
  Robot & sensingRobot;
  Robot & otherRobot;
  PlayingField & walls;
  double forwardOffset;
  double rightOffset;
  bool detectRobot( Vector &, Vector & ) const;
  bool detectWall( Vector & ) const;

};

#endif // HW_TOUCH_SENSOR_H
