
#include <cassert>
#include "MotorDriverElectronics.h"

MotorDriverElectronics::MotorDriverElectronics( Robot & robotDesired,
						MotorDriverSide
						motorSideDesired)
  : robotWithMotor( robotDesired )
{
  motorLocation = motorSideDesired;
}

MotorDriverElectronics::~MotorDriverElectronics()
{
}

void MotorDriverElectronics::setOutputPortValue( unsigned char digitalLevel )
{
  short sign = ( digitalLevel & 0x80 ) >> 7;
  short magnitude = digitalLevel & 0x7f;

  assert( ( sign == 0 || sign == 1 ) &&
	  ( motorLocation == MOTOR_ON_LEFT ||
	    motorLocation == MOTOR_ON_RIGHT ) );


  if ( sign == 0 ) {
    if ( motorLocation == MOTOR_ON_LEFT )
      robotWithMotor.setEl( static_cast< double >( magnitude ) * 0.075 );
    else // motorLocation == MOTOR_ON_RIGHT
      robotWithMotor.setEr( static_cast< double >( magnitude ) * 0.075 );
  }
  else { // sign == 1
    if ( motorLocation == MOTOR_ON_LEFT )
      robotWithMotor.setEl( -static_cast< double >( magnitude ) * 0.075 );
    else // motorLocation == MOTOR_ON_RIGHT
      robotWithMotor.setEr( -static_cast< double >( magnitude ) * 0.075 );
  }

			  
}

MotorDriverSide MotorDriverElectronics::getMotorLocation()
{
  return motorLocation;
}

double MotorDriverElectronics::getMotorVoltage()
{
  assert( motorLocation == MOTOR_ON_LEFT || motorLocation == MOTOR_ON_RIGHT );

  if ( motorLocation == MOTOR_ON_LEFT )
    return robotWithMotor.getEl();
  else
    return robotWithMotor.getEr();
}

