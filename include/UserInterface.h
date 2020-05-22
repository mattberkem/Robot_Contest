
#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "Vector.h"
#include "HardwareSimulator.h"

// GHOST type was added to allow for erasing the robots
enum RobotType { PURSUING = 0, EVADING = 1, GHOST };

class UserInterface {

 public:
  UserInterface( HardwareSimulator & );
  ~UserInterface();
  void printGraphics();
  void printStatus();
  void printMenu();
  char processUserResponse();
  int getPursuerNumber();
  int getEvaderNumber();
  void setPursuerNumber( int );
  void setEvaderNumber( int );

 private:
  HardwareSimulator & theHardwareSimulator;
  void getRobotStates();
  void writeFieldBorder();
  void writeRobotFromState( RobotType );
  void writeRobotFromIndex( short, short, RobotType );
  void eraseRobots();
  void setPursuingRobotState();
  void setEvadingRobotState();
  Vector getUserStateInput();
  void incrementSimulationTime();
  void resetSimulation();
  bool userStateInputBad( double, int );
  //  double nearestInteger( double );
  void displayProcessorState();
  void changePlayers();
  void showCurrentPlayers();
  void showListOfPlayers();
  char screenBuffer[ 18 ][ 63 ];
  short lastRobotLocations[ 2 ][ 2 ];
  Vector pursuingRobotState;
  Vector evadingRobotState;
  bool firstCollisionNotOccurred;
  int pursuerNumber;
  int evaderNumber;

};

#endif // USER_INTERFACE_H


