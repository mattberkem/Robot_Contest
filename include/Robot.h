
#ifndef ROBOT_H
#define ROBOT_H

#include "Vector.h"
#include "DynamicDevice.h"
#include "PlayingField.h"

class Robot : public DynamicDevice {

 public:
  Robot( Vector &, double, double, PlayingField &, double );
  ~Robot();
  void setEr( double );
  void setEl( double );
  double getEr() const;
  double getEl() const;
  double getRadius() const;
  virtual void odeModel( const double, const Vector &, Vector & );

  virtual void setState( Vector & );
  virtual Vector getState() const;

 private:
  double er, el;
  Vector state;
  double radius;
  PlayingField & walls;

};

#endif // ROBOT_H
