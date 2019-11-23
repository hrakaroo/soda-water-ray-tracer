#include <SW/vector.h>
#include <SW/matrix.h>

#include <assert.h>
#include <math.h>
#include <iostream.h>

SWvector::SWvector()
{
  _x = _y = _z = 0.0f;
}

SWvector::SWvector(float x, float y, float z)
{
  _x = x;
  _y = y;
  _z = z;
}

SWvector::SWvector(const SWpoint & point)
{
  _x = point._x;
  _y = point._y;
  _z = point._z;
}

SWvector::SWvector(const SWpoint & point1, const SWpoint & point2)
{ 
  _x = point2._x - point1._x;
  _y = point2._y - point1._y;
  _z = point2._z - point1._z;
}

float SWvector::length()
{
  return sqrtf(_x*_x + _y*_y + _z*_z);
}

ostream& operator<<(ostream & os, const SWvector & vector)
{
  return os << "SWvector: (" 
	    << vector._x << ", " 
	    << vector._y << ", " 
	    << vector._z << ")";
}

float operator*(const SWvector & vector1, const SWvector & vector2)
{
  return (vector1._x*vector2._x + 
	  vector1._y*vector2._y + 
	  vector1._z*vector2._z);
}

SWvector operator+(const SWvector & vector1, const SWvector & vector2)
{
  return SWvector(vector1._x + vector2._x, 
		  vector1._y + vector2._y, 
		  vector1._z + vector2._z);
}

SWvector operator-(const SWvector & vector1, const SWvector & vector2)
{
  return SWvector(vector1._x - vector2._x, 
		  vector1._y - vector2._y, 
		  vector1._z - vector2._z);
}

SWvector operator*(const SWvector & vector, float scale)
{
  return SWvector(vector._x*scale,
		  vector._y*scale,
		  vector._z*scale);
}		  

SWvector operator-(const SWvector & vector)
{
  return SWvector( - vector._x,
		   - vector._y,
		   - vector._z);
}

/*********** SWunitv ***********/

SWunitv::SWunitv() :
  SWvector()
{}

SWunitv::SWunitv(float x, float y, float z) :
  SWvector(x, y, z)
{
  normalize();
}

SWunitv::SWunitv(const SWpoint & point1, const SWpoint & point2) :
  SWvector(point1, point2)
{
  normalize();
}

SWunitv::SWunitv(const SWvector & vector) :
  SWvector(vector)
{
  normalize();
}

void SWunitv::normalize()
{
  float length = sqrtf(_x*_x + _y*_y + _z*_z);
  
  if( length == 0.0f )
    return;
  
  _x /= length;
  _y /= length;
  _z /= length;
}

SWcross SWunitv::cross()
{
  float sin_plan;
  float cos_plan;
  float cos_elev;
  float sin_elev = _y;
  
  if( _x == 0.0f && _z == 0.0f )
    {
      sin_plan = 0.0f;
      cos_plan = 1.0f;
      cos_elev = 0.0f;
    }
  else
    {
      float root = sqrtf(_x*_x + _z*_z);
      sin_plan =   _x / root;
      cos_plan = - _z / root;
      cos_elev = root;
    }

  float data[] = { cos_plan,             0.0f,     sin_plan,           0.0f ,
		   -sin_plan * sin_elev, cos_elev, cos_plan *sin_elev, 0.0f,
		   sin_plan*cos_elev,    sin_elev, cos_plan*cos_elev,  0.0f,
		   0.0f,                 0.0f,     0.0f,               1.0f };
  SWmatrix trans( 4, 4, data);

  SWunitv up   = SWunitv(0, 1, 0) * trans;
  SWunitv side = SWunitv(1, 0, 0) * trans;

  return SWcross(up, side);
}

SWunitv & SWunitv::operator=(const SWvector & vector)
{
  _x = vector._x;
  _y = vector._y;
  _z = vector._z;
  normalize();

  return *this;
}

SWunitv operator-(const SWunitv & unitv)
{
  return SWunitv( - unitv._x,
		  - unitv._y,
		  - unitv._z);
}


/*********** SWcross ***********/

SWcross::SWcross(const SWunitv & up, const SWunitv & side)
{
  _up = up;
  _side = side;
}
