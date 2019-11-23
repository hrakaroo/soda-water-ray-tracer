#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <SW/env.h>
#include <SW/color.h>
#include <SW/line.h>

class SWline;
class SWenv;
class SWobject;

class SWmaterial
{
 private:
  bool    _conductive;
  bool    _reflective;
  float   _refraction;
  float   _opaque;
  SWcolor _color;

  float  _ks;
  float  _kd;
  float  _ns;
  float  _beta;
  
  float specular( const SWunitv &, 
		  const SWunitv &, 
		  const SWunitv & 
		  ) const;

 public:
  SWmaterial();
  SWmaterial( float        , // beta
	      bool         , // conductive
	      bool         , // reflective
	      SWcolor      , // color
	      float = 1.0f , // refraction
	      float = 1.0f   // opaqueness
	      );
  
  SWcolor externalColor( const SWenv       *,
			 const SWline      &,
			 const SWintersect &,
			 int         ,
			 const  SWobject   *
			 ) const;
  
  SWcolor internalColor(const SWenv    *,
			const SWline   &,
			int,
			const SWobject *
			) const;

  inline bool isTransparent() const { return _opaque != 1.0f; }
  inline bool isConductive()  const { return _conductive;  }
  inline bool isReflective()  const { return _reflective;  }
  inline float refraction()   const { return _refraction;  }
  inline float opaque()       const { return _opaque;      }
  inline float ks() const { return _ks; }
  inline float kd() const { return _kd; }
};

#endif //__MATERIAL_H__
