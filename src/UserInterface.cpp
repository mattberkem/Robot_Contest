
#include <cassert>
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

#include <iomanip>

using std::ios;
using std::hex;
using std::dec;
using std::setiosflags;
using std::resetiosflags;

#include <cmath>
#include "UserInterface.h"

#define M_PI		3.14159265358979323846


UserInterface::UserInterface( HardwareSimulator & hardwareSimulatorDesired )
  : theHardwareSimulator( hardwareSimulatorDesired ),
    pursuingRobotState( 5 ), evadingRobotState( 5 ),
    firstCollisionNotOccurred( true )
{
  // Robots get erased before being drawn. The first time, we want to make
  // sure that we erase a safe area
  lastRobotLocations[ PURSUING ][ 0 ] = 10;
  lastRobotLocations[ PURSUING ][ 1 ] = 10;
  lastRobotLocations[ EVADING ][ 0 ] = 10;
  lastRobotLocations[ EVADING ][ 1 ] = 10;

  // initialize screen buffer to spaces
  for ( int i = 0; i < 18; i++ )
    for ( int j = 0; j < 62; j++ )
      screenBuffer[ i ][ j ] = ' ';

  writeFieldBorder();

}

UserInterface::~UserInterface()
{
}

void UserInterface::printStatus()
{
  cout << endl
       << "-----------------------------------------------------------\n"
       << "SYSTEM STATUS" << endl;

  cout.precision( 3 );
  cout.setf( ios::fixed );

  cout << "Simulation Time: " << theHardwareSimulator.getTime() << endl;

  getRobotStates();

  cout << "Pursuing Robot:\n" << "(x, y, theta, v, omega) = ( ";
  for ( unsigned i = 1; i < 5; i++ ) {
    cout.width( 7 );
    cout << pursuingRobotState( i ) << ", ";
  }
  cout.width( 7 );
  cout << pursuingRobotState( 5 ) << " )" << endl;

  cout << "Evading Robot:\n" << "(x, y, theta, v, omega) = ( ";
  for ( int i = 1; i < 5; i++ ) {
    cout.width( 7 );
    cout << evadingRobotState( i ) << ", ";
  }
  cout.width( 7 );
  cout << evadingRobotState( 5 ) << " )" << endl;

  double collisionTime = theHardwareSimulator.getCollisionTime();

  if ( collisionTime > 0.0 && firstCollisionNotOccurred ) {
    cout << "Collision Occurred!" << endl;
    firstCollisionNotOccurred = false;
  }

  cout << "Collision Time: ";

  if ( collisionTime < 0.0 )
    cout << "N/A" << endl;
  else
    cout << collisionTime << endl;

}

void UserInterface::writeFieldBorder()
{
  for ( int j = 0; j < 63; j++ ) {
    screenBuffer[ 0 ][ j ] = '*';
    screenBuffer[ 17 ][ j ] = '*';
  }
  for ( int i = 0; i < 18; i++ ) {
    screenBuffer[ i ][ 0 ] = '*';
    screenBuffer[ i ][ 62 ] = '*';
  }

}

void UserInterface::writeRobotFromState( RobotType theRobotType )
{
  short row, col;
  Vector state( 5 );

  if ( theRobotType == PURSUING )
    state = pursuingRobotState;
  else
    state = evadingRobotState;

  // round up with ceil() and then use col - 2 and row - 1 to compensate
  // in writeRobotFromIndex()
  //          0.05 <  x <= 0.10 means col =  3, x is drawn at 0.075
  //          2.90 <  x <= 2.95 means col = 60, x is drawn at 2.925
  //          0.0  <= y <  0.10 means row = 16, y is drawn at 0.050
  //          1.4  <= y <  1.50 means row =  2, y is drawn at 1.450
  // add 1 to allow for the border
  row = static_cast< short >( ceil( 10.0*( 1.5 - state( 2 ) ) ) ) + 1;
  col = static_cast< short >( ceil( 20.0 * state( 1 ) ) ) + 1;

  assert( 1 < row && row < 17 && 2 < col && col < 61 );

  // save robot locations so they can be erased later
  lastRobotLocations[ theRobotType ][ 0 ] = row;
  lastRobotLocations[ theRobotType ][ 1 ] = col;

  writeRobotFromIndex( row, col, theRobotType );


}

void UserInterface::eraseRobots()
{

  writeRobotFromIndex( lastRobotLocations[ PURSUING ][ 0 ],
		       lastRobotLocations[ PURSUING ][ 1 ], GHOST );

  writeRobotFromIndex( lastRobotLocations[ EVADING ][ 0 ],
		       lastRobotLocations[ EVADING ][ 1 ], GHOST );
}

