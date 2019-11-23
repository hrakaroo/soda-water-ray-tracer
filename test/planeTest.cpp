#include <iostream.h>
#include <plane.h>
#include <point.h>
#include <line.h>

void main()
{
  { 
    point3f point1(0, 0, -5);
    point3f point2(0, 0, -2);
    
    line3f line(point1, point2);
    cout << "line: " << line << endl;

    plane3f plane( unitv3f(0, 1, 0), -3);

    float intersect;
    try
      {
	intersect = plane.intersect(line);
      }
    catch(abovePlane)
      {
	cout << "Above plane" << endl;
      }
    catch(belowPlane)
      {
	cout << "Below plane" << endl;
      }
    
    cout << "plane : " << plane << endl;
    cout << "intersect : " << intersect << endl;
  }
}

