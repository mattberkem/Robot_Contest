#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <math.h>
#include "nrutil.h"
#include "Vector.h"
#include "Matrix.h"
#include "DynamicDevice.h"

const int MAXSTP = 10000;
const double TINY = 1.0e-30;

const double SAFETY = 0.9;
const double PGROW = -0.2;
const double PSHRNK = -0.25;
const double ERRCON = 1.89e-4;


/*
  The value ERRCON equals (5/SAFETY) raised to the power (1/PGROW), see
  use below.
*/

class Integrator {

 public:
  Integrator( DynamicDevice &, int, double, double, double, double );
  ~Integrator();
  void setState();
  void odeint( double, double );

 private:
  int kmax, kount, nvar;
  int *nok, *nbad;
  double eps, h1, hmin;
  Vector *xp;
  Matrix *yp;
  double dxsav;
  Vector ystart;
  DynamicDevice & device;
  void rkck( Vector &, Vector &, double, double, Vector &,
  	     Vector &, DynamicDevice &);
  void rkqs( Vector &, Vector &, double *, double,
  	     Vector &, double *, double *,
  	     DynamicDevice &);


};

#endif // INTEGRATOR_H
