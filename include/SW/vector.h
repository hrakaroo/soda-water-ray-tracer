#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <SW/point.h>

class SWunitv;
class SWpoint;
class SWcross;

class SWvector
{
 protected:
  float _x;
  float _y;
  float _z;

 public:
  SWvector();
  SWvector(float, float, float);
  SWvector(const SWpoint &);
  SWvector(const SWpoint &, const SWpoint &);

  float length();

  inline float x() const { return _x; }
  inline float y() const { return _y; }
  inline float z() const { return _z; }

  friend ostream & operator<<(ostream &, const SWvector &); 
  friend float     operator*(const SWvector &, const SWvector &); 

  friend SWvector  operator+(const SWvector &, const SWvector &);
  friend SWvector  operator-(const SWvector &, const SWvector &);

  friend SWvector  operator*(const SWvector &, float); 
  friend SWvector  operator-(const SWvector &);
			    
  friend class SWunitv;
  friend class SWpoint;
  friend class SWplane;

  // Defined in point.cpp
  friend SWpoint  operator+(const SWpoint &, const SWvector &);
  friend SWpoint  operator-(const SWpoint &, const SWvector &);
};

class SWunitv : public SWvector
{
 private:
  void normalize();

 public:
  SWunitv();
  SWunitv(float, float, float);
  SWunitv(const SWpoint &, const SWpoint &);
  SWunitv(const SWvector &);

  SWcross cross();

  SWunitv & operator=(const SWvector &);

  friend SWunitv  operator-(const SWunitv &);
};  

class SWcross
{
 private:
  SWunitv _up;
  SWunitv _side;
 public:
  SWcross(const SWunitv &, const SWunitv &);
  
  inline SWunitv up()   const { return _up;   }
  inline SWunitv side() const { return _side; }

};
  
#endif //__VECTOR_H__
