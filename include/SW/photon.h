#ifndef __PHOTON_H__
#define __PHOTON_H__

#include <SW/point.h>
#include <SW/color.h>

class SWphoton
{
 private:
  SWpoint _point;  // Where did I hit
  SWcolor _color;  // What color am I

 public:
  SWphoton( const SWpoint &, const SWcolor & );

  inline SWpoint point() const { return _point; }
  inline SWcolor color() const { return _color; }
};

#endif //__PHOTON_H__
