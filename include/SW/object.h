#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <SW/material.h>
#include <SW/matrix.h>
#include <SW/rotation.h>
#include <SW/list.h>
#include <SW/component.h>
#include <SW/except.h>

class SWenv;
class SWmaterial;

class SWobject
{
 protected:
  const SWmatrix   * _obj2wld;
  const SWmatrix   * _wld2obj;
  const SWmaterial * _material;
  SWlist           * _components;
  SWlist           * _planes;


 public:
  SWobject(const SWmaterial *, const SWpoint &, const SWrotation &);

  ~SWobject();

  SWcolor color(const SWenv       *, 
		const SWline      &, 
		const SWintersect &, 
		int
		) const;
  
  inline void addComponent(SWcomponent * component)
    { _components->add(component); }

  inline void addPlane(SWplane * plane) 
    { _planes->add(plane); }

  inline float ks() const { return _material->ks() ; }
  inline float kd() const { return _material->kd() ; }
  inline float opaque() const { return _material->opaque() ; }

  inline bool isTransparent() const { return _material->isTransparent() ; }
  inline bool isReflective() const { return _material->isReflective() ; }

  SWintersect intersect(const SWline &) const;

  SWline enter( const SWline &, const SWintersect & ) const throw (noLeave);
  SWline leave( const SWline &, int, SWline * = NULL) const throw (noLeave);
  SWline bounce( const SWline &, const SWintersect & ) const;
};

#endif //__OBJECT_H__
