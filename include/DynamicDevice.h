
#ifndef DYNAMIC_DEVICE_H
#define DYNAMIC_DEVICE_H

#include "Vector.h"

class DynamicDevice {

 public:
  virtual void odeModel( const double, const Vector &, Vector & ) = 0;
  virtual void setState( Vector & ) = 0;
  virtual Vector getState() const = 0;

  int numStates;
};

#endif // DYNAMIC_DEVICE_H
