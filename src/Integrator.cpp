
#include <cmath>
#include "DynamicDevice.h"
#include "Integrator.h"

Integrator::Integrator( DynamicDevice & deviceDesired,
			int kmaxDesired,
			double dxsavDesired,
			double epsDesired, double h1Desired,
			double hminDesired )
  : device( deviceDesired ),
    kmax( kmaxDesired ), dxsav( dxsavDesired ),
    nvar( deviceDesired.numStates  ),
    eps( epsDesired ), h1( h1Desired ), hmin( hminDesired ),
    ystart( deviceDesired.numStates )
{
  xp = new Vector( kmax );
  yp = new Matrix( deviceDesired.numStates, kmax );
  nok = new int;
  nbad = new int;
  ystart = deviceDesired.getState();
}

Integrator::~Integrator()
{
  delete xp;
  delete yp;
  delete nok;
  delete nbad;
}

//void Integrator::odeint( Vector & ystart, float x1, float x2,
//			 float eps, float h1, float hmin, int *nok, int *nbad,
//			 void (*derivs)(float, const Vector &, Vector &) )
void Integrator::odeint( double x1, double x2 )

/*
  Runge-Kutta driver with adaptive stepsize control. Integrate starting
  values ystart[1..nvar] from x1 to x2 with accuracy eps, storing
  intermediate results in global variables. h1 should be set as a
  guessed first stepsize, hmin as the minimum allowed stepsize (can be
  zero). On output nok and nbad are the number of good and bad (but
  retried and fixed) steps taken, and ystart is replaced by values at the
  end of the integration interval. derivs is the user-supplied routine
  for calculating the right-hand side derivative, while rkqs is the name
  of the stepper routine to be used.
*/

{
  int nstp,i;
  double xsav,x,hnext,hdid,h;
  Vector yscal( nvar );
  Vector y( nvar );
  Vector dydx( nvar );

  //yscal=vector(1,nvar);
  //y=vector(1,nvar);
  //dydx=vector(1,nvar);
  x=x1;
  h= SIGN(h1,x2-x1);
  *nok = (*nbad) = kount = 0;
  for (i=1;i<=nvar;i++) y( i ) = ystart( i );
  /* Assures storage of first step. */
  if (kmax > 0) xsav=x-dxsav*2.0;
  /* Take at most MAXSTP steps. */
  for (nstp=1;nstp<=MAXSTP;nstp++) {
    //(*derivs)(x,y,dydx);
    device.odeModel(x,y,dydx);
    for (i=1;i<=nvar;i++)
      /*
	Scaling used to monitor accuracy. This general-purpose choice can
	be modified if need be.
      */
      // Note: as the Numerical Recipes authors state, the following
      // does not work well near "zero crossings." For this reason, I
      // have commented it out and replaced it with "yscal( i ) = 1.0;"
      // Read the discussion in Numerical Recipes for more information.
      // yscal( i ) = fabs( y( i ) )+fabs(dydx( i )*h)+TINY;
      yscal( i ) = 1.0;
    if (kmax > 0 && kount < kmax-1 && fabs(x-xsav) > fabs(dxsav)) {
      (*xp)( ++kount ) = x;
      /* Store intermediate results. */
      for (i=1;i<=nvar;i++) (*yp)( i, kount ) = y( i );
      xsav=x;
    }
    /* If stepsize can overshoot, decrease. */
    if ((x+h-x2)*(x+h-x1) > 0.0) h=x2-x;
    //    rkqs(y,dydx,nvar,&x,h,eps,yscal,&hdid,&hnext,derivs);
    rkqs(y,dydx,&x,h,yscal,&hdid,&hnext,device);
    if (hdid == h) ++(*nok); else ++(*nbad);
    /* Are we done? */
    if ((x-x2)*(x2-x1) >= 0.0) {
      for (i=1;i<=nvar;i++) ystart( i ) = y( i );
      if (kmax) {
	(*xp)( ++kount ) = x;
	/* Save final step. */
	for (i=1;i<=nvar;i++) (*yp)( i, kount ) = y( i );
      }
      device.setState( ystart );
      //free_vector(dydx,1,nvar);
      //free_vector(y,1,nvar);
      //free_vector(yscal,1,nvar);
      /* Normal exit. */
      return;
    }
    if (fabs(hnext) <= hmin) nrerror("Step size too small in odeint");
    h=hnext;
  }
  nrerror("Too many steps in routine odeint");
}

//void Integrator::rkck(Vector y, Vector dydx, int n, float x,
//		      float h, Vector & yout,
//		      Vector & yerr,
//		      void (*derivs)(float, const Vector &, Vector &))

void Integrator::rkck(Vector & y, Vector & dydx, double x,
		      double h, Vector & yout,
		      Vector & yerr,
		      DynamicDevice & device)

/*
  Given values for n variables y[1..n] and their derivatives
  dydx[1..n] known at x, use the fifth-order Cash-Karp Runge-Kutta method
  to advance the solution over an interval h and return the incremented
  variables as yout[1..n]. Also return an estimate of the local
  truncation error in yout using the embedded fourth-order method. The
  user supplies the routine derivs(x,y,dydx), which returns derivatives
  dydx at x.
*/

