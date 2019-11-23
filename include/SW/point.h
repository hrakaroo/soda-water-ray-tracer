#ifndef __POINT_H__
#define __POINT_H__

#include <iostream.h>
#include "vector.h"

class SWvector;

class SWpoint
{
 private:
  float _x;
  float _y;
  float _z;
  
 public:
  SWpoint();
  SWpoint(float, float, float);

  // inline
  inline float x() const { return _x; }
  inline float y() const { return _y; }
  inline float z() const { return _z; } 

  // operator overload
  friend ostream& operator<<(ostream &, const SWpoint &);
  friend float    operator-(const SWpoint &, const SWpoint &);
  friend SWpoint  operator+(const SWpoint &, const SWvector &);
  friend SWpoint  operator-(const SWpoint &, const SWvector &);

  // friend classes
  friend class SWvector;
  friend class SWplane;
};

#endif //__POINT_H__
