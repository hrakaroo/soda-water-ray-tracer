#include <SW/color.h>
#include <math.h>

SWcolor::SWcolor()
{
  // Init to black
  _red = _green = _blue = 0.0f;
}

SWcolor::SWcolor(float red, float green, float blue)
{
  _red   = red;
  _green = green;
  _blue  = blue;
}

int SWcolor::redInt()
{
  int _redInt = (int)(_red*255.0f);
  return _redInt > 255 ? 255 : _redInt;
}

int SWcolor::greenInt()
{
  int _greenInt = (int)(_green*255.0f);
  return _greenInt > 255 ? 255 : _greenInt;
}

int SWcolor::blueInt()
{
  int _blueInt = (int)(_blue*255.0f);
  return _blueInt > 255 ? 255 : _blueInt;
}

ostream & operator<<(ostream & os, const SWcolor & color)
{
  return os << "red : " << color._red 
	    << " green : " << color._green
	    << " blue : " << color._blue;
}

SWcolor & SWcolor::operator+=(const SWcolor & color)
{
  _red   += color._red;
  _green += color._green;
  _blue  += color._blue;

  return *this;
}


SWcolor & SWcolor::operator*=(const SWcolor & color)
{
  _red   *= color._red;
  _green *= color._green;
  _blue  *= color._blue;

  return *this;
}

SWcolor & SWcolor::operator/=( float scale )
{
  _red   /= scale;
  _green /= scale;
  _blue  /= scale;

  return *this;
}

SWcolor operator*(const SWcolor & color, float scale)
{
  float ascale = fabs(scale);
  return SWcolor( color._red   * ascale,
		  color._green * ascale,
		  color._blue  * ascale );
}

SWcolor operator/(const SWcolor & color, float scale)
{
  float ascale = fabs(scale);
  return SWcolor( color._red   / ascale,
		  color._green / ascale,
		  color._blue  / ascale );
}

SWcolor operator*(const SWcolor & color1, const SWcolor & color2)
{
  return SWcolor( color1._red   * color2._red,
		  color1._green * color2._green,
		  color1._blue  * color2._blue );
}

SWcolor operator+(const SWcolor & color1, const SWcolor & color2)
{
  return SWcolor( color1._red   + color2._red,
		  color1._green + color2._green,
		  color1._blue  + color2._blue );
}

