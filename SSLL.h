#ifndef _SSLL_H_
#define _SSLL_H_
#include "list.h"
#include <stdexcept>

namespace cop3530{
template <typename E>
struct Node
{
  E data;
  Node *next;
};

template <typename E>
class Ssll : public List<E>
{
public:
  Ssll();
  ~Ssll();
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
  bool contains(E elt, bool (*equals_fn)(E a, E b)); // fix this to make it take a function arg too
  E* contents(); // should return an array
private:
  Node<E> *head;
  Node<E> *tail;

public:
  // ITERATOR CLASS
  template <typename DataT>
  class SSLL_Iter
  {
  public:
    // type aliases required for C++ iterator compatibility
    using value_type = DataT;
    using reference = DataT&;
    using pointer = DataT*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    // type aliases for prettier code
    using self_type = SSLL_Iter;
    using self_reference = SSLL_Iter&;

  private:
    Node<DataT>* here;

  public:
    explicit SSLL_Iter( Node<DataT>* start = nullptr ) : here( start ) {}
    SSLL_Iter( const SSLL_Iter& src ) : here( src.here ) {}

    reference operator*() const {
      return here->data;
    }
    pointer operator->() const {
      return &(operator*());
    }

    self_reference operator=( SSLL_Iter<DataT> const& src ) {
      if (this == &src) {
        return *this;
      }
      here = src;
      return *this;
    }

    self_reference operator++() {
      here = here->next;
      return *this;
    } // preincrement

    self_type operator++(int) {
      iterator preincremented = *this;
      here = here->next;
      return preincremented;
    } // postincrement

    bool operator==( SSLL_Iter<DataT> const& rhs ) const {
      return here == rhs.here;
    }

    bool operator!=( SSLL_Iter<DataT> const& rhs) const {
      return here != rhs.here;
    }
  }; // end SSLL_Iter

public:
  // type aliases for prettier code:
  using iterator = SSLL_Iter<E>;
  using const_iterator = SSLL_Iter<E const>;

  // iterators over a non-const List
  iterator begin() { return iterator(head); /* iterator denoting first element */ }
  iterator end() { return iterator(tail->next);/* iterator denoting 1 past the last element */ }

