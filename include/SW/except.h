#ifndef __EXCEPT_H__
#define __EXCEPT_H__

class noIntersect
{
  int _value;
 public:
  noIntersect(){ _value = 0; }
  noIntersect( int value ) { _value = value; }
  int value() { return _value; }
};
class noTouch{};
class abovePlane{};
class belowPlane{};
class noLeave{};

#endif //__EXCEPT_H__
