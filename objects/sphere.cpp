#include <SW/component.h>

#include <math.h>

SWsphere::SWsphere(float  radius)
{ _radius = radius; }

SWintersect SWsphere::intersect(const SWline & ray)
{
  // Line   equation: p = org + u * dir
  // Sphere equation: |p - orgin| = radius
  //  | org + u * dir - orgin | = radius
  //  ( org + u * dir - orgin )^2 = radius^2
  //
  //  ( u * dir + (org - orgin) )^2 = radius^2
  //  u^2*dir^2 + 2*u*dir*(org-orgin) + (org-orgin)^2 - radius^2 = 0
  //
  //  a = dir * dir
  //  b = 2 * dir * (org - orgin)
  //  c = (org - orgin) * (org - orgin) - radius * radius

  // Make a vector out of the ray orgin ... for ease of use
  SWvector rayPoint( ray.point() );
  
  float a = ray.direction() * ray.direction();
  float b = 2.0f * ( ray.direction() * rayPoint );
  float c = rayPoint * rayPoint - _radius * _radius;

  // Quadratic equation
  float rr = (b*b - 4.0f * a * c);
  
  if( rr < 0.0f ) return SWintersect();

  float r = sqrtf( rr );
  float a2 = 2.0f * a;

  // Calculate two distances
  float u[2];
  u[0] = (- b + r)/a2;
  u[1] = (- b - r)/a2;

  // Create a view Vector which is in the opposite dir from the ray.
  SWunitv view = - ray.direction();

  SWintersect hit;

  // We only care about positive values for u
  for( int i = 0; i < 2; i++ )
    {
      // Compute intersect point 
      SWpoint point = ray * u[i];
      
      // Create a normal for this point
      SWunitv normal(point);
      
      // Check for a hit
      float angle = view * normal;

      if( rr == 0.0f )
	{
	  hit.in( u[i], normal );
	  hit.out( u[i], normal );
	  return hit;
	}
      if( angle >= 0.0f )
	{
	  hit.in( u[i], normal );
	}
      else
	{
	  hit.out( u[i], normal );
	}
    }
  if( (hit.inSet() && hit.inDistance() >= 0.0f ) ||
      (hit.outSet() && hit.outDistance() >= 0.0f ))
    return hit;

  return SWintersect();
}
