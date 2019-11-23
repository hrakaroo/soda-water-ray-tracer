#include <SW/plane.h>
#include <SW/except.h>
#include <SW/component.h>

#include <assert.h>


SWmesh::SWmesh(SWlist * planes)
{ _planes = planes; }

SWintersect SWmesh::intersect(const SWline & ray)
{
  assert(_planes != NULL);

  SWunitv view = - ray.direction();

  SWintersect hit;

  int size = _planes->size();
  for( int i = 0; i < size; i++ )
    {
      //cout << "Testing plane : " << i << endl; 
      // Fetch the plane
      SWplane * plane = (SWplane *)_planes->get(i);

      float distance;
      try
	{
	  distance = plane->intersect(ray);
	}
      catch(abovePlane)
	{
	  // We have completly missed the object
	  return SWintersect();
	}
      catch(belowPlane)
	{
	  // Boring
	  continue;
	}

      // Compute intersect angle
      float angle    = view * plane->normal();

      if( angle > 0.0f )
	{
	  if( ! hit.inSet() || distance > hit.inDistance() )
	    hit.in( distance, plane->normal() );
	}
      else
	{
	  if( ! hit.outSet() || distance < hit.outDistance() )
	    hit.out(distance, plane->normal() );
	}
    }
  
  //  if( (hit.inSet() && hit.inDistance() >= 0.0f ) ||
  //      (hit.outSet() && hit.outDistance() >= 0.0f ) &&
  //      hit.inDistance() < hit.outDistance() )
  if( hit.inSet() && hit.outSet() && 
      hit.inDistance() <= hit.outDistance() &&
      hit.outDistance() >= 0.0f )
    return hit;       // Yes, we hit this object

  // No hit
  return SWintersect();
}

