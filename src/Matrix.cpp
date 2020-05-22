#include <cassert>
#include "Matrix.h"

Matrix::Matrix(unsigned rows, unsigned cols)
  : numRows (rows),
    numCols (cols),
    data ( new double [rows * cols] )
{}

Matrix::Matrix( const Matrix &init )
  : numRows( init.numRows ), numCols( init.numCols )
{
  data = new double [numRows * numCols];

  for( unsigned i = 0; i < numRows; i++ )
    for( unsigned j = 0; j < numCols; j++ )
      data[i*numCols + j] = init.data[i*numCols + j];
}

Matrix::~Matrix()
{
  delete [] data;
}

double& Matrix::operator() (unsigned row, unsigned col)
{
  assert( 0 < row && row <= numRows && 0 < col && col <= numCols );
  return data[ numCols*( row - 1 ) + col - 1 ];
}

const double& Matrix::operator() (unsigned row, unsigned col) const
{
  assert( 0 < row && row <= numRows && 0 < col && col <= numCols );
  return data[ numCols*( row - 1 ) + col - 1 ];
}

const Matrix &Matrix::operator=( const Matrix &right )
{
  if ( &right != this ) {
    if ( numRows != right.numRows || numCols != right.numCols ) {
      delete [] data;
      numRows = right.numRows;
      numCols = right.numCols;
      data = new double[ numRows * numCols ];
      assert( data != 0 );
    }
    for( unsigned i = 0; i < numRows; i++ )
      for( unsigned j = 0; j < numCols; j++ )
	data[i*numCols + j] = right.data[i*numCols + j];
  }
  return *this;
}
