
#ifndef HARDWARE_SIMULATOR_H
#define HARDWARE_SIMULATOR_H

#include "Vector.h"
#include "PlayingField.h"
#include "HWBeaconSensor.h"
#include "HWTouchSensor.h"
#include "MotorDriverElectronics.h"
#include "Processor.h"
#include "Robot.h"
#include "InteractingRobots.h"
#include "Integrator.h"

class RobotController;

class HardwareSimulator {
 public:
  HardwareSimulator();
  ~HardwareSimulator();
  void simulateOneTenthSecond();
  void simulateMultipleTenths( int );
  Vector getPursuingRobotState();
  Vector getEvadingRobotState();
  double getTime();
  double getCollisionTime();
  void setPursuingRobotState( Vector & );
  void setEvadingRobotState( Vector & );
  void setPursuingRobotOutputPort( unsigned short, unsigned char );
  void setEvadingRobotOutputPort( unsigned short, unsigned char );
  void processOutputPorts();
  void processInputPorts();
  unsigned char getPursuingRobotInputPort( unsigned short );
  unsigned char getEvadingRobotInputPort( unsigned short );
  unsigned char getPursuingRobotOutputPort( unsigned short );
  unsigned char getEvadingRobotOutputPort( unsigned short );
  void resetIntegratorState();
  void resetTime();
  long getPursuingProcessorTime();
  long getEvadingProcessorTime();
  static const int PURSUING;
  static const int EVADING;
  static const int RIGHT;
  static const int LEFT;
  void setPursuingRobotController( RobotController * );
  void setEvadingRobotController( RobotController * );


 private:
  PlayingField field;
  Vector robotInitialState;
  Robot pursuingRobot;
  Robot evadingRobot;
  HWBeaconSensor pursuingRobotBeaconSensor;
  HWBeaconSensor evadingRobotBeaconSensor;
  HWTouchSensor pursuingRobotRightTouchSensor;
  HWTouchSensor pursuingRobotLeftTouchSensor;
  HWTouchSensor evadingRobotRightTouchSensor;
  HWTouchSensor evadingRobotLeftTouchSensor;
  MotorDriverElectronics pursuingRobotRightMotorDriver;
  MotorDriverElectronics pursuingRobotLeftMotorDriver;
  MotorDriverElectronics evadingRobotRightMotorDriver;
  MotorDriverElectronics evadingRobotLeftMotorDriver;
  Processor pursuingRobotProcessor;
  Processor evadingRobotProcessor;
  InteractingRobots robotPair;
  Integrator theIntegrator;
  long timeStep;
  double tStart;
  double tEnd;
  double collisionTime;
  RobotController * pursuingRobotControllerPtr;
  RobotController * evadingRobotControllerPtr;
    
};

#endif // HARDWARE_SIMULATOR_H
