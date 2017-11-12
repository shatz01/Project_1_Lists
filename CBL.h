#ifndef _CBL_H_
#define _CBL_H_
#include "list.h"
#include <stdexcept>

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

namespace cop3530{

template <typename E>
class CBL : public List<E>
{
public:
  CBL();
  CBL(int sz);
  ~CBL();
  void insert (E elt, int pos);
  void push_front(E elt);
  void push_back(E elt);
  E replace(E elt, int pos);
  E remove(int pos);
  E pop_front();
  E pop_back();
  E item_at (int pos);
  E peek_front();
  E peek_back();
  int length();
  bool is_empty();
  bool is_full();
  void clear();
  std::ostream& print(std::ostream &out);
  bool contains(E elt, bool (*equals_fn)(E a, E b));
  // // bool contains(E elt); // fix this to make it take a function arg too
  E* contents(); // should return an array


  // - non virtual functions - //
  void print_contents();
  void print_full();
  void inc_head();
  void inc_tail();
  void dec_head();
  void dec_tail();
private:
  int head;
  int tail;
  int mx_sz;
  E *data;

public:
  // ITERATOR CLASS
  template <typename DataT>
  class CBL_Iter
  {
    // type aliases required for C++ iterator compatibility
    using value_type = DataT;
    using reference = DataT&;
    using pointer = DataT*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    // type aliases for prettier code
    using self_type = CBL_Iter;
    using self_reference = CBL_Iter&;

  private:
    DataT* here;
    int max;
    E *array;

  public:
    explicit CBL_Iter( DataT* start, int mx_sz, E *data) : here( start ), max(mx_sz), array(data){}
    CBL_Iter( const CBL_Iter& src, int mx_sz, E *data ) : here( src.here ), max(mx_sz), array(data) {}

    reference operator*() const {
      return *here;
    }

    pointer operator->() const {
      return &(operator*());
    }

    self_reference operator=( CBL_Iter<DataT> const& src ) {
      if (this == &src) {
        return *this;
      }
      here = src;
      return *this;
    }

    self_reference operator++() {
      int distance = here - array;
      // here = mod(here+1, mx_sz + 1);
      if (distance == max)
      {
        here = array;
      } else {
        here = here + 1;
      }
      return *this;
    } // preincrement

    self_type operator++(int) {
      int distance = here - array;
      iterator preincremented = *this;
      if (distance == max)
      {
        here = array;
      } else {
        here = here + 1;
      }
      return preincremented;
    } // postincrement

    bool operator==( CBL_Iter<DataT> const& rhs ) const {
      return here == rhs.here;
    }

    bool operator!=( CBL_Iter<DataT> const& rhs) const {
      return here != rhs.here;
    }

  };// end ITERATOR class

public:
  // type aliases for prettier code:
  using iterator = CBL_Iter<E>;
  using const_iterator = CBL_Iter<E const>;

  // iterators over a non-const List
  iterator begin() { return iterator(data + head, mx_sz, data); /* iterator denoting first element */ }
  iterator end() { return iterator(data + tail, mx_sz, data);/* iterator denoting 1 past the last element */ }

