#ifndef _SDAL_H_
#define _SDAL_H_

#include "list.h"
#include <stdexcept>

namespace cop3530{
template <typename E>
class SDAL : public List <E>
{
public:
  SDAL();
  SDAL(int sz);
  ~SDAL();
  void insert (E elt, int pos);
  void push_front(E elt);
  void push_back(E elt);
  E pop_front();
  E pop_back();
  E peek_front();
  E peek_back();
  E item_at(int pos);
  bool is_empty();
  bool is_full();
  std::ostream& print(std::ostream &out);
private:
  void shift_and_expand();
  void expand();
  void shrink();
  void shift();
  void shift_left();
  int tail;
  int mx_sz;
  int initial_mx_sz;
  E *data;
}; // End SDAL definition

// --- default constructor --- //
template <typename E>
SDAL<E>::SDAL()
{
  tail = 0;
  mx_sz = 50;
  initial_mx_sz = 50;
  data = new E[mx_sz + 1];
}
// --- specified constructor --- //
template <typename E>
SDAL<E>::SDAL(int sz)
{
  tail = 0;
  mx_sz = sz;
  initial_mx_sz = sz;
  data = new E[mx_sz + 1];
}
// --- destructor --- //
template <typename E>
SDAL<E>::~SDAL()
{
  delete [] data;
}

// --- push_front --- //
template <typename E>
void SDAL<E>::push_front(E elt)
{
  if(is_empty() && mx_sz >= 1)
  {
    data[0] = elt;
  } else if (is_full()) {
    shift_and_expand();
    data[0] = elt;
  } else if (mx_sz >= 1) {
    shift();
    data[0] = elt;
  }
  ++tail;
}

// --- push_back --- //
template <typename E>
void SDAL<E>::push_back(E elt)
{
  if(is_empty() && mx_sz >= 1)
  {
    data[0] = elt;
  } else if (is_full()) {
    expand();
    data[tail] = elt;
  } else if (mx_sz >= 1) {
    data[tail] = elt;
  }
  ++tail;
}

// --- pop_front --- //
template <typename E>
E SDAL<E>::pop_front()
{
  if (is_empty())
  {
    throw std::runtime_error("E SDAL<E>::pop_front(): List empty");
  }
  E top = data[0];
  shift_left();
  --tail;
  if (mx_sz >= 2*initial_mx_sz && tail < mx_sz/2)
  {
    shrink();
  }
  return top;
}

// --- peek_front --- //
template <typename E>
E SDAL<E>::peek_front()
{
  if (is_empty())
  {
    throw std::runtime_error("E SDAL<E>::peek_front(): List empty");
  }
  return data[0];
}

// --- peek_back --- //
template <typename E>
E SDAL<E>::peek_back()
{
  if (is_empty())
  {
    throw std::runtime_error("E SDAL<E>::peek_back(): List empty");
  }
  return data[tail-1];
}

// --- item_at --- //
template <typename E>
E SDAL<E>::item_at(int pos)
{
  if (is_empty())
  {
    throw std::runtime_error("E SDAL<E>::item_at(int pos): List empty");
  } else if (pos < 0 || pos >= tail) {
    throw std::runtime_error("E SDAL<E>::item_at(int pos): index out of bounds");
  }
  return data[pos];
}

// --- is_empty --- //
template <typename E>
bool SDAL<E>::is_empty()
{
  return(tail == 0);
}

// --- is_full -- ///
template <typename E>
bool SDAL<E>::is_full()
{
  return (tail == mx_sz);
}

// -- shift_and_expand -- //
template <typename E>
void SDAL<E>::shift_and_expand()
{
  // copy over elements starting at the first index of new array
  // make an array 150% the size of the old one
  E *new_data = new E[(mx_sz*3)/2];
  mx_sz = (mx_sz*3)/2;

  // fill in the new array with elements from old array shifted
  for (int i = 0; i < tail; ++i)
  {
    new_data[i+1] = data[i];
  }

  // delete old array
  delete [] data;

  // set data equal to new array
  data = new_data;
}

// --- expand --- //
template <typename E>
void SDAL<E>::expand()
{
  // copy over elements starting at the 0 index of new array
  // make an array 150% the size of the old one
  E *new_data = new E[(mx_sz*3)/2];
  mx_sz = (mx_sz*3)/2;

  // fill in the new array with elements from old array shifted
  for (int i = 0; i < tail; ++i)
  {
    new_data[i+1] = data[i];
  }

  // delete old array, change mx_sz
  delete [] data;

  // set data equal to new array
  data = new_data;
}

// --- shrink --- //
template <typename E>
void SDAL<E>::shrink()
{
  // copy over elements starting at the 0 index of new array
  // make an array 75% the size of the old one
  E *new_data = new E[(mx_sz*3)/4];

  // fill in the new array with elements from old array shifted
  for (int i = 0; i < tail; ++i)
  {
    new_data[i] = data[i];
  }

  // delete old array
  delete [] data;

  // set data equal to new array
  data = new_data;

}

// --- shift --- //
template <typename E>
void SDAL<E>::shift()
{
  for (int i = tail; i > 0; --i)
  {
    data[i] = data[i-1];
  }
}

// --- shift_left --- //
template <typename E>
void SDAL<E>::shift_left()
{
  for (int i = 0; i < tail-1; ++i)
  {
    data[i] = data[i+1];
  }
}

// --- print --- //
template <typename E>
std::ostream& SDAL<E>::print(std::ostream &out)
{
  if (is_empty())
  {
    out << "<empty list>";
  } else {
    out << "[";
    for (int i = 0; i < tail; ++i)
    {
      if (i == tail - 1)
      {
        out << data[i];
      } else {
        out << data[i] << ",";
      }
    }
    out << "]";
  }
  return out;
}




}

#endif
