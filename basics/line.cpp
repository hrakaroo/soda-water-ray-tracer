#include <SW/line.h>

SWline::SWline()
{ 
}

SWline::SWline(const SWpoint & point1, const SWpoint & point2)
{
  _point     = point1;
  _direction = SWunitv(point1, point2);
}

SWline::SWline(const SWpoint & point, const SWunitv & direction)
{
  _point     = point;
  _direction = direction;
}


SWpoint operator*(const SWline & line, float scale)
{
  return line._point + line._direction * scale;
}

ostream& operator<<(ostream & os, const SWline & line)
{
  return os << "SWline: " << endl
	    << "\tpoint     = " << line._point     << endl
	    << "\tdirection = " << line._direction << endl;
}