  // iterators over a const List
  const_iterator begin() const { return iterator(data + head, mx_sz, data)/* const_iterator denoting first element */; }
  const_iterator end() const { return iterator(data + tail, mx_sz, data)/* const_iterator denoting 1 past the last element */; }


}; // end CBL class definition



// --- print_full --- //
template <typename E>
void CBL<E>::print_full()
{
  std::cout << "ENTIRE ARRAY: ";
  for (int i = 0; i < mx_sz +1; i++)
  {
    std::cout << data[i] << " ";
  }
  std::cout << std::endl;
}

// --- is_empty --- //
template <typename E>
bool CBL<E>::is_empty()
{
  return (head == tail);
}

// --- is_full --- //
template <typename E>
bool CBL<E>::is_full()
{
  return (head == mod(tail+1, mx_sz+1));
}

// --- push_front --- //
template <typename E>
void CBL<E>::push_front(E elt)
{
  if (is_empty())
  {
    data[head] = elt;
    inc_tail();
  } else if (is_full()){
    // Need to make a new array that is 150% bigger than the OG
    int new_mx_sz = ((mx_sz)*3)/2;
    E* new_data = new E[new_mx_sz+1];


    // copy items over
    int j = 0;
    for (int i = head; i != tail; i = mod(i+1, mx_sz + 1))
    {
      new_data[j] = data[i];
      j++;
    }
    // set this new array as the data[]
    // deallocate old array
    delete [] data;
    mx_sz = new_mx_sz;
    data = new_data;
    head = mx_sz;
    tail = j;
    data[head] = elt;
  } else {
    dec_head();
    data[head] = elt;
  }
}

// --- push_back --- //
template <typename E>
void CBL<E>::push_back(E elt)
{
  if (is_empty())
  {
    data[head] = elt;
    inc_tail();
  } else if (is_full()){
    int new_mx_sz = ((mx_sz)*3)/2;
    E* new_data = new E[new_mx_sz+1];


    // copy items over
    int j = 0;
    for (int i = head; i != tail; i = mod(i+1, mx_sz + 1))
    {
      new_data[j] = data[i];
      j++;
    }
    // set this new array as the data[]
    // deallocate old array
    delete [] data;
    mx_sz = new_mx_sz;
    data = new_data;
    head = 0;
    tail = j;
    data[tail] = elt;
    inc_tail();
  } else {
    data[tail] = elt;
    inc_tail();
  }
}

// --- peek_front --- //
template <typename E>
E CBL<E>::peek_front()
{
  if (is_empty())
  {
    throw std::runtime_error("E CBL<E>::peek_front(): list empty");
  } else {
    return data[head];
  }
}

// --- peek_back --- //
template <typename E>
E CBL<E>::peek_back()
{
  if (is_empty())
  {
    throw std::runtime_error("E CBL<E>::peek_back(): list empty");
  } else {
    return data[mod(tail-1, mx_sz+1)];
  }
}

// --- length --- //
template <typename E>
int CBL<E>::length()
{
  if (is_empty())
  {
    return 0;
  } else {
    int len = 0;
    for (int i = head; i != tail; i = mod(i+1, mx_sz + 1))
    {
      len++;
    }
    return len;
  }
}

// --- item_at --- //
template <typename E>
E CBL<E>::item_at(int pos)
{
  if (is_empty())
  {
    throw std::runtime_error("E CBL<E>::item_at(int pos): list empty");
  } else if (pos < 0 || pos > length()-1) {
    throw std::runtime_error("E CBL<E>::item_at(int pos): index out of domain");
  } else {
    int act_pos = mod(head+pos, mx_sz+1);
    return data[act_pos];
  }
}


// --- contents --- //
template <typename E>
E* CBL<E>::contents()
{
  E* content_arr = new E[length()];
  // copy items over
  int j = 0;
  for (int i = head; i != tail; i = mod(i+1, mx_sz + 1))
  {
    content_arr[j] = data[i];
    j++;
  }
  return content_arr;
}

// --- clear -- //
template <typename E>
void CBL<E>::clear()
{
  head = 0;
  tail = 0;

  if (mx_sz >= 100)
  {
    mx_sz = (mx_sz*3)/4;
    delete [] data;
    data = new E[mx_sz+1];
  }
}

// --- print_contents --- //
template <typename E>
void CBL<E>::print_contents()
{

  if (is_empty())
  {
    throw std::runtime_error("void CBL<E>::print_contents(): list empty");
  } else {
    std::cout << "CONTENTS: " ;
    E* arr = contents();
    for (int i = 0; i < length(); i++)
    {
      std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    delete [] arr;
  }
}

// --- replace --- //
template <typename E>
E CBL<E>::replace(E elt, int pos)
{
  if (is_empty())
  {
    throw std::runtime_error("E CBL<E>::item_at(int pos): list empty");
  } else if (pos < 0 || pos > length()-1) {
    throw std::runtime_error("E CBL<E>::item_at(int pos): index out of domain");
  } else {
    int act_pos = mod(head+pos, mx_sz+1);
    E popped = data[act_pos];
    data[act_pos] = elt;
    return popped;
  }
}

// --- pop_front --- //
template <typename E>
E CBL<E>::pop_front()
{
  if (is_empty())
  {
    throw std::runtime_error("E CBL<E>::pop_front(): list empty");
  } else {
    E popped = data[head];
    inc_head();
    if (mx_sz >= 100 && length() < mx_sz/2)
    {
      int new_mx_sz = (mx_sz*3)/4;
      E* new_data = new E[new_mx_sz+1];

      // copy items over
      int j = 0;
      for (int i = head; i != tail; i = mod(i+1, mx_sz + 1))
      {
        new_data[j] = data[i];
        j++;
      }

      // set this new array as the data[]
      // deallocate old array
      delete [] data;
      mx_sz = new_mx_sz;
      data = new_data;
      head = 0;
      tail = j;

    }
    return popped;
  }
}

// --- pop_back --- //
template <typename E>
E CBL<E>::pop_back()
{
  if (is_empty())
  {
    throw std::runtime_error("E CBL<E>::pop_back(): list empty");
  } else {
    E popped = data[mod(tail-1, mx_sz+1)];
    dec_tail();
    if (mx_sz >= 100 && length() < mx_sz/2)
    {
      int new_mx_sz = (mx_sz*3)/4;
      E* new_data = new E[new_mx_sz+1];

      // copy items over
      int j = 0;
      for (int i = head; i != tail; i = mod(i+1, mx_sz + 1))
      {
        new_data[j] = data[i];
        j++;
      }

      // set this new array as the data[]
      // deallocate old array
      delete [] data;
      mx_sz = new_mx_sz;
      data = new_data;
      head = 0;
      tail = j;
    }
    return popped;
  }
}

// --- insert --- //
template <typename E>
void CBL<E>::insert(E elt, int pos)
{
  if (is_empty())
  {
    throw std::runtime_error("void CBL<E>::insert(E elt, int pos): list empty");
  } else if (is_full()){
    // just need to make the list fatter and then call insert again.

    // Need to make a new array that is 150% bigger than the OG
    int new_mx_sz = ((mx_sz)*3)/2;
    E* new_data = new E[new_mx_sz+1];

    // copy items over
    int j = 0;
    for (int i = head; i != tail; i = mod(i+1, mx_sz + 1))
    {
      new_data[j] = data[i];
      j++;
    }

    // set this new array as the data[]
    // deallocate old array
    delete [] data;
    mx_sz = new_mx_sz;
    data = new_data;
    head = 0;
    tail = j;

    int act_pos = mod(head+pos, mx_sz+1);
    // move all the elements over 1
    for (int i = tail; i != act_pos; i = mod(i-1, mx_sz+1))
    {
      data[i] = data[mod(i-1, mx_sz+1)];
    }
    data[act_pos] = elt;
    inc_tail();

  } else if (pos < 0 || pos > length()-1){
    throw std::runtime_error("void CBL<E>::insert(E elt, int pos): index outside of domain");
  } else {
    int act_pos = mod(head+pos, mx_sz+1);
    // move all the elements over 1
    for (int i = tail; i != act_pos; i = mod(i-1, mx_sz+1))
    {
      data[i] = data[mod(i-1, mx_sz+1)];
    }
    data[act_pos] = elt;
    inc_tail();
  }
}

// --- remove --- //
template <typename E>
E CBL<E>::remove(int pos)
{
  if (is_empty())
  {
    throw std::runtime_error("E CBL<E>::remove(int pos): list empty");
  } else if (pos < 0 || pos > length()-1 ){
    throw std::runtime_error("E CBL<E>::remove(int pos): index not in domain");
  } else {
    int act_pos = mod(head+pos, mx_sz+1);
    E removed = data[act_pos];
    // move all the elements over 1
    for (int i = act_pos; i != tail; i = mod(i+1, mx_sz+1))
    {
      data[i] = data[mod(i+1, mx_sz+1)];
    }
    dec_tail();

    if (mx_sz >= 100 && length() < mx_sz/2)
    {
      int new_mx_sz = (mx_sz*3)/4;
      E* new_data = new E[new_mx_sz+1];

      // copy items over
      int j = 0;
      for (int i = head; i != tail; i = mod(i+1, mx_sz + 1))
      {
        new_data[j] = data[i];
        j++;
      }

      // set this new array as the data[]
      // deallocate old array
      delete [] data;
      mx_sz = new_mx_sz;
      data = new_data;
      head = 0;
      tail = j;
    }
    return removed;
  }
}



// - inc/dec functions - //
// --- dec_head --- //
template <typename E>
void CBL<E>::dec_head()
{
  head = mod(head - 1, mx_sz+1);
}

// --- inc_tail --- //
template <typename E>
void CBL<E>::inc_tail()
{
  tail = mod(tail + 1, mx_sz+1);
}

// --- inc_head --- //
template <typename E>
void CBL<E>::inc_head()
{
  head = mod(head + 1, mx_sz+1);
}

// --- dec_tail --- //
template <typename E>
void CBL<E>::dec_tail()
{
  tail = mod(tail - 1, mx_sz+1);
}

// --- print --- //
template <typename E>
std::ostream& CBL<E>::print(std::ostream &out)
{
  if(is_empty())
  {
    out << "<empty list>";
  } else {
    out << "[";
    size_t size = length();
    E* list = contents();
    for (size_t i = 0; i < size; ++i)
    {
      if (i == size-1)
        out << list[i];
      else
        out << list[i] << ",";
    }
    out << "]";
  }
  return out;
}

// --- contains --- //
template <typename E>
bool CBL<E>::contains(E elt, bool (*equals_fn)(E a, E b))
{
  if (is_empty())
  {
    return false;
  }
  bool exists = false;
  for (auto thing : *this)
  {
    if (equals_fn(thing, elt)){
      exists = true;
      break;
    }
  }
  return exists;
}


}
#endif
