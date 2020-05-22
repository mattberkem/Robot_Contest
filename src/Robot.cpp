
#include <cmath>
#include "Robot.h"

Robot::Robot( Vector & x, double er, double el, PlayingField & field,
	      double radiusDesired )
  : state( 5 ), walls( field )
{
  numStates = 5;
  setEr( er );
  setEl( el );
  setState( x );

  if ( radiusDesired > 0.0 )
    radius = radiusDesired;
  else
    radius = -radiusDesired;
}

Robot::~Robot()
{
}

// This is the robot ODE (Ordinary Differential Equation) model.
void Robot::odeModel( const double t, const Vector & x, Vector & xdot )
{
  xdot( 1 ) = x( 4 ) * cos( x( 3 ) );
  xdot( 2 ) = x( 4 ) * sin( x( 3 ) );
  xdot( 3 ) = x( 5 );
  xdot( 4 ) = -3.2 * x( 4 ) + 0.37 * ( er + el );
  xdot( 5 ) = -5.1 * x( 5 ) + 8.4 * ( er - el );

  xdot( 4 ) += walls.forceFromBottomWall( x, radius );
  xdot( 4 ) += walls.forceFromTopWall( x, radius );
  xdot( 4 ) += walls.forceFromLeftWall( x, radius );
  xdot( 4 ) += walls.forceFromRightWall( x, radius );

}

void Robot::setEr( double val )
{
  if ( -10.0 <= val && val <= 10.0 )
    er = val;
  else
    er = 0.0;
}

void Robot::setEl( double val )
{
  if ( -10.0 <= val && val <= 10.0 )
    el = val;
  else
    el = 0.0;
}

double Robot::getEl() const
{
  return el;
}

double Robot::getEr() const
{
  return er;
}

void Robot::setState( Vector & x )
{
  state = x;
}

Vector Robot::getState() const
{
  return state;
}

double Robot::getRadius() const
{
  return radius;
}
