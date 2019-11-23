#include <SW/env.h>
#include <SW/object.h>
#include <SW/component.h>
#include <SW/plane.h>
#include <SW/light.h>
#include <SW/photon.h>
#include <SW/vector.h>
#include <SW/rotation.h>

#include <math.h>
#include <assert.h>

#define PI 3.1415
#define ANNSAMPLE 40

#define WALLOBJ    true
#define DIAMONDOBJ false
#define SPHEREOBJ  true
#define BASEOBJ    true
#define ECONEOBJ   false
#define ENERGY     320000
// #define SAMPLE9    true

SWenv::SWenv(int pixelsX, int pixelsY)
{
  // Create the lists
  _objects = new SWlist();
  _lights  = new SWlist();

  // Zero out photons
  _photons     = NULL;
  _photonIndex = 0;
  _photonSize  = 0;

  // Alloc the ANN photon crap
  _index = new ANNidx[ANNSAMPLE];
  _dists = new ANNdist[ANNSAMPLE];
  _query = annAllocPt(3);  

  // Load up our test enviornment
  loadEnv();

  // Assume square pixels
  _camera.height( _camera.width() * (float)pixelsY / (float)pixelsX );
  _scaleX =     _camera.width()  / (float)pixelsX;
  _scaleY = - ( _camera.height() / (float)pixelsY );

  // Give info as to where the eye is
  cout << "eye: " << _camera.eye() << endl;
}

SWenv::~SWenv()
{
  cout << "delete lists!" << endl;
  delete _index;
  delete _dists;

  for( int i = 0; i < _photonIndex; i ++ )
    {
      delete _photons[i];
    }
  delete _photons;
}

void SWenv::mapPhotons()
{
  // Get size of lights
  int size = _lights->size();

  // How many photons could we possibly have
  _photonSize = size * ENERGY;

  // Alloc the space
  _photons = new SWphoton * [ _photonSize ];

  // Whip through the lights
  for( int i = 0; i < size; i ++ )
    {
      cout << "Mapping light: " << i << endl;

      // Fetch the light
      SWlight * light = (SWlight *)_lights->get(i);

      // Draw a vector from the light to the camera target
      SWunitv l( light->location(), _camera.target() );

      int energy = (int) ((float)ENERGY * light->power());

      // Create the energy for the lights
      for( int e = 0; e < energy; e ++ )
	{
	  SWvector v;

	  // Find a good vector
	  do
	    {
  	      // xx yy zz between -RAND_MAX/2 +RAND_MAX/2
  	      int xx = random() - RAND_MAX/2;
  	      int yy = random() - RAND_MAX/2;
  	      int zz = random() - RAND_MAX/2;
	      
  	      float x = (float)xx / ( (float)RAND_MAX / 2.0f);
  	      float y = (float)yy / ( (float)RAND_MAX / 2.0f);
  	      float z = (float)zz / ( (float)RAND_MAX / 2.0f);
	      
  	      v = SWvector(x, y, z);
  	    }
	  while( v.length() > 1.0f || v * l < 0.0f );

	  // Got one so map it.
	  mapPhoton( SWline( light->location(), v ),
		     light->color() );
	}
    }
  buildKDTree();
}

/*
 * The basic idea is we are going to find the closest object and
 *  if it is transparent, then map the photon through the object
 *  and record where it hits.  Good good.
 */
