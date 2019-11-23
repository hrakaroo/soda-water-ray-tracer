#include <SW/list.h>

#include <stdlib.h>
#include <assert.h>
#include <iostream.h>

SWlist::SWlist()
{
  _next   = NULL;
  _object = NULL;
}

void SWlist::add(void * object)
{
  if( _object == NULL )
    {
      _object = object;
    }
  else
    {
      if( _next == NULL )
	{
	  _next = new SWlist();
	}
      _next->add( object );
    }
}

void * SWlist::get( int index ) const
{
  if( index == 0 )
    return _object;

  assert( _next != NULL );
  return _next->get( index - 1 );
}

void SWlist::push(void * object)
{
  add( object );
}

void * SWlist::pop()
{
  if( _next == NULL )
    {
      void * object = _object;
      _object = NULL;
      return object;
    }
      
  if( _next->_next == NULL )
    {
      void * object = _next->_object;
      delete _next;
      _next = NULL;
      return object;
    }

  return _next->pop();
}

void * SWlist::peek() const
{
  if( _next == NULL )
    return _object;

  return _next->peek();
}

int SWlist::size() const
{
  if( _object == NULL )
    return 0;

  if( _next == NULL )
    return 1;

  return (_next->size() + 1);
}
    
	  
