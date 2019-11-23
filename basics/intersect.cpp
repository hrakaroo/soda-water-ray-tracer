#include <SW/intersect.h>

#include <assert.h>

SWintersect::SWintersect()
{
  _contact = false;
  _inSet   = false;
  _outSet  = false;
}

void SWintersect::in(float distance, const SWunitv & normal)
{
  _inDistance = distance;
  _inNormal   = normal;
  _contact    = true;
  _inSet      = true;
}

void SWintersect::out(float distance, const SWunitv & normal)
{
  _outDistance = distance;
  _outNormal   = normal;
  _contact     = true;
  _outSet      = true;
}

float   SWintersect::inDistance()  const 
{ 
  assert( _inSet );
  return _inDistance;  
}

SWunitv SWintersect::inNormal()    const 
{ 
  assert( _inSet );
  return _inNormal;    
}

float   SWintersect::outDistance() const 
{
  assert( _outSet );
  return _outDistance; 
}

SWunitv SWintersect::outNormal()   const 
{ 
  assert( _outSet );
  return _outNormal;   
}