void UserInterface::writeRobotFromIndex( short row, short col,
					 RobotType theRobotType )
{
  char robotSymbol;

  switch( theRobotType ) {
  case PURSUING:
    robotSymbol = 'P';
    break;
  case EVADING:
    robotSymbol = 'E';
    break;
  case GHOST:
    robotSymbol = ' ';
    break;
  default:
    robotSymbol = ' ';
    break;
  }

  assert( 1 < row && row < 17 && 2 < col && col < 61 );

  for ( short i = -2; i < 2; i++ ) {
    screenBuffer[ row ][ col + i ] = robotSymbol;
    screenBuffer[ row - 1 ][ col + i ] = robotSymbol;
  }


}

void UserInterface::printGraphics()
{
  eraseRobots();

  getRobotStates();
  writeRobotFromState( PURSUING );
  writeRobotFromState( EVADING );

  for ( int i = 0; i < 18; i++ ) {
    for ( int j = 0; j < 63; j++ )
      cout << screenBuffer[ i ][ j ];
    cout << endl;
  }
  
}

void UserInterface::getRobotStates()
{
  pursuingRobotState = theHardwareSimulator.getPursuingRobotState();
  evadingRobotState = theHardwareSimulator.getEvadingRobotState();
}

void UserInterface::printMenu()
{
  cout << "\nMENU\n"
       << "1:       Change pursuing robot state.\n"
       << "2:       Change evading robot state.\n"
       << "3:       Increment simulation time.\n"
       << "4:       Display processor state.\n"
       << "5:       Reset simulation.\n"
       << "6:       Change players.\n"
       << "7:       Show current players.\n"
       << "9:       Quit.\n"
       << "default: Increment simulation time by 0.1 seconds.\n\n\n"
       << "Choice: ";

}

char UserInterface::processUserResponse()
{
  char response;

  response = cin.get();

  switch( response ) {
  case '1':
    // get rid of extra carriage return in stream?
    cin.get();
    setPursuingRobotState();
    break;
  case '2':
    // get rid of extra carriage return in stream?
    cin.get();
    setEvadingRobotState();
    break;
  case '3':
    // get rid of extra carriage return in stream?
    cin.get();
    incrementSimulationTime();
    break;
  case '4':
    // get rid of extra carriage return in stream?
    cin.get();
    displayProcessorState();
    break;
  case '5':
    // get rid of extra carriage return in stream?
    cin.get();
    resetSimulation();
    break;
  case '6':
    cin.get();
    changePlayers();
    break;
  case '7':
    cin.get();
    showCurrentPlayers();
    break;
  case '9':
    cin.get();
    break;
  default:
    theHardwareSimulator.simulateOneTenthSecond();
    break;
  }
  return response;
}

void UserInterface::incrementSimulationTime()
{
  double response;
  int iterations;

  cout << "\nEnter the amount to increment the simulation time: ";

  cin >> response;

  //  iterations = static_cast< int >( nearestInteger( response / 0.1 ) );
  iterations = static_cast< int >( floor( response / 0.1 ) );

  while ( iterations <= 1 ) {
    cout << "\n  That input is not allowed, please re-enter: ";
    cin >> response;
    //    iterations = static_cast< int >( nearestInteger( response / 0.1 ) );
    iterations = static_cast< int >( floor( response / 0.1 ) );
  }

  // get rid of extra carriage return in stream?
  cin.get();
  theHardwareSimulator.simulateMultipleTenths( iterations );

}

//double UserInterface::nearestInteger( double value )
//{
//  if ( ceil( value ) - value > value - floor( value ) )
//    return floor( value );
//  else
//    return ceil( value );
//}

void UserInterface::setPursuingRobotState()
{
  Vector userState( 5 );

  cout << "\nChanging pursuing robot state...\n";

  userState = getUserStateInput();

  // get rid of extra carriage return in stream?
  cin.get();
  theHardwareSimulator.setPursuingRobotState( userState );
  theHardwareSimulator.resetIntegratorState();
}



void UserInterface::setEvadingRobotState()
{
  Vector userState( 5 );

  cout << "\nChanging evading robot state...\n";

  userState = getUserStateInput();

  // get rid of extra carriage return in stream?
  cin.get();
  theHardwareSimulator.setEvadingRobotState( userState );
  theHardwareSimulator.resetIntegratorState();
}
 
Vector UserInterface::getUserStateInput()
{
  double response;
  Vector state( 5 );

  for ( int i = 1; i <=5; i++ ) {
    cout << "  New x(" << i << ") : ";
    cin >> response;
    while( userStateInputBad( response, i ) ) {
      cout << "    That input is not allowed, please re-enter : ";
      cin >> response;
    }
    state(i) = response;
  }

  return state;
}
 

