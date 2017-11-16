#ifndef _LIST_H_
#define _LIST_H_
#include <iostream>
namespace cop3530{


template <typename E>
class List
{
public:
  virtual void insert (E elt, int pos) = 0;
  virtual void push_front(E elt) = 0;
  virtual void push_back(E elt) = 0;
  virtual E replace(E elt, int pos) = 0;
  virtual E remove(int pos) = 0;
  virtual E pop_front() = 0;
  virtual E pop_back() = 0;
  virtual E item_at (int pos) = 0;
  virtual E peek_front() = 0;
  virtual E peek_back() = 0;
  virtual int length() = 0;
  virtual bool is_empty() = 0;
  virtual bool is_full() = 0;
  virtual void clear() = 0;
  virtual void print(std::ostream & out) = 0;
  virtual bool contains(E elt, bool (*equals_fn)(const E &a, const E &b)) = 0;
  virtual E* contents() = 0; // should return an array

};


}
#endif
