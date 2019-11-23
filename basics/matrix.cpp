#include <SW/matrix.h>

#include <stdlib.h>
#include <assert.h>
#include <math.h>

SWmatrix::SWmatrix(unsigned int rows, unsigned int cols, const float * matrix)
{
  _cols   = cols;
  _rows   = rows;
  
  // allocate space
  _matrix = (float *)(malloc( sizeof(float) * _cols * _rows));

  // copy data
  for( int i = 0; i < _cols * _rows; i ++ )
    _matrix[i] = matrix[i];
}

SWmatrix::SWmatrix(unsigned int rows, unsigned int cols)
{
  _cols = cols;
  _rows = rows;
  
  // allocate space 
  _matrix = (float *)(malloc( sizeof(float) * _cols * _rows));

  for( int x = 0; x < _cols; x ++ )
    for( int y = 0; y < _rows; y ++ )
      if( x == y )
	_matrix[ y * _cols + x ] = 1.0f;
      else
	_matrix[ y * _cols + x ] = 0.0f;
	  
}

SWmatrix::SWmatrix(const SWmatrix & matrix)
{
  _cols = matrix._cols;
  _rows = matrix._rows;
  _matrix = (float *)(malloc( sizeof(float) * _cols * _rows));
  
  for( int i = 0; i < _cols * _rows; i ++ )
    _matrix[i] = matrix._matrix[i];
}

SWmatrix::SWmatrix(const SWpoint & point)
{
  _cols = 4;
  _rows = 1;
  _matrix = (float *)(malloc( sizeof(float) * _cols * _rows));

  _matrix[0] = point.x();
  _matrix[1] = point.y();
  _matrix[2] = point.z();
  _matrix[3] = 1.0f;
}

SWmatrix::SWmatrix(const SWvector & vector)
{
  _cols = 4;
  _rows = 1;
  _matrix = (float *)(malloc( sizeof(float) * _cols * _rows));

  _matrix[0] = vector.x();
  _matrix[1] = vector.y();
  _matrix[2] = vector.z();
  _matrix[3] = 0.0f;
}

SWmatrix::SWmatrix(const SWline & line)
{
  _cols = 4;
  _rows = 2;
  
  _matrix = (float *)(malloc( sizeof(float) * _cols * _rows));

  _matrix[0] = line.point().x();
  _matrix[1] = line.point().y();
  _matrix[2] = line.point().z();
  _matrix[3] = 1.0f;

  _matrix[4] = line.direction().x();
  _matrix[5] = line.direction().y();
  _matrix[6] = line.direction().z();
  _matrix[7] = 0.0f;
}

SWmatrix::~SWmatrix()
{
  free(_matrix);
}

void SWmatrix::set( unsigned int col, unsigned int row, float value )
{
  assert( col < _cols );
  assert( row < _rows );
  _matrix[ row * _cols + col ] = value;
}

float SWmatrix::get( unsigned int col, unsigned int row ) const
{
  assert( col < _cols );
  assert( row < _rows );
  return _matrix[ row * _cols + col ];
}

SWmatrix SWmatrix::invert() const
{
  // This will hold the inverse
  assert(_cols == _rows);
  SWmatrix inv(_cols, _rows);

  // Copy off this one
  SWmatrix tmp = *this;
  
  // Scale each row by the first element
  for( int d = 0; d < _rows; d ++ )
    {
      for( int y = d; y < _rows; y ++ )
        {
          float value = tmp.get(d, y);
          if( value == 0.0f )
            continue;

          for( int x = 0; x < _cols; x ++ )
            {
              tmp.set( x, y, tmp.get(x, y) / value);
	      inv.set( x, y, inv.get(x, y) / value);
	    }
        }
      
      for( int y = d + 1; y < _rows;  y ++ )
        {
          if( tmp.get(d, y) == 0.0f )
            continue;

          for( int x = 0; x < _cols; x ++ )
            {
              tmp.set(x, y, tmp.get(x, d) - tmp.get(x, y));
	      inv.set(x, y, inv.get(x, d) - inv.get(x, y));
            }
        }
    }

  for( int d = 0; d < _cols-1; d ++ )
    {
      for( int x = d + 1; x < _cols ; x ++ )
        {
          float value = tmp.get(x, d);
          if( value == 0.0f )
            continue;

          for( int xx = 0; xx < _cols ; xx ++ )
            {
              tmp.set(xx, d, tmp.get(xx, d) - tmp.get(xx, x) * value);
	      inv.set(xx, d, inv.get(xx, d) - inv.get(xx, x) * value); 
            }
        }
    }
  return inv;
}


