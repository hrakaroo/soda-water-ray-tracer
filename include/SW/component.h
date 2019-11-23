#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <SW/intersect.h>
#include <SW/list.h>
#include <SW/line.h>
#include <SW/except.h>
#include <SW/plane.h>

class SWcomponent
{
 public:
  virtual SWintersect intersect(const SWline &) = 0;
};

class SWsphere : public SWcomponent
{
 private:
  float _radius;

 public:
  SWsphere(float);
  SWintersect intersect(const SWline &);
};

class SWecone : public SWcomponent
{
 private:
  float _radiusX;
  float _radiusY;
  float _radiusZ;
  
 public:
  SWecone(float, float, float);
  SWintersect intersect(const SWline &);
};  

class SWmesh : public SWcomponent
{
 private:
  SWlist * _planes;

 public:
  SWmesh(SWlist *);
  SWintersect intersect(const SWline &);
};

#endif //__COMPONENT_H__
