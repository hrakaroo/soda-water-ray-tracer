#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream.h>

#include <SW/point.h>
#include <SW/vector.h>
#include <SW/line.h>

class SWmatrix
{
 private:
  int _cols;
  int _rows;

  float * _matrix;

 public:
  SWmatrix(unsigned int, unsigned int, const float *);
  SWmatrix(unsigned int, unsigned int);
  SWmatrix(const SWmatrix &);
  SWmatrix(const SWpoint &);
  SWmatrix(const SWvector &);
  SWmatrix(const SWline  &);
  ~SWmatrix();

  void  set( unsigned int, unsigned int, float );

  float get( unsigned int, unsigned int ) const;
  SWmatrix invert() const;

  SWmatrix & operator=(const SWmatrix & matrix);

  friend ostream& operator<<(ostream &, const SWmatrix &);
  friend SWmatrix  operator*(const SWmatrix &, const SWmatrix &);
  friend SWpoint  operator*(const SWpoint &, const SWmatrix &); 
  friend SWvector operator*(const SWvector &, const SWmatrix &); 
  friend SWline   operator*(const SWline  &, const SWmatrix &); 

  static SWmatrix rotX( float );
  static SWmatrix rotY( float );
  static SWmatrix rotZ( float );
  
};

#endif //__MATRIX_H__