ostream& operator<<(ostream & os, const SWmatrix & matrix)
{
  os << "SWmatrix: " << endl;
  for( int y = 0; y < matrix._rows; y ++ )
    {
      os << "\t";
      for( int x = 0; x < matrix._cols; x ++ )
	{
	  os << matrix._matrix[ y * matrix._cols + x ] << "  ";
	}
      os << endl;
    }
  return os;
}

SWmatrix & SWmatrix::operator=(const SWmatrix & matrix)
{
  _cols   = matrix._cols;
  _rows   = matrix._rows;
  _matrix = (float *)(malloc( sizeof(float) * _cols * _rows));

  for( int i = 0; i < _cols * _rows; i ++ )
    _matrix[i] = matrix._matrix[i];

  return *this;
}

SWmatrix operator*(const SWmatrix & matrix1, const SWmatrix & matrix2)
{
  assert( matrix1._cols == matrix2._rows );

  SWmatrix result( matrix1._rows, matrix2._cols );

  for( int y = 0; y < matrix1._rows; y ++ )
    {
      for( int x = 0; x < matrix2._cols; x ++ )
	{

	  float value = 0.0f;
	  for( int i = 0; i < matrix1._cols;  i ++ )
	    {
	      value += matrix1.get(i, y) * matrix2.get(x, i);
	    }

	  result.set( x, y, value );
	}
    }
  
  return result;
}

SWpoint operator*(const SWpoint & point, const SWmatrix & matrix)
{
  SWmatrix matrix1( point );
  
  SWmatrix result = matrix1 * matrix;

  return SWpoint(result._matrix[0],
		 result._matrix[1],
		 result._matrix[2]);
}

SWvector operator*(const SWvector & vector, const SWmatrix & matrix)
{
  SWmatrix matrix1( vector );
  
  SWmatrix result = matrix1 * matrix;

  return SWvector(result._matrix[0],
		  result._matrix[1],
		  result._matrix[2]);
}

SWline operator*(const SWline & line, const SWmatrix & matrix)
{
  SWmatrix matrix1( line );
  
  SWmatrix result = matrix1 * matrix;

  return SWline( SWpoint(result._matrix[0],
			 result._matrix[1],
			 result._matrix[2]),
		 SWunitv(result._matrix[4],
			 result._matrix[5],
			 result._matrix[6]));
}

SWmatrix SWmatrix::rotX( float radian )
{
  float matrix[] = {  1.0f,    0.0f,         0.0f,        0.0f,
		      0.0f,    cos(radian), -sin(radian), 0.0f,
		      0.0f,    sin(radian),  cos(radian), 0.0f,
		      0.0f,    0.0f,         0.0f,        1.0f };

  return SWmatrix(4, 4, matrix);
}

SWmatrix SWmatrix::rotY( float radian )
{
  float matrix[] = {  cos(radian),  0.0f,    sin(radian), 0.0f,
		      0.0f,         1.0f,    0.0f,        0.0f,
		     -sin(radian),  0.0f,    cos(radian), 0.0f,
		      0.0f,         0.0f,    0.0f,        1.0f };
  return SWmatrix(4, 4, matrix);
}
  
SWmatrix SWmatrix::rotZ( float radian )
{
  float matrix[] = {  cos(radian), -sin(radian), 0.0f, 0.0f,
		      sin(radian),  cos(radian), 0.0f, 0.0f,
		      0.0f,         0.0f,        1.0f, 0.0f,
		      0.0f,         0.0f,        0.0f, 1.0f };


  return SWmatrix(4, 4, matrix);
}
