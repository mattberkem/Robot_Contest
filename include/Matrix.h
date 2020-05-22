
#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
 public:
  Matrix( unsigned, unsigned );
  Matrix( const Matrix & );
  ~Matrix();
  double& operator() ( unsigned, unsigned );
  const double& operator() ( unsigned, unsigned ) const;
  const Matrix &operator=( const Matrix & );

 private:
  unsigned numRows, numCols;
  double* data;
};

#endif // MATRIX_H
