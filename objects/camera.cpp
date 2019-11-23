#include <SW/camera.h>
#include <math.h>

SWcamera::SWcamera()
{}

SWcamera::SWcamera(const SWpoint & target,
		         float     distance,
		         float     width,
		         float     plan      = 0.0f,
		         float     elevation = 0.0f,
		         float     roll      = 0.0f)
{
  _target    = target;
  _distance  = distance;
  _plan      = plan;
  _elevation = elevation;
  _roll      = roll;

  _height   = _width     = width;

  initVectors();
  setUpperLeft();
}

void SWcamera::initVectors()
{
  float cosAlpha = cos(_roll);
  float sinAlpha = sin(_roll);
  float cosTheta = cos(_plan);
  float sinTheta = sin(_plan);
  float cosPhi   = cos(_elevation);
  float sinPhi   = sin(_elevation);

  _look = SWunitv( sinTheta * cosPhi,
		  - sinPhi,
		  cosTheta * cosPhi);
  _side = SWunitv( (cosAlpha * cosTheta) - (sinAlpha * sinTheta * sinPhi),
		  -(sinAlpha * cosPhi),
		  -(cosAlpha * sinTheta) - (sinAlpha * cosTheta * sinPhi));
  
  _up   = SWunitv( (sinAlpha * cosTheta) + (cosAlpha * sinTheta * sinPhi),
		  (cosAlpha * cosPhi),
		  -(sinAlpha * sinTheta) + (cosAlpha * cosTheta * sinPhi));
}

void SWcamera::setUpperLeft()
{
  _upperLeft = _target + ( (_side * ( -0.5f * _width  )) +
			   (_up   * (  0.5f * _height )));
}


void SWcamera::height( float height )
{
  _height = height;
  setUpperLeft();
}

SWpoint SWcamera::eye() const
{
  return _target - _look * _distance;
}

