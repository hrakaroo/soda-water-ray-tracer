#ifndef __COLOR_H__
#define __COLOR_H__

#include <iostream.h>

class SWcolor
{
 private:
  float _red;
  float _green;
  float _blue;

 public:
  SWcolor();
  SWcolor(float, float, float);

  inline float red()  { return _red;   }
  inline float green(){ return _green; }
  inline float blue() { return _blue;  }

  int redInt();
  int greenInt();
  int blueInt();

  SWcolor & operator+=(const SWcolor &);
  SWcolor & operator*=(const SWcolor &);
  SWcolor & operator/=( float );

  friend ostream & operator<<(ostream &, const SWcolor &);
  //  friend bool operator==(const SWcolor &, const SWcolor &);

  friend SWcolor operator*(const SWcolor &, float);
  friend SWcolor operator/(const SWcolor &, float);
  friend SWcolor operator*(const SWcolor &, const SWcolor &);
  friend SWcolor operator+(const SWcolor &, const SWcolor &);
};

#endif