void SWenv::mapPhoton( const SWline & ray, const SWcolor & color  )
{
  // Lets hold onto the intersect for the closest object
  SWintersect hit;

  // Copy the photon off so we can change it
  SWline photon = ray;

  // Do we care
  bool care = false;

  // How deep do we care
  int depth = 5;

  // This is to make sure we don't check the object we just hit
  SWobject * self = NULL;

  do
    {
      // Find the closest object
      SWobject * object = intersect( photon, self, depth, &hit );
      
      // If we missed, the photon never hit anything so just return
      if( object == NULL ) return;

      // Copy off self for the next time through the loop
      self = object;

      // Transparent objects are of most interest
      if( object->isTransparent() )
	{
	  float roulette = (float)random() / (float)RAND_MAX;
	  if( roulette < object->opaque() )
	    {
	      // All of the sudden, we really do care
	      care = true;

	      // Da, we go through
	      try
		{
		  // Get the exit line
		  SWline refractPhoton = object->enter( photon, hit );
		  photon = object->leave(refractPhoton, 10); 
		}
	      catch( noLeave )
		{
		  // The photon got lost in a transparent object so just
		  // return, we may want to actually do something here 
		  // but I'm not quite sure what.
		  return;
		}
	    }
	  else
	    {
	      // We have hit a real surface, so finish looping
	      break;
	    }
	}
      else if( object->isReflective() )
	{
	  // Don't mess with the care, but bounce the ray on a 
	  //  Russian Roulette
	  float roulette = (float)random() / (float)RAND_MAX;
	  if( roulette < object->ks() )
	    {
	      // Da, we bounce
	      photon = object->bounce( photon, hit );
	    }
	  else
	    {
	      // We have hit a real surface, so finish looping
	      break;
	    }
	}
      else 
	{
	  // We have hit a real surface so finish looping
	  break;
	}
    }
  while( depth -- );
  
  if( care )
    {
      // Record the final hit point
      SWpoint point = photon * hit.inDistance();
      
      // This should never be thrown ... right
      assert( _photonIndex < _photonSize );

      // Add the photon to the stack
      _photons[ _photonIndex ++ ] = new SWphoton( point, color );
    }
}

void SWenv::buildKDTree()
{
  cout << "Building photon tree of size: " << _photonIndex << endl;
  
  // Alloc the points
  ANNpointArray points = annAllocPts(_photonIndex, 3);

  // Copy the points overn
  for( int i = 0; i < _photonIndex; i ++ )
    {
      SWpoint point = _photons[i]->point();
      
      points[i][0] = point.x();
      points[i][1] = point.y();
      points[i][2] = point.z();
    }
  
  // Alloc the tree
  _kdtree = new ANNkd_tree(points, _photonIndex, 3);
  assert( _kdtree != NULL );
}  

SWcolor SWenv::intensity(const SWpoint & point) const
{
  _query[0] = point.x();
  _query[1] = point.y();
  _query[2] = point.z();
  
  // Make sure we have a tree
  assert( _kdtree != NULL );

  // If we have too little points, just return
  if( _photonIndex < ANNSAMPLE ) return SWcolor();

  // Search out the nearest x points
  _kdtree->annkSearch(_query, ANNSAMPLE, _index, _dists, 0.0f);

  // Start with a black color
  SWcolor color;
  
  // Add up all the photon colors
  for( int i = 0; i < ANNSAMPLE; i ++ )
    color += _photons[ _index[ i ] ]->color();

  // Divide by the number of points
  color /= (float)ANNSAMPLE;

  // Compute the area
  float area = 3.1415f * _dists[ANNSAMPLE - 1];

  // Return the color divided by the area
  return color / (area * 2.0f);
}

#ifdef SAMPLE9
SWcolor SWenv::color(int x, int y)
{
  SWcolor finalColor;

  float sx = _scaleX/3.0f;
  float sy = _scaleY/3.0f;

  float xx = (float)x * _scaleX - sx;
  float yy = (float)y * _scaleY - sy;

  int count = 0;
  for( int dy = -1; dy <= 1; dy ++ )
    {
      for( int dx = -1; dx <= 1; dx ++ )
	{
	  SWpoint target = _camera.upperLeft() +
	    ((_camera.side() * ( (float)((3 * x) + dx) ) * sx) +
	     (_camera.up() * ( (float)((3 * y) + dy) ) * sy));

	  SWline ray( _camera.eye(), target);
	  
	  finalColor += color(ray, 40, NULL);
	  count ++;
	}
    }

  return finalColor /= 9.0f;
}
#else
SWcolor SWenv::color(int x, int y)
{
  SWpoint target = _camera.upperLeft() +
    ((_camera.side() * (float)x * _scaleX) + 
     (_camera.up() * (float)y * _scaleY));
  
  SWline ray( _camera.eye(), target);
  
  return color(ray, 10, NULL);
}
#endif

SWcolor SWenv::color(const SWline   & ray,
		          int       depth,
		   const SWobject * theObject
		    ) const
{
  if( depth <= 0 ) return _background;

  SWintersect myIntersect;

  // Find the closest object
  SWobject * object = intersect(ray, theObject, false, &myIntersect);

  // If we hit nothing, return background
  if( object == NULL ) return _background;

  // Now calculate the color
  return object->color(this, ray, myIntersect, depth);
}


