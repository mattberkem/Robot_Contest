
#ifndef VECTOR_H
#define VECTOR_H

class Vector {
 public:
  Vector( unsigned );
  Vector( const Vector & );
  ~Vector();
  const Vector &operator=( const Vector & );
  double& operator() ( unsigned );
  const double& operator() ( unsigned ) const;

 private:
  unsigned numElements;
  double* data;
};

#endif // VECTOR_H
