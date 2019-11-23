#include <SW/rotation.h>

SWrotation::SWrotation()
{
  _matrix = new SWmatrix(4,4);
}

SWrotation::~SWrotation()
{
  delete(_matrix);
}

void SWrotation::x(float radian)
{
  *_matrix = *_matrix * SWmatrix::rotX(radian);
}

void SWrotation::y(float radian)
{
  *_matrix = *_matrix * SWmatrix::rotY(radian);
}

void SWrotation::z(float radian)
{
  *_matrix = *_matrix * SWmatrix::rotZ(radian);
}