  // iterators over a const List
  const_iterator begin() const { return iterator(head)/* const_iterator denoting first element */; }
  const_iterator end() const { return iterator(tail->next)/* const_iterator denoting 1 past the last element */; }

}; // end ssll class definition

/// --- FUNCTIONS --- ///
// --- constructor --- ///
template <typename E>
Ssll<E>::Ssll()
{
  head = NULL;
  tail = NULL;
}
template <typename E>
Ssll<E>::~Ssll()
{
  while(head){
    Node<E> *prev = head;
    head = head->next;
    delete prev;
  }
}


// --- push_front --- //
template <typename E>
void Ssll<E>::push_front(E elt)
{

  if (is_empty())
  {
    Node<E> *temp = new Node<E>;
    temp->data = elt;
    // temp->next = head;
    head = temp;
    tail = temp;
  } else {
    Node<E> *temp = new Node<E>;
    temp->data = elt;
    temp->next = head; // point new node's next to old top of stack
    head = temp; // point top to the new top of stack
  }
}

// --- push_back --- //
template <typename E>
void Ssll<E>::push_back(E elt)
{
  if (is_empty())
  {
    Node<E> *temp = new Node<E>;
    temp->data = elt;
    // temp->next = head;
    head = temp;
    tail = temp;
  } else {
    Node<E> *temp = new Node<E>;
    temp->data = elt;
    tail->next = temp; // point new node's next to old top of stack
    tail = temp; // point top to the tail of stack
  }
}

// --- length --- //
template <typename E>
int Ssll<E>::length()
{
  int len = 0;
  Node<E> *temp = new Node<E>;
  temp = head;
  while (temp != tail)
  {
    len++;
    temp = temp->next;
  }
  len++;
  return len;
}

// --- contents -- //
template <typename E>
E* Ssll<E>::contents()
{
  if (is_empty())
  {
    return new E[0];
  } else {
    E* cont = new E[length()];

    Node<E> *temp = new Node<E>;
    temp = head;
    int i = 0;
    while (temp != tail)
    {
      cont[i] = temp->data;
      i = i + 1;
      temp = temp->next;
    }
    cont[i] = temp->data;
    return cont;
  }
}

// -- is_empty -- //
template <typename E>
bool Ssll<E>::is_empty()
{
  return(head == NULL && tail == NULL);
}

// --- pop_front --- //
template <typename E>
E Ssll<E>::pop_front()
{
  if (is_empty())
  {
    throw std::runtime_error("Ssll<E>.pop_front(): empty list");
  } else {
    Node<E> *temp = new Node<E>;
    temp = head;
    head = head->next;
    return temp->data;
  }
}

// --- pop_back --- //
template <typename E>
E Ssll<E>::pop_back()
{
  if (is_empty())
  {
    throw std::runtime_error("Ssll<E>.pop_back(): empty list");
  } else {
    Node<E> *temp = new Node<E>;
    temp = tail;
    Node<E> *temp2 = new Node<E>;
    temp2 = head;
    while (temp2->next != tail)
    {
      temp2 = temp2->next;
    }
    tail = temp2;
    return temp->data;
  }
}

// --- peek_front --- //
template <typename E>
E Ssll<E>::peek_front()
{
  if (is_empty())
  {
    throw std::runtime_error("Ssll<E>.peek_front(): empty list");
  } else {
    return head->data;
  }
}

// --- peek_back --- //
template <typename E>
E Ssll<E>::peek_back()
{
  if (is_empty())
  {
    throw std::runtime_error("Ssll<E>.peek_front(): empty list");
  } else {
    return tail->data;
  }
}

// --- is_full --- //
template <typename E>
bool Ssll<E>::is_full()
{
  return false;
}

// --- clear --- //
template <typename E>
void Ssll<E>::clear()
{
  head = NULL;
  tail = NULL;
}

// --- item_at --- //
template <typename E>
E Ssll<E>::item_at(int pos)
{
  if (is_empty())
  {
    throw std::runtime_error("Ssll<E>::item_at(): list empty");
  } else if (pos < 0 || pos > length()-1) {
    throw std::runtime_error("Ssll<E>::item_at(): index not in domain");
  } else {
    // assuming 0-indexed

    Node<E> *temp = new Node<E>;
    temp = head;
    int curr_pos = 0;
    while (curr_pos < pos)
    {
      temp = temp->next;
      curr_pos++;
    }
    return temp->data;
  }
}

// --- remove --- //
template <typename E>
E Ssll<E>::remove(int pos)
{
  if (is_empty())
  {
    throw std::runtime_error("Ssll<E>::remove(): list empty");
  } else if (pos >= 0 && pos < length()){
    if (pos == 0){
      return pop_front();
    } else if (pos == length()-1) {
      return pop_back();
    } else {
      Node<E> *before = new Node<E>;
      Node<E> *during = new Node<E>;
      Node<E> *after = new Node<E>;
      before = head;
      during = head->next;
      after = during->next;
      int curr_pos = 1;
      while (curr_pos != pos)
      {
        before = before->next;
        during = during->next;
        after = after->next;
        curr_pos++;
      }
      before->next = after;
      return during->data;
    }
  } else {
    throw std::runtime_error("Ssll<E>::remove(): index not in domain");
  }
}

// --- insert --- //
template <typename E>
void Ssll<E>::insert(E elt, int pos)
{

  if (is_empty())
  {
    throw std::runtime_error("Ssll<E>::insert(): list empty");
  } else if (pos < 0 || pos > length()-1) {
    throw std::runtime_error("Sssll<E>::insert(): index not in domain");
  } else {
    if (pos == 0) {
      push_front(elt);
    } else {
      Node<E> *before = new Node<E>;
      Node<E> *during = new Node<E>;
      Node<E> *new_node = new Node<E>;
      new_node->data = elt;
      before = head;
      during = head->next;
      int curr_pos = 1;
      while(curr_pos != pos)
      {
        before = before->next;
        during = during->next;
        curr_pos++;
      }
      new_node->next = during;
      before->next = new_node;
    }
  }
}

// --- replace --- //
template <typename E>
E Ssll<E>::replace(E elt, int pos)
{
  if (is_empty())
  {
    throw std::runtime_error("Ssll<E>::replace(E elt, int pos): list empty");
  } else if (pos < 0 || pos > length()-1){
    throw std::runtime_error("Ssll<E>::replace(E elt, int pos): index out of domain");
  } else {
    if (pos == 0)
    {
      E result = pop_front();
      push_front(elt);
      return result;
    } else if (pos == length()-1 ){
      E result = pop_back();
      push_back(elt);
      return result;
    } else {
      E result = remove(pos);
      insert(elt, pos);
      return result;
    }
  }
}

// --- print --- //
template <typename E>
std::ostream& Ssll<E>::print(std::ostream &out)
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
bool Ssll<E>::contains(E elt, bool (*equals_fn)(E a, E b))
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
