#include <SW/except.h>
#include <SW/plane.h>

#include <math.h>

SWplane::SWplane()
{}

SWplane::SWplane(const SWunitv & normal, float k)
{
  _normal = normal;
  _k      = k;
}

SWplane::SWplane(float x, float y, float z, float k)
{
  float length = sqrtf(x*x + y*y + z*z);
  _normal = SWunitv(x, y, z);
  _k      = k/length;
}

ostream& operator<<(ostream & os, const SWplane & plane)
{
  return os << "SWplane: " << endl 
	    << "\tnormal: " << plane._normal << endl
	    << "\tk     : " << plane._k << endl;
}

float SWplane::intersect(const SWline & line) const 
  throw(abovePlane, belowPlane)
{
  // line equation  : p = p1 + u * dir
  // plane equation : p * normal - k = 0
  // u = (k - p1*normal)/(dir * normal)

  // remember! k is negative so final equation is actually
  // u = (- k - p1*normal)/(dir * normal)

  // angle = - dir * normal

  //cout << "SWplane::intersect()" << endl;

  float num = _k -  (_normal._x * line._point._x +
		     _normal._y * line._point._y +
		     _normal._z * line._point._z);

  float den = line._direction * _normal;

  if( den == 0.0f )  // runs parallel to plane
    if( num < 0 )
      throw abovePlane();
    else
      throw belowPlane();
  
  // distance to plane
  float u = num / den;

  return u;
}
