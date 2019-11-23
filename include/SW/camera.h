#ifndef __CAMERA_H__
#define __CAMERA_H__
 
#include <SW/point.h>
#include <SW/vector.h>
 
class SWcamera
{
 protected:
  // set data
  SWpoint _target;    // Aimed to where
  float   _distance;  // Distance from orgin
  float   _width;     //
  float   _plan;      //
  float   _elevation;
  float   _roll;
 
  // derived data
  float   _height;
  SWpoint _upperLeft;
  SWunitv _up;
  SWunitv _side;
  SWunitv _look;
 
  // private functions
  void initVectors();
  void setUpperLeft();
 
 public:
  SWcamera();
  SWcamera(const SWpoint &,
           float,
           float,
           float = 0.0f,
           float = 0.0f,
           float = 0.0f);
 
  void    height( float );
  SWpoint eye() const;
 
  inline SWpoint target()    const { return _target; }
  inline float   width()     const { return _width; }
  inline float   height()    const { return _height; }
  inline SWunitv up()        const { return _up; }
  inline SWunitv side()      const { return _side; }
  inline SWunitv look()      const { return _look; }
  inline SWpoint upperLeft() const { return _upperLeft; }
};
 
#endif //__CAMERA_H__
