#include <iostream.h>

float hit(int v)
{
  if( v == 0 )
    throw 'z';
  return 5;
}
    

main()
{
  int v;
  cin >> v;
  try {
    hit( v );
    cout << "nope" << endl;
  }
  catch( char c )
    {
      cout << "caught : " << c << endl;
    }
}