bool UserInterface::userStateInputBad( double userInput, int stateNumber )
{
  // should also check if user intersects one robot with another
  // try to do this later.
  switch( stateNumber ) {
  case 1:
    return ( userInput < 0.1 || userInput > 2.9 );
    break;  
  case 2:
    return ( userInput < 0.1 || userInput > 1.4 );
    break;
  case 3:
    return ( userInput < -M_PI || userInput > M_PI );
    break;
  case 4:
    return ( userInput < -2.5 || userInput > 2.5 );
    break;
  case 5:
    return ( userInput < -35.0 || userInput > 35.0 );
    break;
  default:
    return false;
    break;
  }
    
}

void UserInterface::displayProcessorState()
{

  cout << hex << setiosflags( ios::showbase )
       << "\nPursuing processor:\n"
       << "Ouput Port 0: "
       << static_cast< int >( theHardwareSimulator.
			      getPursuingRobotOutputPort( 0 ) )
       << " "
       << "Output Port 1: "
       << static_cast< int >( theHardwareSimulator.
			      getPursuingRobotOutputPort( 1 ) )
       << " "
       << "Input Port 0: "
       << static_cast< int >( theHardwareSimulator.
			      getPursuingRobotInputPort( 0 ) )
       << " "
       << dec << resetiosflags( ios::showbase )
       << "Time: "
       << theHardwareSimulator.getPursuingProcessorTime()
       << hex << setiosflags( ios::showbase )
       << "\n\nEvading processor:\n"
       << "Ouput Port 0: "
       << static_cast< int >( theHardwareSimulator.
			      getEvadingRobotOutputPort( 0 ) )
       << " "
       << "Output Port 1: "
       << static_cast< int >( theHardwareSimulator.
			      getEvadingRobotOutputPort( 1 ) )
       << " "
       << "Input Port 0: "
       << static_cast< int >( theHardwareSimulator.
			      getEvadingRobotInputPort( 0 ) )
       << " "
       << dec << resetiosflags( ios::showbase )
       << "Time: "
       << theHardwareSimulator.getEvadingProcessorTime()
       << endl << endl;

}

void UserInterface::resetSimulation()
{
  // set time to 0 and processor times to 0
  theHardwareSimulator.resetTime();

  // reset processor output ports. it should not be necessary to reset
  // the input ports since they get set by the devices before
  // integration is done. in most cases, it should not be necessary to
  // reset the output ports either except in the (unusual?) case that
  // the robot controller does not set them.
  theHardwareSimulator.setPursuingRobotOutputPort( 0, 0 );
  theHardwareSimulator.setPursuingRobotOutputPort( 1, 0 );
  theHardwareSimulator.setEvadingRobotOutputPort( 0, 0 );
  theHardwareSimulator.setEvadingRobotOutputPort( 1, 0 );

  // set robot states to initial values
  Vector resetState( 5 );

  resetState( 1 ) = 0.2;
  resetState( 2 ) = 1.3;
  resetState( 3 ) = 0.0;
  resetState( 4 ) = 0.0;
  resetState( 5 ) = 0.0;
  theHardwareSimulator.setPursuingRobotState( resetState );

  resetState( 1 ) = 2.8;
  resetState( 2 ) = 0.2;
  resetState( 3 ) = M_PI;
  resetState( 4 ) = 0.0;
  resetState( 5 ) = 0.0;
  theHardwareSimulator.setEvadingRobotState( resetState );

  // force the integrator to re-read the state vector
  theHardwareSimulator.resetIntegratorState();

  // reset collision time will be done in
  // HardwareSimulator::simulateOneTenthSecond(), but we should reset
  // our local flag
  firstCollisionNotOccurred = true;
}

void UserInterface::showListOfPlayers()
{
  cout << "  \n\n  List of Players\n"
       << "  0. Placebo\n"
       << "  1. Douglas\n"
       << "  2. Morales\n"
       << "  3. Mulholland\n"
       << "  4. Stokes\n\n";
}

void UserInterface::changePlayers()
{
  showListOfPlayers();

  cout << "  Enter number for puruser: ";
  cin >> pursuerNumber;
  while( pursuerNumber < 0 || pursuerNumber > 4 ) {
    cout << "    That input is not allowed, please re-enter: ";
    cin >> pursuerNumber;
  }

  cout << "  Enter number for evader: ";
  cin >> evaderNumber;
  while( evaderNumber < 0 || evaderNumber > 4 ) {
    cout << "    That input is not allowed, please re-enter: ";
    cin >> evaderNumber;
  }
  cout << endl << endl;

  // get rid of extra carriage return
  cin.get();


}

void UserInterface::showCurrentPlayers()
{
  showListOfPlayers();

  cout << "Current pursuer is " << pursuerNumber << " "
       << "Current evader is " << evaderNumber << endl << endl;

}
  

int UserInterface::getPursuerNumber()
{
  return pursuerNumber;
}

int UserInterface::getEvaderNumber()
{
  return evaderNumber;
}

void UserInterface::setPursuerNumber( int number )
{
  pursuerNumber = number;
}

void UserInterface::setEvaderNumber( int number )
{
  evaderNumber = number;
}

