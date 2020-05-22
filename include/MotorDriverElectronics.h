
#ifndef MOTOR_DRIVER_ELECTRONICS_H
#define MOTOR_DRIVER_ELECTRONICS_H

#include "ProcessorOutputDevice.h"
#include "Robot.h"

enum MotorDriverSide { MOTOR_ON_RIGHT, MOTOR_ON_LEFT };

class MotorDriverElectronics : public ProcessorOutputDevice {

 public:
  MotorDriverElectronics( Robot &, MotorDriverSide );
  ~MotorDriverElectronics();
  virtual void setOutputPortValue( unsigned char );
  double getMotorVoltage();
  MotorDriverSide getMotorLocation();

 private:
  Robot & robotWithMotor;
  MotorDriverSide motorLocation;

};

#endif // MOTOR_DRIVER_ELECTRONICS_H
