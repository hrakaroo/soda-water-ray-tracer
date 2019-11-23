#ifndef __ROTATION_H__
#define __ROTATION_H__

#include <SW/matrix.h>

class SWrotation
{
 private:
  SWmatrix *_matrix;

 public:
  SWrotation();
  ~SWrotation();
  
  void x(float);
  void y(float);
  void z(float);

  inline SWmatrix matrix() const { return *_matrix; }
};

#endif // __ROTATION_H__
