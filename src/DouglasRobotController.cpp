
#include <cassert>
#include "DouglasRobotController.h"

DouglasRobotController::DouglasRobotController( HardwareSimulator &
						hardwareSimulatorDesired,
						int typeDesired )
  : RobotController( hardwareSimulatorDesired, typeDesired )
{
  //Following psuedo-random number generator
	//was implemented using Mother-of-All generator
	//from internet site http://www.agner.org/random
	//initialize random array with seed of 1
	s = 1;	
	for (i=0; i<5; i++) {
		s = s * 29943829 - 1;
		x[i] = s * (1./(65536.*65536.));}
	// randomize some more
	for (i=0; i<19; i++) {
		c = (long double)2111111111.0 * x[3] +
		1492.0 * (x[3] = x[2]) +
		1776.0 * (x[2] = x[1]) +
		5115.0 * (x[1] = x[0]) + x[4];
		x[4] = floorl(c);
		x[0] = c - x[4];
		x[4] = x[4] * (1./(65536.*65536.));}

	//sets intitial conditions for the robot
	left = 0;
	right = 0;
	time = theClock.getTime();
	touched = false;
}

void DouglasRobotController::runControlLoop()
{

	//this whole function is built based upon the assumption that
	//this function will be called every 0.1 seconds 
	assert( type == HardwareSimulator::PURSUING ||
		    type == HardwareSimulator::EVADING );
  
	if ( type == HardwareSimulator::PURSUING ) 
	{
		// If beacon is detected, drive forward, otherwise, rotate
		if ( theBeaconSensor.detect() ) 
		{
			 leftMotor.setVoltage( 5.0 );
	   		 rightMotor.setVoltage( 5.0 );
		}
		else 
		{
			 leftMotor.setVoltage( 5 );
			 rightMotor.setVoltage( -1 );
		}
	}  
	   
	else { // type == EVADING
    // complete random movements unless wall or robot is detected through sensors
		//"time" variable records the time when a new action will be initialized
		  //IFLEVEL: 1
			//if it was touched
			if(!touched)
			{
				//IFLEVEL: 2
				//check if it is touched, this holds first priority
				if((leftTouchSensor.detect())||(rightTouchSensor.detect()))
				{
					leftMotor.setVoltage(-9.525);
					rightMotor.setVoltage(-2.325);
			  		time = theClock.getTime() + 0.5;
			  		touched = true;
				}
				//IFLEVEL: 2
				//if its not touched check the previous duration for previous movement
				//it its up, get new movement and duration
				else if( (time-theClock.getTime()) < 0 )
				{
					//get random number one for movement
			  		c = (long double)2111111111.0 * x[3] +
					1492.0 * (x[3] = x[2]) +
					1776.0 * (x[2] = x[1]) +
					5115.0 * (x[1] = x[0]) + x[4];
					x[4] = floorl(c);
		    		x[0] = c - x[4];
		  			x[4] = x[4] * (1./(65536.*65536.));
					rnd1 = long(6 * x[0]);
		  			if (rnd1 >= 6) rnd1 = 5;
			   		
					//get random number two for duration
		  			c = (long double)2111111111.0 * x[3] +
		    		1492.0 * (x[3] = x[2]) +
					1776.0 * (x[2] = x[1]) +
					5115.0 * (x[1] = x[0]) + x[4];
					x[4] = floorl(c);
					x[0] = c - x[4];
					x[4] = x[4] * (1./(65536.*65536.));
					rnd2 = long(11 * x[0]); 
					if (i >= 11) i = 10;
          
					//switch statement to set the voltages for movements based 
					//on the random number rnd1
					switch(rnd1)
					{
						case 0:
						{
							left = 9.525;
							right = 9.525;
							break;
						}
						case 1:
						{
							left = 9.525;
							right = 4.725;
							break;
						}
						case 2:
						{
							left = 4.725;
							right = 9.525;
							break;
						}
						case 3:
						{
							left = -9.525;
							right = -9.525;
							break;
						}
						case 4:
						{
							left = -9.525;
							right = -4.725;
							break;
						}
						case 5:
						{
							left = -4.725;
							right = -9.525;
							break;
						}
						default:
						{
							left = 9.525;
							right = 9.525;
							break;
						}
					}
					//sets voltages and duration
					leftMotor.setVoltage(left);
					rightMotor.setVoltage(right);
					time = theClock.getTime() + double(rnd2*0.1);
				}
				else
				{
					//this will only execute if the robot is not touched, and the previous
					//duration is not up for the movement.  this will keep track of the duration
					//modifier in the event that the duration is changed due to a sensor detection
					rnd2--;
				}
       
				//end of first if statement
			}
			//IFLEVEL: 1
		    //if it is touched, then check to see if the half second cycle is
			//over so that it can reset the voltages, duration, touch sensors
			else if( (time-theClock.getTime()) < 0) 
			{
				touched = false;
				leftMotor.setVoltage(left);
				rightMotor.setVoltage(right);
				time = theClock.getTime() + double(rnd2*0.1);
			}

			//else it will continue on it course and speed
  }

}
