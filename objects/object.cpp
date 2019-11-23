#include <SW/object.h>

#include <assert.h>
#include <stdlib.h>
#include <math.h>

SWobject::SWobject(const SWmaterial * material,
		   const SWpoint    & location,
		   const SWrotation & rotation)
{
  _material = material;

  // Create the transformation matrix
  float data[] = { 1, 0, 0, 0,
		   0, 1, 0, 0,
		   0, 0, 1, 0,
		   location.x(), location.y(), location.z(), 1 };

  SWmatrix shift(4, 4, data);

  SWmatrix trans = rotation.matrix() * shift;

  _obj2wld = new SWmatrix( trans );
  _wld2obj = new SWmatrix( trans.invert() );

  _components = new SWlist();
  _planes     = new SWlist();
}

SWobject::~SWobject()
{
  if( _obj2wld != NULL )
    delete(_obj2wld);
  
  if( _wld2obj != NULL )
    delete(_wld2obj);

  if( _components )
    {
      delete _components;
      cout << "need to delete all components" << endl;
    }
  
  if( _planes )
    delete _planes;
}


SWcolor SWobject::color(const SWenv       * env,
			const SWline      & ray,
			const SWintersect & intersect,
			int                depth 
			) const
{
  return _material->externalColor(env, ray, intersect, depth, this);
}

SWintersect SWobject::intersect(const SWline & ray ) const
{
  // Make sure we have something to hit
  assert( _components != NULL ); 

  // Transfer the ray to object cords
  SWline  rayObject = ray * *_wld2obj;

  // At this point we only have one component, so just fetch that one
  SWcomponent * component = (SWcomponent *) _components->get(0);

  // Find the intersect for this component
  SWintersect hit = component->intersect( rayObject );

  // If we missed the component, we missed the object
  if( ! hit.contact() ) return SWintersect();

  // If we get here then we must have hit the component

  // Create a view vector
  SWunitv view = - rayObject.direction();

  // Walk through our cutting place, resetting intersect points as needed
  int planeSize = _planes->size();
  for( int i = 0; i < planeSize; i++ )
    {
      // Fetch plane
      SWplane * plane = (SWplane *) _planes->get(i);
      
      // Find where our ray hits this plane
      float distance;
      try
	{
	  distance = plane->intersect(rayObject);
	}
      catch( abovePlane )
	{
	  // If we are above the cutting plane, we have missed the object
	  return SWintersect();
	}
      catch( belowPlane )
	{
	  // Boring ... next plane
	  continue;
	}
      
      // Get the angle of intersect
      float angle = view * plane->normal();

      if( angle >= 0.0f )
	{
	  // We entered and left the object before even
	  // hitting the cutting plane, so we never hit the
	  // object
	  if( hit.outSet() && hit.outDistance() < distance )
	    return SWintersect();

	  // Change hit.in
	  else if( ! hit.inSet() || distance > hit.inDistance() )
	    hit.in( distance, plane->normal() );
	}
      else
	{
	  // Again, I hit the cutting plane before I even
	  // entered the object so I never hit the object
	  if( hit.inSet() && distance < hit.inDistance() )
	    return SWintersect();

	  // Change hit.out
	  else if( ! hit.outSet() || hit.outDistance() > distance )
	    hit.out( distance, plane->normal() );
	}
    }
  
  if( hit.outSet() )
    hit.out( hit.outDistance(), hit.outNormal() * *_obj2wld );
  
  if( hit.inSet() )
    hit.in( hit.inDistance(), hit.inNormal() * *_obj2wld );

  return hit;
}

SWline SWobject::bounce(const SWline & ray,
			const SWintersect & hit) const
{
  // Calculate the hit point
  SWpoint  point    = ray * hit.inDistance();

  // Calculate everything on the outside
  SWvector view     = - ray.direction();
  SWvector normal   = hit.inNormal();
  SWvector normalP  = normal * ( view * normal );
  SWvector step     = normalP - view;
  SWvector reflect  = normalP + step;

  return SWline( point, reflect );
}

SWline SWobject::enter(const SWline & ray, 
		       const SWintersect & hit) const
  throw ( noLeave )
{
  // Calculate everything on the outside
  SWvector view     = - ray.direction();
  SWvector normal   = hit.inNormal();
  SWvector normalP  = normal * ( view * normal );
  SWvector step     = normalP - view;

  // Now flip and calculate the refracted vector
  SWvector stepP    = step * (1.0f / _material->refraction() );
  float length      = stepP.length();
  SWvector normalPP = - normal * ( sqrtf( 1 - length * length ));
  SWvector refract  = normalPP + stepP;

  // Calculate the hit point
  SWpoint  point    = ray * hit.inDistance();

  // Build a line for the refracted Ray
  SWline refractRay( point, refract );

  return refractRay;
}

SWline SWobject::leave( const SWline & ray, int depth, 
			SWline * bounce = NULL ) const
  throw (noLeave)
{
  // Copy off the ray so we can mess with it
  SWline refractRay = ray;

  // Try to get out
  do
    {
      // ask us for an internal intersect
      SWintersect hit = intersect( refractRay );

      // If we didn't hit the object (which we are in) then 
      //  round off error has screwed us
      if( ! hit.outSet() ) throw noLeave();

      // Compute a new point
      SWpoint  point = refractRay * hit.outDistance();

      SWvector view    = - refractRay.direction();
      SWvector normal  = - hit.outNormal();
      SWvector normalP = normal * (view * normal);
      SWvector step    = normalP - view; 
      SWvector stepP   = step * (_material->refraction()/1.0f);

      float    length  = stepP.length();

      if( length >= 1.0f )
	{
	  // Internal bounce, find a reflected ray and loop
	  SWvector reflect = normalP + step;
	  refractRay = SWline( point, reflect );
	}
      else
	{
	  // We're out!
	  SWvector normalPP = - normal * ( sqrtf( 1 - length * length ));
  
	  SWvector refract = normalPP + stepP;
	  
	  SWline   refractRay(point, SWunitv(refract));

	  if( bounce != NULL )
	    {
	      SWvector reflect = normalP + step;
	      (*bounce) = SWline( point, reflect );
	    }
	  
	  return refractRay;
	}
    }
  while( depth -- );

  // If we get here then we never left in the x number of bounces 
  //  so throw a noLeave

  throw noLeave();
}
