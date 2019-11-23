#include <SW/component.h>
#include <SW/line.h>
#include <SW/point.h>
#include <SW/vector.h>

#include <math.h>

SWecone::SWecone(float radiusX, float radiusY, float radiusZ)
{
  _radiusX = radiusX;
  _radiusY = radiusY;
  _radiusZ = radiusZ;
}

SWintersect SWecone::intersect(const SWline & ray)
{
  // q1 =  (1/rx)^2
  // q2 = -(1/ry)^2 
  // q3 =  (1/rz)^2

  float q1 =  1.0f / ( _radiusX * _radiusX );
  float q2 = -1.0f / ( _radiusY * _radiusY );
  float q3 =  1.0f / ( _radiusZ * _radiusZ );

  float i = ray.direction().x();
  float j = ray.direction().y();
  float k = ray.direction().z();

  float x0 = ray.point().x();
  float y0 = ray.point().y();
  float z0 = ray.point().z();

  float a = (q1 * i * i) + (q2 * j * j) + (q3 * k * k);
  float b = 2.0f * (q1 * x0 * i + q2 * y0 * j + q3 * z0 * k);
  float c = q1 * x0 * x0 + q2 * y0 * y0 + q3 * z0 * z0;
  
  float rr = b * b - 4.0f * a * c;
  
  if( rr < 0.0f )
    return SWintersect();

  float r = sqrtf( rr );
  
  float t[2];
  t[0] = (- b + r)/(2.0f * a);
  t[1] = (- b - r)/(2.0f * a);

  // Create a view Vector which is in the opposite dir from the ray.
  SWunitv view = - ray.direction();

  // This is the intersect info we will return
  SWintersect hit;
  
  // Go through our two computed points
  for( int ii = 0; ii < 2; ii++ )
    {
      // Compute intersect point 
      SWpoint point = ray * t[ii];

      // If our point has a negative y, ignore it
      if( point.y() < 0.0f )
	continue;

      float u = 2.0f * q1 * point.x();
      float v = 2.0f * q2 * point.y();
      float w = 2.0f * q3 * point.z();
      
      float uu = u*u;
      float vv = v*v;
      float ww = w*w;

      float length = sqrtf(uu + vv + ww);

      float i = u / length;
      float j = v / length;  
      float k = w / length;

      // Create a normal for this point
      SWunitv normal(i, j, k);
      
      // Check for a hit
      float angle = view * normal;

      if( rr == 0.0f )
	{
	  if( t[ii] < 0.0f )
	    return SWintersect();
	  
	  hit.in( t[ii], normal );
	  hit.out( t[ii], normal );
	  return hit;
	}
      if( angle >= 0.0f )
	{
	  // This is an in hit
	  hit.in( t[ii], normal );
	}
      else
	{
	  // This is an out hit
	  hit.out( t[ii], normal );
	}
    }
  if( (hit.inSet() && hit.inDistance() >= 0.0f ) ||
      (hit.outSet() && hit.outDistance() >= 0.0f ))
    return hit;

  return SWintersect();
}
