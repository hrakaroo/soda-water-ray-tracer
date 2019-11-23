#ifndef __LIST_H__
#define __LIST_H__

class SWlist
{
 protected:
  SWlist * _next;
  void   * _object;

 public:
  SWlist();

  void   add(void *);
  void * get( int ) const;

  void   push(void *);
  void * pop();
  void * peek() const;

  int    size() const;
};

#endif // __LIST_H__

    
  
