#ifndef __PLANE_H__
#define __PLANE_H__

#include <SW/vector.h>
#include <SW/except.h>
#include <SW/line.h>

class SWplane
{
 private:
  SWunitv _normal;
  float   _k;

 public:
  SWplane();
  SWplane(const SWunitv &, float);
  SWplane(float, float, float, float);

  inline SWunitv normal() const { return _normal; }
  inline float   k()      const { return _k;      }

  float intersect(const SWline &) const 
    throw(abovePlane, belowPlane);

  friend ostream& operator<<(ostream &, const SWplane &);
};

#endif //__PLANE_H__
