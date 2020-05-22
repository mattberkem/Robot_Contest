#ifndef INTERACTING_ROBOTS_H
#define INTERACTING_ROBOTS_H

#include "Vector.h"
#include "DynamicDevice.h"
#include "Robot.h"

class InteractingRobots : public DynamicDevice {

 public:
  InteractingRobots( Robot &, Robot &, double );
  ~InteractingRobots();
  virtual void odeModel( const double, const Vector &, Vector & );
  virtual void setState( Vector & );
  virtual Vector getState() const;
  bool getCollisionOccurred();
  void resetCollisionOccurred();

 private:
  Robot & pursuingRobot;
  Robot & evadingRobot;
  double springConstant;
  void applyCollisionForces( const Vector &, Vector & );
  bool collisionOccurred;


};

#endif // INTERACTING_ROBOTS_H
