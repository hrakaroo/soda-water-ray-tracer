#ifndef __LINE_H__
#define __LINE_H__

#include <SW/point.h>
#include <SW/vector.h>

class SWline
{
 private:
  SWpoint _point;
  SWunitv _direction;

 public:
  SWline();
  SWline(const SWpoint &, const SWpoint &);
  SWline(const SWpoint &, const SWunitv &);

  inline SWpoint point()     const { return _point;     }
  inline SWunitv direction() const { return _direction; }
  SWunitv _perturb[9];
  inline SWunitv get(int i)        { return _perturb[i]; }

  friend SWpoint operator*(const SWline &, float);
  friend ostream& operator<<(ostream &, const SWline &);
  friend class SWplane;
};

#endif //__LINE_H__
