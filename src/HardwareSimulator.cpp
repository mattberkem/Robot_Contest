
#include <cmath>
#include <cassert>
#include "RobotController.h"
#include "HardwareSimulator.h"

#define M_PI		3.14159265358979323846

const int HardwareSimulator::PURSUING = 0;
const int HardwareSimulator::EVADING = 1;
const int HardwareSimulator::RIGHT = 0;
const int HardwareSimulator::LEFT = 1;

HardwareSimulator::HardwareSimulator()
  : field( 0.0, 1.5, 0.0, 3.0, 5000.0 ),
    robotInitialState( 5 ),
    pursuingRobot( robotInitialState, 0.0, 0.0, field, 0.1 ),
    evadingRobot( robotInitialState, 0.0, 0.0, field, 0.1 ),
    pursuingRobotBeaconSensor( pursuingRobot, evadingRobot ),
    evadingRobotBeaconSensor( evadingRobot, pursuingRobot ),
    pursuingRobotRightTouchSensor( pursuingRobot, evadingRobot,
				   field, 0.12,  0.1 ),
    pursuingRobotLeftTouchSensor( pursuingRobot, evadingRobot,
				  field, 0.12, -0.1 ),
    evadingRobotRightTouchSensor( evadingRobot, pursuingRobot,
				 field, 0.12,  0.1 ),
    evadingRobotLeftTouchSensor( evadingRobot, pursuingRobot,
				 field, 0.12, -0.1 ),
    pursuingRobotRightMotorDriver( pursuingRobot, MOTOR_ON_RIGHT ),
    pursuingRobotLeftMotorDriver( pursuingRobot, MOTOR_ON_LEFT   ),
    evadingRobotRightMotorDriver( evadingRobot, MOTOR_ON_RIGHT ),
    evadingRobotLeftMotorDriver( evadingRobot, MOTOR_ON_LEFT   ),
    robotPair( pursuingRobot, evadingRobot, 10000.0 ),
    theIntegrator( robotPair, 1000, 0.01, 1.0e-6, 0.001, 0.0 ),
    timeStep( 0 ), tStart( 0.0 ), tEnd( 0.0 ), collisionTime( -1.0 )
{
  // set initial conditions for the pursuing robot
  robotInitialState(1) = 0.2;
  robotInitialState(2) = 1.3;
  robotInitialState(3) = 0.0;
  robotInitialState(4) = 0.0;
  robotInitialState(5) = 0.0;

  pursuingRobot.setState( robotInitialState );

  robotInitialState(1) = 2.8;
  robotInitialState(2) = 0.2;
  robotInitialState(3) = M_PI;
  robotInitialState(4) = 0.0;
  robotInitialState(5) = 0.0;

  evadingRobot.setState( robotInitialState );

  // The integrator sets its starting state when it is initialized. Since
  // the integrator was intialized when the robots had the wrong starting
  // states, I added this.  There probably is a better way.
  resetIntegratorState();

  // connect the pursuing robot beacon sensor to bit 0 of
  // processor input port number 0
  pursuingRobotProcessor.connectInputDevice( & pursuingRobotBeaconSensor,
					     0x01, 0 );

  // connect the pursuing robot right touch sensor to bit 1 of
  // processor input port number 0
  pursuingRobotProcessor.connectInputDevice( & pursuingRobotRightTouchSensor,
					     0x02, 0 );

  // connect the pursuing robot left touch sensor to bit 2 of
  // processor input port number 0
  pursuingRobotProcessor.connectInputDevice( & pursuingRobotLeftTouchSensor,
					     0x04, 0 );

  // connect the pursuing robot right motor driver to bits 0--7 of
  // processor output port number 0
  pursuingRobotProcessor.connectOutputDevice( & pursuingRobotRightMotorDriver,
					      0xff, 0 );

  // connect the pursuing robot left motor driver to bits 0--7 of
  // processor output port number 1
  pursuingRobotProcessor.connectOutputDevice( & pursuingRobotLeftMotorDriver,
					      0xff, 1 );




  // connect the evading robot beacon sensor to bit 0 of
  // processor input port number 0
  evadingRobotProcessor.connectInputDevice( & evadingRobotBeaconSensor,
					    0x01, 0 );

  // connect the evading robot right touch sensor to bit 1 of
  // processor input port number 0
  evadingRobotProcessor.connectInputDevice( & evadingRobotRightTouchSensor,
					    0x02, 0 );

  // connect the evading robot left touch sensor to bit 2 of
  // processor input port number 0
  evadingRobotProcessor.connectInputDevice( & evadingRobotLeftTouchSensor,
					    0x04, 0 );

  // connect the evading robot right motor driver to bits 0--7 of
  // processor output port number 0
  evadingRobotProcessor.connectOutputDevice( & evadingRobotRightMotorDriver,
					     0xff, 0 );

  // connect the evading robot left motor driver to bits 0--7 of
  // processor output port number 1
  evadingRobotProcessor.connectOutputDevice( & evadingRobotLeftMotorDriver,
					     0xff, 1 );
  
}
    

  
HardwareSimulator::~HardwareSimulator()
{}

