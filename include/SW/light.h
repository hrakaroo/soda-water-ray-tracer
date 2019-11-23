#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <SW/color.h>
#include <SW/point.h>

class SWlight
{
 private:
  SWcolor  _color;
  SWpoint  _location;
  float    _power;

 public:
  SWlight(const SWcolor &, const SWpoint &, float );
  
  inline SWcolor color()    const { return _color;    }
  inline SWpoint location() const { return _location; }
  inline float   power()    const { return _power;    }
};

#endif //__LIGHT_H__
