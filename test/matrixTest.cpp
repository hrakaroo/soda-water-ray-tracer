#include <iostream.h>
#include <matrix.h>
#include <line.h>

void mult1();
void mult2();
void mult3();
void mult4();
void blank();
void invert();
void invert2();
void point();
void rot();
void line1();
void line2();

float radian( float degree )
{
  return 3.1415f/ 180.0f * degree;
}



void main()
{
  /*
  mult1();
  mult2();
  mult3();
  mult4();
  blank();
  invert();
  invert2();
  point();
  rot();
  line1();
  */
  
  line2();
}

void line1()
{
  float data1[] = { 0, 0, -7, 1,
		    0, 0, 1,  1 };

  matrixf matrix1(2, 4, data1);

  cout << "matrix1: " << matrix1 << endl;

  float data2[] = { 1, 0, 0, 0,
		    0, 1, 0, 0,
		    0, 0, 1, 0,
		    2, 0, 0, 1 };

  matrixf matrix2(4, 4, data2);

  cout << "matrix2: " << matrix2 << endl;

  matrixf matrix3 = matrix2.invert();

  cout << "matrix3: " << matrix3 << endl;

  matrixf matrix4 = matrix1 * matrix3;

  cout << "matrix4: " << matrix4 << endl;
}

void line2()
{
  line3f line1( point3f(0, 0, -7), point3f(0, 0, 0) );

  cout << "line1 : " << line1 << endl;
  
  float data1[] = { 1, 0, 0, 0,
		    0, 1, 0, 0,
		    0, 0, 1, 0,
		    2, 0, 0, 1 };

  matrixf matrix1(4, 4, data1);

  cout << "matrix1: " << matrix1 << endl;

  line3f line2 = line1 * matrix1.invert();

  cout << "line2 : " << line2 << endl;
}
 
void mult1()
{
  float data1[] = { 2, 3,
		    3, 4,
		      4, 5 };
  
  float data2[] = { 2, 3, 4,
		    3, 4, 5 };
  
  matrixf matrix1(3, 2, data1 );
  cout << "matrix1 : " << matrix1 << endl;
  
  matrixf matrix2(2, 3, data2 );
  cout << "matrix2 : " << matrix2 << endl;
  
  matrixf matrix3 = matrix1 * matrix2;
  cout << "matrix1 * matrix2: " << matrix3 << endl;
}

void mult2()
{
  float data1[] = { 1, 2 };
  
  float data2[] = { 1, 3, 
		    2, 4 };
  
  matrixf matrix1(1, 2, data1 );
  cout << "matrix1 : " << matrix1 << endl;
  
  matrixf matrix2(2, 2, data2 );
  cout << "matrix2 : " << matrix2 << endl;
  
  matrixf matrix3 = matrix1 * matrix2;
  cout << "matrix1 * matrix2 : " << matrix3 << endl;
}

void mult3()
{ 
  float data1[] = { 1, 2, 3,
		    2, 3, 4,
		    3, 4, 5 };
  matrixf matrix1(3, 3, data1);
  
  cout << "matrix1 : " << matrix1 << endl;
  
  float data2[] = { 2, 3, 4,
		    3, 4, 5,
		    4, 5, 6 };
  matrixf matrix2(3, 3, data2);
  
  cout << "matrix2 : " << matrix2 << endl;
  
  matrixf matrix3 = matrix1 * matrix2;
  
  cout << "matrix3 : " << matrix3 << endl;
}


void point()
{
  point3f point(0.0f, 0.0f, 0.0f);
  float   trans[] = { 1, 0, 0, 0,
		      0, 1, 0, 0,
		      0, 0, 1, 0,
		      4, 5, 6, 1 };
  matrixf matrix(4, 4, trans);
  
  cout << "point : " << point << endl;
  cout << "matrix: " << matrix << endl;
  
  matrixf pmatrix( point );
  
  cout << "matrix point: " << pmatrix << endl;
  
  point3f move = point * matrix;
  
  cout << "move : " << move << endl;
}

void rot()
{
  point3f point(1.0f, 0.0f, 0.0f);
  
  cout << "point : " << point << endl;
  
  matrixf rot = matrixf::rotZ( radian(45) );
  
  cout << "rot : " << rot << endl;
  
  point3f move = point * rot;
  
  cout << "move : " << move << endl;
}

void mult4()
{
  float mat1[] = { -4, 3, 0, 1,
		   1, 0, 0, 1};
  
  matrixf matrix1(2, 4, mat1);
  cout << "mat1: " << matrix1 << endl;
  
  float mat2[] = { 1, 0,  0, 0,
		   0, 1,  0, 0,
		   0, 0,  1, 0,
		   0, -2, 0, 1 };
  matrixf matrix2(4, 4, mat2);
  cout << "mat2: " << matrix2 << endl;
  
  matrixf result = matrix1 * matrix2;
  
  cout << "result: " << result << endl;
}

void blank()
{
  matrixf matrix(4, 4);
  
  cout << "empty matrix: " << matrix << endl;
}

void invert()
{ 
  float data1[] = { 3, 1, 0, 1,
		    -1, 1, 2, 1,
		    0, 2, 4, 1,
		    -1, 2, 4, 1};
  
  matrixf matrix1(4, 4, data1);
  
  cout << "matrix1 : " << matrix1 << endl;
  
  matrixf matrix2 = matrix1.invert();
  
  cout << "matrix2 : " << matrix2 << endl;
  
  matrixf matrix3 = matrix1 * matrix2;
  
  cout << "matrix3 : " << matrix3 << endl;
}

void invert2()
{
  float data1[] = { 3, 1, 0,
		    -1, 1, 2,
		    0, 2, 4 };
  matrixf matrix1(3, 3, data1);
  
  cout << "matrix1 : " << matrix1 << endl;
  
  float data2[] = {0, -1, 0.5,
		   1, 3, -1.5, 
		   -0.5, -1.5, 1};
  
  matrixf matrix2(3, 3, data2);
  
  cout << "matrix2 : " << matrix2 << endl;
  
  matrixf matrix3 = matrix1 * matrix2;
  
  cout << "matrix3 : " << matrix3 << endl;
  
}
