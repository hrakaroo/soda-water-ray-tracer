#include <SW/light.h>
#include <assert.h>

SWlight::SWlight(const SWcolor & color, 
		 const SWpoint & location,
		 float power )
{
  _color    = color;
  _location = location;
  _power    = power;
}

