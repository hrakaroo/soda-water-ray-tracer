#include <SW/point.h>
#include <math.h>

SWpoint::SWpoint()
{
  _x = _y = _z = 0.0f;
}

SWpoint::SWpoint(float x, float y, float z)
{
  _x = x;
  _y = y;
  _z = z;
}


ostream & operator<<(ostream & os, const SWpoint & point)
{
  return os << "SWpoint: (" 
	    << point._x << ", " 
	    << point._y << ", " 
	    << point._z << ")";
}

float operator-(const SWpoint & point1, const SWpoint & point2)
{
  float x = point2._x - point1._x;
  float y = point2._y - point1._y;
  float z = point2._z - point1._z;
  return sqrtf( x*x + y*y + z*z );
}

SWpoint operator+(const SWpoint & point, const SWvector & vector)
{
  return SWpoint( point._x + vector._x,
		  point._y + vector._y,
		  point._z + vector._z );
}

SWpoint operator-(const SWpoint & point, const SWvector & vector)
{
  return SWpoint( point._x - vector._x,
		  point._y - vector._y,
		  point._z - vector._z );
}
