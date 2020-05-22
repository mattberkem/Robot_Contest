#include <cassert>
#include "Vector.h"

Vector::Vector( unsigned elements )
  : numElements ( elements ),
    data ( new double [ elements ] )
{
  for ( unsigned i = 0; i < elements; i++ )
    data[ i ] = 0.0;
}

Vector::Vector( const Vector &init ) : numElements( init.numElements )
{
  data = new double[ numElements ];

  for( unsigned i = 0; i < numElements; i++ )
    data[i] = init.data[i];
}

Vector::~Vector()
{
  delete [] data;
}

double& Vector::operator() (unsigned element)
{
  assert( 0 < element && element <= numElements );
  return data[ element - 1 ];
}

const double& Vector::operator() (unsigned element) const
{
  assert( 0 < element && element <= numElements );
  return data[ element - 1 ];
}

const Vector &Vector::operator=( const Vector &right )
{
  if ( &right != this ) {
    if ( numElements != right.numElements ) {
      delete [] data;
      numElements = right.numElements;
      data = new double[ numElements ];
      assert( data != 0 );
    }
    for ( unsigned i = 0; i < numElements; i++ )
      data[ i ] = right.data[ i ];
  }
  return *this;
}
