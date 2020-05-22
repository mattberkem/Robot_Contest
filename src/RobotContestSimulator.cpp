
#include "RobotContestSimulator.h"
#include "PlaceboRobotController.h"
#include "MoralesRobotController.h"
#include "MulhollandRobotController.h"
#include "StokesRobotController.h"
#include "DouglasRobotController.h"

RobotContestSimulator::RobotContestSimulator()
  : theHardwareSimulator(), theUserInterface( theHardwareSimulator ),
    pursuingRobotControllerPtr( 0 ), evadingRobotControllerPtr( 0 )
{
  setContestPlayers( 0, 0 );
  theUserInterface.setPursuerNumber( 0 );
  theUserInterface.setEvaderNumber( 0 );
}

RobotContestSimulator::~RobotContestSimulator()
{
  if ( pursuingRobotControllerPtr != 0 )
    delete pursuingRobotControllerPtr;
  if ( evadingRobotControllerPtr != 0 )
    delete evadingRobotControllerPtr;
}

void RobotContestSimulator::runSimulation()
{
  char response;

  do {
    theUserInterface.printStatus();
    theUserInterface.printGraphics();
    theUserInterface.printMenu();

    response = theUserInterface.processUserResponse();

    if ( response == '6' )
      setContestPlayers( theUserInterface.getPursuerNumber(),
			 theUserInterface.getEvaderNumber()   );

  } while ( response != '9' );



}

void RobotContestSimulator::setContestPlayers( int pursuer, int evader )
{
  if ( pursuingRobotControllerPtr != 0 )
    delete pursuingRobotControllerPtr;
  if ( evadingRobotControllerPtr != 0 )
    delete evadingRobotControllerPtr;

  switch( pursuer ) {
  case 0:
    pursuingRobotControllerPtr = new
      PlaceboRobotController( theHardwareSimulator,
			      HardwareSimulator::PURSUING );
    break;
  case 1:
    pursuingRobotControllerPtr = new
      DouglasRobotController( theHardwareSimulator,
			      HardwareSimulator::PURSUING );
    break;
  case 2:
    pursuingRobotControllerPtr = new
      MoralesRobotController( theHardwareSimulator,
			      HardwareSimulator::PURSUING );
    break;
  case 3:
    pursuingRobotControllerPtr = new
      MulhollandRobotController( theHardwareSimulator,
			      HardwareSimulator::PURSUING );
    break;
  case 4:
    pursuingRobotControllerPtr = new
      StokesRobotController( theHardwareSimulator,
			      HardwareSimulator::PURSUING );
    break;
  default:
    pursuingRobotControllerPtr = 0;
    break;
  }


  switch( evader ) {
  case 0:
    evadingRobotControllerPtr = new
      PlaceboRobotController( theHardwareSimulator,
			      HardwareSimulator::EVADING );
    break;
  case 1:
    evadingRobotControllerPtr = new
      DouglasRobotController( theHardwareSimulator,
			      HardwareSimulator::EVADING );
    break;
  case 2:
    evadingRobotControllerPtr = new
      MoralesRobotController( theHardwareSimulator,
			      HardwareSimulator::EVADING );
    break;
  case 3:
    evadingRobotControllerPtr = new
      MulhollandRobotController( theHardwareSimulator,
			      HardwareSimulator::EVADING );
    break;
  case 4:
    evadingRobotControllerPtr = new
      StokesRobotController( theHardwareSimulator,
			      HardwareSimulator::EVADING );
    break;
  default:
    evadingRobotControllerPtr = 0;
    break;
  }


  theHardwareSimulator.
    setPursuingRobotController( pursuingRobotControllerPtr );
  theHardwareSimulator.
    setEvadingRobotController( evadingRobotControllerPtr );
}

