#include <iostream.h>
#include <assert.h>
#include <math.h>

#include <point.h>
#include <vector.h>
#include <line.h>
#include <plane.h>

void point();
void line();
void plane();
void vector();
void matrix();

main()
{
  cout << "********** POINT **********" << endl;
  point();
  cout << endl;
  
  cout << "********** VECTOR **********" << endl;
  vector();
  cout << endl;

  cout << "********** LINE **********" << endl;
  line();
  cout << endl;

  cout << "********** PLANE **********" << endl;
  plane();
  cout << endl;

  cout << "********** MATRIX **********" << endl;
  matrix();
  cout << endl;
}



void line()
{
  point3f point1(1, 0, 0);
  point3f point2(5, 0, 0);

  line3f line(point1, point2);

  cout << line << endl;

  point3f point = line * 5;

  cout << point << endl;
}

void vector()
{
  unitv3f unitv(1, 1, 1);
  
  cout << "unitv(1, 1, 1) = " << unitv << endl;
  
  vector3f vector = unitv * 5;

  cout << "vector = " << vector << endl;

  unitv3f unitv2 = unitv * 5;

  cout << "unitv2 = " << unitv2 << endl;

  {
    unitv3f unitv(1, 1, 1);
    cout << "unitv = " << unitv << endl;
    unitv3f unitv2 = - unitv;
    cout << "- unitv = " << unitv2 << endl;
  }

  {
    vector3f vector(1, 1, 1);
    cout << "vector = " << vector << endl;
    vector3f vector2 = - vector;
    cout << "- vector = " << vector2 << endl;
  }

  { 
    unitv3f unitv(1, 1, 1);
    cout << "unitv = " << unitv << endl;
    vector3f vector = - unitv;
    cout << "- vector = " << vector << endl;
  }

  { 
    unitv3f normal(1, 1, 1);
    unitv3f unitv(1, .75, .50);
    cout << "unitv = " << unitv << endl;
    cout << "angle = " << (normal * unitv) << endl;
    cout << "angle2 = " << (normal * - unitv) << endl;
  }
}

void point()
{
  point3f point1( 1, 0, 0);
  point3f point2( 0, 1, 0);

  cout << "These should be pretty damn close" << endl;
  cout << point1 << " - " << point2 << " = " << (point1 - point2) << endl;
  cout << "sqrt 2 = " << sqrtf( 2.0f ) << endl;
}

