#ifndef PLAYING_FIELD_H
#define PLAYING_FIELD_H

#include "Vector.h"

class PlayingField{

 public:
  PlayingField( double, double, double, double, double );
  ~PlayingField();
  double forceFromBottomWall( const Vector &, double );
  double forceFromTopWall( const Vector &, double );
  double forceFromLeftWall( const Vector &, double );
  double forceFromRightWall( const Vector &, double );
  double getBottomWallLocation();
  double getTopWallLocation();
  double getLeftWallLocation();
  double getRightWallLocation();

 private:
  double bottomWallLocation;
  double topWallLocation;
  double leftWallLocation;
  double rightWallLocation;
  double springConstant;

};

#endif // PLAYING_FIELD_H
