#include <list.h>
#include <iostream.h>
#include <string.h>

// create a basic class
class namer
{
private:
  char _name[20];
  
public:
  namer(char *);

  inline void speak(){ cout << "my name is: " << _name << endl; }
};

namer::namer(char * name)
{
  strcpy( _name, name );
}


main()
{
  namer fred1("fred1");
  namer fred2("fred2");
  namer fred3("fred3");
  namer fred4("fred4");

  list * names = new list();
  
  names->add(& fred1);
  names->add(& fred2);
  names->add(& fred3);
  names->add(& fred4);

  int size = names->size();
  cout << "list size: " << size << endl;
  
  for( int i = 0; i < size; i ++ )
    {
      namer * name = (namer *)(names->get(i));
      name->speak();
    }

  cout << endl;

  while( names->peek() != NULL )
    {
      {
	namer * name = (namer *)(names->peek());
	name->speak();
      }
      {
	namer * name = (namer *)(names->pop());
	name->speak();
      }
    }
}


  