{
  int i;

  static double a2=0.2,a3=0.3,a4=0.6,a5=1.0,a6=0.875,b21=0.2,
    b31=3.0/40.0,b32=9.0/40.0,b41=0.3,b42 = -0.9,b43=1.2,
    b51 = -11.0/54.0, b52=2.5,b53 = -70.0/27.0,b54=35.0/27.0,
    b61=1631.0/55296.0,b62=175.0/512.0,b63=575.0/13824.0,
    b64=44275.0/110592.0,b65=253.0/4096.0,c1=37.0/378.0,
    c3=250.0/621.0,c4=125.0/594.0,c6=512.0/1771.0,
    dc5 = -277.00/14336.0;
  double dc1=c1-2825.0/27648.0,dc3=c3-18575.0/48384.0,
    dc4=c4-13525.0/55296.0,dc6=c6-0.25;
  Vector ak2( nvar );
  Vector ak3( nvar );
  Vector ak4( nvar );
  Vector ak5( nvar );
  Vector ak6( nvar );
  Vector ytemp( nvar );

  //ak2=vector(1,n);
  //ak3=vector(1,n);
  //ak4=vector(1,n);
  //ak5=vector(1,n);
  //ak6=vector(1,n);
  //ytemp=vector(1,n);
  /* First step. */
  for (i=1;i<=nvar;i++)
    ytemp(i)=y(i)+b21*h*dydx(i);
  /* Second step. */
  //  (*derivs)(x+a2*h,ytemp,ak2);
  device.odeModel(x+a2*h,ytemp,ak2);
  for (i=1;i<=nvar;i++)
    ytemp(i)=y(i)+h*(b31*dydx(i)+b32*ak2(i));
  /* Third step. */
  //  (*derivs)(x+a3*h,ytemp,ak3);
  device.odeModel(x+a3*h,ytemp,ak3);
  for (i=1;i<=nvar;i++)
    ytemp(i)=y(i)+h*(b41*dydx(i)+b42*ak2(i)+b43*ak3(i));
  /* Fourth step. */
  //  (*derivs)(x+a4*h,ytemp,ak4);
  device.odeModel(x+a4*h,ytemp,ak4);
  for (i=1;i<=nvar;i++)
    ytemp(i)=y(i)+h*(b51*dydx(i)+b52*ak2(i)+b53*ak3(i)+b54*ak4(i));
  /* Fifth step. */
  //  (*derivs)(x+a5*h,ytemp,ak5);
  device.odeModel(x+a5*h,ytemp,ak5);
  for (i=1;i<=nvar;i++)
    ytemp(i)=y(i)+h*(b61*dydx(i)+b62*ak2(i)+b63*ak3(i)+
		     b64*ak4(i)+b65*ak5(i));
  /* Sixth step. */
  //  (*derivs)(x+a6*h,ytemp,ak6);
  device.odeModel(x+a6*h,ytemp,ak6);
  for (i=1;i<=nvar;i++)
    /* Accumulate increments with proper weights. */
    yout(i)=y(i)+h*(c1*dydx(i)+c3*ak3(i)+c4*ak4(i)+c6*ak6(i));
  for (i=1;i<=nvar;i++)
    yerr(i)=h*(dc1*dydx(i)+dc3*ak3(i)+dc4*ak4(i)+dc5*ak5(i)+dc6*ak6(i));
  /* Estimate error as difference between fourth and fifth order methods. */
  //free_vector(ytemp,1,n);
  //free_vector(ak6,1,n);
  //free_vector(ak5,1,n);
  //free_vector(ak4,1,n);
  //free_vector(ak3,1,n);
  //free_vector(ak2,1,n);
}

//void Integrator::rkqs(Vector & y, Vector dydx, int n, float *x,
//		      float htry, float eps,
//		      Vector yscal, float *hdid, float *hnext,
//		      void (*derivs)(float, const Vector &, Vector &))
void Integrator::rkqs(Vector & y, Vector & dydx, double *x,
		      double htry,
		      Vector & yscal, double *hdid, double *hnext,
		      DynamicDevice & device)

     /*
       Fifth-order Runge-Kutta step with monitoring of local truncation error
       to ensure accuracy and adjust stepsize. Input are the dependent
       variable vector y[1..n] and its derivative dydx[1..n] at the starting
       value of the independent variable x. Also input are the stepsize to be
       attempted htry, the required accuracy eps, and the vector yscal[1..n]
       against which the error is scaled. On output, y and x are replaced by
       their new values, hdid is the stepsize that was actually accomplished,
       and hnext is the estimated next stepsize. derivs is the user-supplied
       routine that computes the right-hand side derivatives.
     */

{
  int i;
  double errmax,h,htemp,xnew;

  //yerr=vector(1,n);
  //ytemp=vector(1,n);
  Vector yerr( nvar );
  Vector ytemp( nvar );
  /* Set stepsize to the initial trial value. */
  h=htry;
  for (;;) {
    /* Take a step. */
    //    rkck(y,dydx,n,*x,h,ytemp,yerr,derivs);
    rkck(y,dydx,*x,h,ytemp,yerr,device);
    /* Evaluate accuracy. */
    errmax=0.0;
    for (i=1;i<=nvar;i++) errmax=DMAX(errmax,fabs(yerr( i )/yscal( i )));
    /* Scale relative to required tolerance. */
    errmax /= eps;
    /* Step succeeded. Compute size of next step. */
    if (errmax <= 1.0) break;
    htemp=SAFETY*h*pow(errmax,PSHRNK);
    /* Truncation error too large, reduce stepsize. */
    h=(h >= 0.0 ? DMAX(htemp,0.1*h) : DMIN(htemp,0.1*h));
    /* No more than a factor of 10. */
    xnew=(*x)+h;
    if (xnew == *x) nrerror("stepsize underflow in rkqs");
  }
  if (errmax > ERRCON) *hnext=SAFETY*h*pow(errmax,PGROW);
  /* No more than a factor of 5 increase. */
  else *hnext=5.0*h;
  *x += (*hdid=h);
  for (i=1;i<=nvar;i++) y( i )=ytemp( i );
  //free_vector(ytemp,1,n);
  //free_vector(yerr,1,n);
}

void Integrator::setState()
{
  ystart = device.getState();
}
