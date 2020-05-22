
#include <cmath>
#include "InteractingRobots.h"

InteractingRobots::InteractingRobots( Robot & Robot1, Robot & Robot2,
				      double springConstantDesired )
  : pursuingRobot( Robot1 ), evadingRobot( Robot2 ), collisionOccurred( false )
{
  numStates = Robot1.numStates + Robot2.numStates;
  if ( springConstantDesired > 0.0 )
    springConstant = springConstantDesired;
  else
    springConstant = -springConstantDesired;
}

InteractingRobots::~InteractingRobots()
{
}

void InteractingRobots::odeModel( const double t, const Vector & x,
				  Vector & xdot)
{
  int n = pursuingRobot.numStates;

  Vector tempXDot( n );
  Vector tempX( n );

  for ( int i = 1; i <= n; i++ )
    tempX( i ) = x( i );

  pursuingRobot.odeModel( t, tempX, tempXDot );

  for ( int i = 1; i <= n; i++ )
    xdot( i ) = tempXDot( i );
  
  for ( int i = 1; i <= n; i++ )
    tempX( i ) = x( i + n );

  evadingRobot.odeModel( t, tempX, tempXDot );

  for ( int i = 1; i <= n; i++ )
    xdot( i + n ) = tempXDot( i );

  applyCollisionForces( x, xdot );


}

Vector InteractingRobots::getState() const
{
  int n = pursuingRobot.numStates;

  Vector temp1( n );
  Vector temp2( 2 * n );

  temp1 = pursuingRobot.getState();

  for ( int i = 1; i <= n; i++ )
    temp2( i ) = temp1( i );

  temp1 = evadingRobot.getState();

  for ( int i = 1; i <= n; i++ )
    temp2( i + 5 ) = temp1( i );

  return temp2;
}

void InteractingRobots::setState( Vector & x )
{
  int n = pursuingRobot.numStates;

  Vector temp( n );

  for( int i = 1; i <= n; i++ )
    temp( i ) = x( i );

  pursuingRobot.setState( temp );

  for( int i = 1; i <= n; i++ )
    temp( i ) = x( i + n );

  evadingRobot.setState( temp );


}

void InteractingRobots::applyCollisionForces( const Vector & x, Vector & xdot )
{
  // Here, we provide repelling forces in case the robots collide

  double separation, penetration;

  separation = sqrt( ( x(1) - x(6) ) * ( x(1) - x(6) ) +
		     ( x(2) - x(7) ) * ( x(2) - x(7) )   );

  penetration = pursuingRobot.getRadius() + evadingRobot.getRadius() -
                separation;
  
  if ( penetration > 0.0 ) {
    xdot(4) += springConstant *
      ( ( x(1) - x(6) ) * cos( x(3) ) +
	( x(2) - x(7) ) * sin( x(3) )   ) * penetration / 2.0;
    
    xdot(9) += springConstant *
      ( ( x(6) - x(1) ) * cos( x(8) ) +
	( x(7) - x(2) ) * sin( x(8) )   ) * penetration / 2.0;

    collisionOccurred = true;
  }
}

bool InteractingRobots::getCollisionOccurred()
{
  return collisionOccurred;
}

void InteractingRobots::resetCollisionOccurred()
{
  collisionOccurred = false;
}
