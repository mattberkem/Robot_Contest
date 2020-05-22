
#include <cmath>
#include "PlayingField.h"

PlayingField::PlayingField( double bottom, double top,
			    double left, double right,
			    double springConstantDesired )
{
  bottomWallLocation = bottom;
  topWallLocation = top;
  leftWallLocation = left;
  rightWallLocation = right;

  if ( springConstantDesired > 0.0 )
    springConstant = springConstantDesired;
  else
    springConstant = -springConstantDesired;
}

PlayingField::~PlayingField()
{
}

double PlayingField::forceFromBottomWall( const Vector & x, double r )
{
  double restLength;

  restLength = bottomWallLocation + r;

  if ( x(2) < restLength )
    return -springConstant * ( x( 2 ) - restLength )*sin( x( 3 ) );
  else
    return 0.0;
}

double PlayingField::forceFromTopWall( const Vector & x, double r )
{
  double restLength;

  restLength = topWallLocation - r;

  if ( x(2) > restLength )
    return -springConstant*( x( 2 ) - restLength )*sin( x( 3 ) );
  else
    return 0.0;
}

double PlayingField::forceFromLeftWall( const Vector & x, double r )
{
  double restLength;

  restLength = leftWallLocation + r;

  if ( x(1) < restLength )
    return -springConstant*( x( 1 ) - restLength )*cos( x( 3 ) );
  else
    return 0.0;
}

double PlayingField::forceFromRightWall( const Vector & x, double r )
{
  double restLength;

  restLength = rightWallLocation - r;

  if ( x(1) > restLength )
    return -springConstant*( x( 1 ) - restLength )*cos( x( 3 ) );
  else
    return 0.0;
}

double PlayingField::getBottomWallLocation()
{
  return bottomWallLocation;
}

double PlayingField::getTopWallLocation()
{
  return topWallLocation;
}

double PlayingField::getLeftWallLocation()
{
  return leftWallLocation;
}

double PlayingField::getRightWallLocation()
{
  return rightWallLocation;
}

