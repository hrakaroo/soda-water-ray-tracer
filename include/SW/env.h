#ifndef __ENV_H__
#define __ENV_H__

#include <SW/intersect.h>
#include <SW/list.h>
#include <SW/line.h>
#include <SW/photon.h>
#include <SW/color.h>
#include <SW/camera.h>

#include <ANN/ANN.h>

class SWobject;

class SWenv
{
 private:
  SWlist     * _objects;
  SWlist     * _lights;
  SWcolor      _ambient;
  SWcamera     _camera;
  SWcolor      _background;
  float        _dimmer;
  float        _scaleX;
  float        _scaleY;
  int          _rayId;

  ANNidxArray    _index;
  ANNdistArray   _dists;
  ANNkd_tree   * _kdtree;
  ANNpoint       _query;

  SWphoton     ** _photons;
  int            _photonIndex;
  int            _photonSize;
  
 public:
  SWenv(int, int);
  ~SWenv();

  void loadEnv();
  void loadEnv( char * );
  void photonPass();

  SWcolor color(int, int);
  
  void mapPhotons();
  void mapPhoton( const SWline &, const SWcolor & );
  
  void buildKDTree();
  SWcolor intensity(const SWpoint &) const;

  SWobject * intersect(const SWline     &,
		       const SWobject   *,
		       bool              ,
		       SWintersect *
		       ) const;

  SWcolor color(const SWline   &,   // line
		int        ,  // recursion
		const SWobject *    // current obj
		)const;
  
  inline SWlist   * objects() const { return _objects;    }
  inline SWlist   * lights()  const { return _lights;     }
  inline float      dimmer()  const { return _dimmer;     }
  inline SWcolor    ambient() const { return _ambient;    }
  inline SWcamera   camera()  const { return _camera;     }
  inline int        rayId()   const { return _rayId;      }
  inline void       rayId(int value){ _rayId = value;     }
};

#endif //__ENV_H__
