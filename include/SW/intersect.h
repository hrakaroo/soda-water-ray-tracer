#ifndef __INTERSECT_H__
#define __INTERSECT_H__

#include <SW/vector.h>

class SWintersect
{
 private:
  bool    _contact;
  float   _inDistance;
  SWunitv _inNormal;
  bool    _inSet;
  float   _outDistance;
  SWunitv _outNormal;
  bool    _outSet;

 public:
  SWintersect();
  SWintersect( float, const SWunitv &, float, const SWunitv &);

  void in( float, const SWunitv &);
  void out( float, const SWunitv &);

  inline bool    contact()     const { return _contact;     }

  inline bool    inSet()       const { return _inSet;       }
  inline bool    outSet()      const { return _outSet;      }

  float   inDistance()  const;
  SWunitv inNormal()    const;

  float   outDistance() const;
  SWunitv outNormal()   const;
};
  

#endif //__INTERSECT_H__