SWobject * SWenv::intersect(const SWline   & ray,
			   const SWobject * theObject,
			   bool             internal,
			   SWintersect     * theIntersect
			   ) const
{
  float      minDistance;     // Closest distance
  SWobject * myObject = NULL; // Closest object
  
  // Whip through the objects
  int size = _objects->size(); 
  for( int i = 0; i < size; i++ )
    {
      // Fetch the object 
      SWobject * object = (SWobject *)_objects->get(i);

      // If this is us, skip it
      if( object == theObject ) continue;

      SWintersect hit = object->intersect(ray);

      if( ! hit.contact() ) continue; 	  // Try a different object
      
      if( myObject == NULL || hit.inDistance() < minDistance )
	{
	  minDistance = hit.inDistance();
	  myObject    = object;

	  if( theIntersect != NULL ) *theIntersect  = hit;
	}
    }
  return myObject;
}

void SWenv::loadEnv( char * filename )
{
}

void SWenv::loadEnv()
{
  _background = SWcolor(0.45f, 0.45f, 0.65f);
  _camera     = SWcamera( SWpoint(0.0f, 1.0f, 2.0f), 12.0f, 8.0f,
			    - 1.0f, .2f); 
			  
  _dimmer     = 1.0f;
  _ambient    = SWcolor(0.1f, 0.1f, 0.1f);

  _lights->add( new SWlight( SWcolor(1.0f, 1.0f, 1.0f),
			     SWpoint(0.0f, 13.0f, -10.0f),
			     1.0f * _dimmer));

  if( WALLOBJ )
    {
      SWmaterial * material = new SWmaterial(0.11, true, true,
					   SWcolor(1.0f, 1.0f, 1.0f),
					   1.5, 0.5);

      SWlist * mirror = new SWlist();
      mirror->add( new SWplane( SWunitv( 0, 0, -1 ), 3 ) );
      mirror->add( new SWplane( SWunitv( 0, 0,  1 ), 3 ) );
      mirror->add( new SWplane( SWunitv( -1, 0, 0 ), 3 ) );
      mirror->add( new SWplane( SWunitv(  1, 0, 0 ), 3 ) );
      mirror->add( new SWplane( SWunitv( 0, -1, 0 ), 0 ) );
      mirror->add( new SWplane( SWunitv( 0,  1, 0 ), .25 ) );
      
      SWmesh   * mesh   = new SWmesh( mirror );
      SWobject * object = new SWobject(material,
				       SWpoint(0.0f, 1.0f, 1.0f),
				       SWrotation());
      object->addComponent(mesh);
      _objects->add(object);
    }
  
  // Add big green sphere
  if( SPHEREOBJ )
    {
      SWmaterial * material = new SWmaterial(0.157, true, true,
					   SWcolor(0.0f, 0.0f, 1.0f),
					   1.5f, 0.2f);
      SWsphere * sphere = new SWsphere(1.5f);
      SWrotation rotation;
      rotation.x(0.3f);
      SWobject * object = new SWobject(material,
				       //  SWpoint(-1.1f, 1.0f, 0.0f),
				       SWpoint(.75f, 3.5f, -0.5f),
				       rotation
				       );
      object->addComponent(sphere);

      object->addPlane( new SWplane( SWunitv( 0.0f, 1.0f, 0.0f ), 0.0f) );
      _objects->add( object );
    }
  
  
  // Add base
  if(BASEOBJ)
    {
      SWmaterial * material = new SWmaterial(0.11, true, false,
					   SWcolor(0.70f, 0.60f, 0.30f));      
      
      SWlist * baseList = new SWlist();
      baseList->add( new SWplane( SWunitv(0.0f,  1.0f,  0.0f), 0.5f)); // 0top
      baseList->add( new SWplane( SWunitv(0.0f,  0.0f, -1.0f), 3.0f)); // 1front
      baseList->add( new SWplane( SWunitv(1.0f,  0.0f,  0.0f), 3.0f)); // 2right
      baseList->add( new SWplane( SWunitv(0.0f,  0.0f,  1.0f), 3.0f)); // 3back
      baseList->add( new SWplane( SWunitv(-1.0f, 0.0f,  0.0f), 3.0f)); // 4left
      baseList->add( new SWplane( SWunitv(0.0f, -1.0f,  0.0f), 0.5f)); // 5bottom
      SWmesh   * base   = new SWmesh( baseList );
      SWobject * object = new SWobject( material,
					SWpoint(0, -0.5, 2),
					SWrotation());
      object->addComponent( base );
      _objects->add( object );
    }

}