void HardwareSimulator::simulateOneTenthSecond()
{
  assert( pursuingRobotControllerPtr !=0 && evadingRobotControllerPtr != 0 );

  processInputPorts();
  pursuingRobotControllerPtr->runControlLoop();
  evadingRobotControllerPtr->runControlLoop();
  processOutputPorts();

  tStart = static_cast< double >( timeStep ) * 0.1;
  tEnd = static_cast< double >( timeStep + 1 ) * 0.1;

  theIntegrator.odeint( tStart, tEnd );

  timeStep++;
  pursuingRobotProcessor.incrementTimeStep();
  evadingRobotProcessor.incrementTimeStep();

  if ( robotPair.getCollisionOccurred() && collisionTime < 0.0 )
    collisionTime = ( tStart + tEnd )/2.0;

  // always reset the collisionOccurred flag. this is ok since we can
  // always check this flag before we get to this point if, at a later
  // point, we want to detect collisions beyond the first collision.
  robotPair.resetCollisionOccurred();


}

void HardwareSimulator::simulateMultipleTenths( int iterations )
{
  for ( int i = 0; i < iterations; i++ )
    simulateOneTenthSecond();

}

Vector HardwareSimulator::getPursuingRobotState()
{
  return pursuingRobot.getState();
}

Vector HardwareSimulator::getEvadingRobotState()
{
  return evadingRobot.getState();
}

void HardwareSimulator::setPursuingRobotState( Vector & state )
{
  pursuingRobot.setState( state );
}

void HardwareSimulator::setEvadingRobotState( Vector & state )
{
  evadingRobot.setState( state );
}

double HardwareSimulator::getTime()
{
  return tEnd;
}

void HardwareSimulator::setPursuingRobotOutputPort( unsigned short portNumber,
						    unsigned char value )
{
  pursuingRobotProcessor.setOutputPort( portNumber, value );
}

void HardwareSimulator::setEvadingRobotOutputPort( unsigned short portNumber,
						   unsigned char value )
{
  evadingRobotProcessor.setOutputPort( portNumber, value );
}

void HardwareSimulator::processOutputPorts()
{
  pursuingRobotProcessor.outputToDevices();
  evadingRobotProcessor.outputToDevices();
}

void HardwareSimulator::processInputPorts()
{
  pursuingRobotProcessor.readInDevices();
  evadingRobotProcessor.readInDevices();
}

unsigned char HardwareSimulator::getPursuingRobotInputPort( unsigned short
							    portNumber )
{
  return pursuingRobotProcessor.getInputPort( portNumber );
}

unsigned char HardwareSimulator::getEvadingRobotInputPort( unsigned short
							    portNumber )
{
  return evadingRobotProcessor.getInputPort( portNumber );
}

unsigned char HardwareSimulator::getPursuingRobotOutputPort( unsigned short
							     portNumber )
{
  return pursuingRobotProcessor.getOutputPort( portNumber );
}

unsigned char HardwareSimulator::getEvadingRobotOutputPort( unsigned short
							     portNumber )
{
  return evadingRobotProcessor.getOutputPort( portNumber );
}

// this causes the integrator to re-read its starting state from
// the device it is connected to.
void HardwareSimulator::resetIntegratorState()
{
  theIntegrator.setState();
}

double HardwareSimulator::getCollisionTime()
{
  return collisionTime;
}

void HardwareSimulator::setPursuingRobotController( RobotController *
						    robotControllerPtr )
{
  pursuingRobotControllerPtr = robotControllerPtr;
}

void HardwareSimulator::setEvadingRobotController( RobotController *
						    robotControllerPtr )
{
  evadingRobotControllerPtr = robotControllerPtr;
}

long HardwareSimulator::getPursuingProcessorTime()
{
  return pursuingRobotProcessor.getTimeStep();
}

long HardwareSimulator::getEvadingProcessorTime()
{
  return evadingRobotProcessor.getTimeStep();
}

void HardwareSimulator::resetTime()
{
  timeStep = 0;
  tStart = tEnd = 0.0;
  pursuingRobotProcessor.resetTimeStep();
  evadingRobotProcessor.resetTimeStep();
  collisionTime = -1.0;
}
