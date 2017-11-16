#ifndef _PSLL_H_
#define _PSLL_H_
#include "List.h"
#include <stdexcept>

namespace cop3530{
template <typename E>
struct Node_psll
{
  E data;
  Node_psll *next;
};

template <typename E>
class PSLL : public List<E>
{
public:
  PSLL();
  ~PSLL();
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
  void print(std::ostream & out);
  E* contents(); // should return an array
  bool contains(E elt, bool (*equals_fn)(const E &a, const E &b));
private:
  void print_contents(); // prints the array returned from contents
  void print_free(); // prints the free list from 0 to the number of nodes in free list minus 1
  bool free_is_empty();
  int free_length ();
  Node_psll<E> pop_free();
  Node_psll<E> *head;
  Node_psll<E> *tail;
  Node_psll<E> *free_head;

public:
  // ITERATOR CLASS
  template <typename DataT>
  class PSLL_Iter
  {
  public:
    // type aliases required for C++ iterator compatibility
    using value_type = DataT;
    using reference = DataT&;
    using pointer = DataT*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    // type aliases for prettier code
    using self_type = PSLL_Iter;
    using self_reference = PSLL_Iter&;

  private:
    Node_psll<DataT>* here;

  public:
    explicit PSLL_Iter( Node_psll<DataT>* start = nullptr ) : here( start ) {}
    PSLL_Iter( const PSLL_Iter& src ) : here( src.here ) {}

    reference operator*() const {
      return here->data;
    }
    pointer operator->() const {
      return &(operator*());
    }

    self_reference operator=( PSLL_Iter<DataT> const& src ) {
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

    bool operator==( PSLL_Iter<DataT> const& rhs ) const {
      return here == rhs.here;
    }

    bool operator!=( PSLL_Iter<DataT> const& rhs) const {
      return here != rhs.here;
    }
  }; // end PSLL_Iter

public:
  // type aliases for prettier code:
  using iterator = PSLL_Iter<E>;
  using const_iterator = PSLL_Iter<E const>;

  // iterators over a non-const List
  iterator begin() { return iterator(head); /* iterator denoting first element */ }
  iterator end() { return iterator(tail->next);/* iterator denoting 1 past the last element */ }

  // iterators over a const List
  const_iterator begin() const { return iterator(head)/* const_iterator denoting first element */; }
  const_iterator end() const { return iterator(tail->next)/* const_iterator denoting 1 past the last element */; }


}; // end PSLL class definition

// --- constructor --- //
template <typename E>
PSLL<E>::PSLL()
{
  // Node_psll<E> *first_node = new Node_psll<E>;
  head = nullptr;
  tail = nullptr;
  free_head = nullptr;
}
template <typename E>
PSLL<E>::~PSLL()
{
  while(head)
  {
    Node_psll<E> *prev = head;
    head = head->next;
    delete prev;
  }
  while (free_head)
  {
    Node_psll<E> *prev_free = free_head;
    free_head = free_head->next;
    delete prev_free;
  }
}



// --- is_empty --- //
template <typename E>
bool PSLL<E>::is_empty()
{
  return (head == nullptr && tail == nullptr);
}

// --- is_full --- //
template <typename E>
bool PSLL<E>::is_full()
{
  return false;
}

// --- item_at --- //
template <typename E>
E PSLL<E>::item_at(int pos)
{
  if (is_empty())
  {
    throw std::runtime_error("SPSLL<E>::item_at(): list empty");
  } else if (pos < 0 || pos > length()-1) {
    throw std::runtime_error("PSLL<E>::item_at(): index not in domain");
  } else {
    // assuming 0-indexed

    Node_psll<E> *temp = new Node_psll<E>;
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

// --- free_is_empty --- //
template <typename E>
bool PSLL<E>::free_is_empty()
{
  return (free_head == nullptr);
}

// --- print_free --- //
template <typename E>
void PSLL<E>::print_free()
{
  if (free_is_empty())
  {
    throw std::runtime_error("free is empty");
  }
  Node_psll<E> *temp = new Node_psll<E>;
  temp = free_head;
  int i = 0;
  while (temp != NULL)
  {
    temp = temp->next;
    std::cout << i << " ";
    i++;
  }
  std::cout << std::endl;
}

// --- free_length() --- //
template <typename E>
int PSLL<E>::free_length()
{
  Node_psll<E> *temp = new Node_psll<E>;
  temp = free_head;
  int i = 0;
  while (temp != NULL)
  {
    temp = temp->next;
    i++;
  }
  return i;
}


// --- push_front --- //
template <typename E>
void PSLL<E>::push_front(E elt)
{
  if (free_is_empty())
  {
    if(is_empty()) // is_empty refers to the used list
    {
      Node_psll<E> *new_node = new Node_psll<E>;
      new_node->data = elt;
      head = new_node;
      tail = new_node;
    } else {
      Node_psll<E> *new_node = new Node_psll<E>;
      new_node->data = elt;
      new_node->next = head;
      head = new_node;
    }
  } else {
    if(is_empty()) // is_empty refers to the used list
    {
      Node_psll<E> *new_node = new Node_psll <E>;
      *new_node = pop_free();
      new_node->data = elt;
      head = new_node;
      tail = new_node;
    } else {
      Node_psll<E> *new_node = new Node_psll <E>;
      *new_node = pop_free();
      new_node->data = elt;
      new_node->next = head;
      head = new_node;
    }
  }
}

// --- push_back --- //
template <typename E>
void PSLL<E>::push_back(E elt)
{
  if (free_is_empty())
  {
    if(is_empty()) // is_empty refers to the used list
    {
      Node_psll<E> *new_node = new Node_psll<E>;
      new_node->data = elt;
      head = new_node;
      tail = new_node;
    } else {
      Node_psll<E> *new_node = new Node_psll<E>;
      new_node->data = elt;
      tail->next = new_node;
      tail = new_node;
    }
  } else {
    if(is_empty()) // is_empty refers to the used list
    {
      Node_psll<E> *new_node = new Node_psll <E>;
      *new_node = pop_free();
      new_node->data = elt;
      head = new_node;
      tail = new_node;
    } else {
      Node_psll<E> *new_node = new Node_psll <E>;
      *new_node = pop_free();
      new_node->data = elt;
      tail->next = new_node;
      tail = new_node;
    }
  }
}

// --- pop_front --- //
template <typename E>
E PSLL<E>::pop_front()
{
  if (is_empty())
  {
    throw std::runtime_error("E PSLL<E>::pop_front(): list empty");
  } else {
    E return_this;
    Node_psll<E> *temp = head;
    head = head->next;
    if (free_length() < 50)
    {
      temp->next = free_head;
      free_head = temp;
      return_this = free_head->data;
    } else {
      return_this = temp->data;
      delete temp;
    }

    // PRETTY SURE I DONT NEED ANY OF THIS ANYMORE SINCE NOW LENGTH OF FREE LIST WONT EXCEED 50.
    // code below is depreciated
    // if (length() >= 100 && (free_length() > length()/2))
    // {
    //   // reduce number of pool nodes to half list size by deallocation
    //   int half_list_sz = length()/2;
    //
    //   while (free_length() > half_list_sz)
    //   {
    //     Node_psll<E> *temp = new Node_psll<E>;
    //     temp = free_head;
    //     free_head = free_head->next;
    //     delete temp;
    //   }
    // }
    return return_this;
  }
}

// --- pop_back --- //
template <typename E>
E PSLL<E>::pop_back()
{
  if (is_empty())
  {
    throw std::runtime_error("E PSLL<E>::pop_back(): list empty");
  } if (length() == 1) {
    E data = head->data;
    if (free_length() < 50)
    {
      head->next = free_head;
      free_head = head;
    } else {
      delete head;
    }
    head = nullptr;
    tail = nullptr;
    return data;
  }

  else {
    E return_this;
    // Node_psll<E> *temp = new Node_psll<E>;
    // temp = head;
    // head = head->next;
    // temp->next = free_head;
    // free_head = temp;


    Node_psll<E> *temp = tail;
    Node_psll<E> *temp2 = head;

    while (temp2->next != tail)
    {
      temp2 = temp2->next;
    }
    tail = temp2;

    if (free_length() < 50 )
    {
      temp->next = free_head;
      free_head = temp;
      return_this = free_head->data;
    } else {
      return_this = temp->data;
      delete temp;
    }


    // PRETTY SURE I DONT NEED ANY OF THIS ANYMORE SINCE NOW LENGTH OF FREE LIST WONT EXCEED 50.
    // code below is depreciated
    // if (length() >= 100 && (free_length() > length()/2))
    // {
    //   // reduce number of pool nodes to half list size by deallocation
    //   int half_list_sz = length()/2;
    //
    //   while (free_length() > half_list_sz)
    //   {
    //     Node_psll<E> *temp = new Node_psll<E>;
    //     temp = free_head;
    //     free_head = free_head->next;
    //     delete temp;
    //   }
    // }
    return return_this;
  }

}

// --- peek_front --- //
template <typename E>
E PSLL<E>::peek_front()
{
  if (is_empty())
  {
    throw std::runtime_error("PSLL<E>.peek_front(): empty list");
  } else {
    return head->data;
  }
}


// --- peek_back --- //
template <typename E>
E PSLL<E>::peek_back()
{
  if (is_empty())
  {
    throw std::runtime_error("PSLL<E>.peek_front(): empty list");
  } else {
    return tail->data;
  }
}


// --- pop_free --- //
template <typename E>
Node_psll<E> PSLL<E>::pop_free()
{
  Node_psll<E> *temp = new Node_psll<E>;
  temp = free_head;
  free_head = free_head->next;
  return *temp;
}

// --- contents --- //
template <typename E>
E* PSLL<E>::contents()
{
  if (is_empty())
  {
    return new E[0];
  } else {
    E* cont = new E[length()];

    Node_psll<E> *temp = new Node_psll<E>;
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

// --- length --- //
template <typename E>
int PSLL<E>::length()
{
  if (is_empty())
  {
    return 0;
  } else {
    int len = 0;
    Node_psll<E> *temp = new Node_psll<E>;
    temp = head;
    while (temp != tail)
    {
      len++;
      temp = temp->next;
    }
    len++;
    return len;
  }
}

// --- print_contents --- //
template <typename E>
void PSLL<E>::print_contents()
{
  E *p = contents();
  std::cout << "CONTENTS: ";
  for (int i = 0; i < length() ; i++)
  {
    std::cout << p[i] << " ";
  }
  std::cout << std::endl;
}

// --- insert --- //
template <typename E>
void PSLL<E>::insert(E elt, int pos)
{
  if (is_empty())
  {
    throw std::runtime_error("PSLL<E>::insert(): list empty");
  } else if (pos < 0 || pos > length()-1) {
    throw std::runtime_error("SPSLL<E>::insert(): index not in domain");
  } else if (free_is_empty()) {

    if (pos == 0) {
      push_front(elt);
    } else {
      Node_psll<E> *before = new Node_psll<E>;
      Node_psll<E> *during = new Node_psll<E>;
      Node_psll<E> *new_node = new Node_psll<E>;
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
  } else {

    if (pos == 0) {
      push_front(elt);
    } else {
      Node_psll<E> *before = new Node_psll<E>;
      Node_psll<E> *during = new Node_psll<E>;
      Node_psll<E> *new_node = new Node_psll <E>;
      *new_node = pop_free();
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
E PSLL<E>::replace(E elt, int pos)
{
  if (is_empty())
  {
    throw std::runtime_error("PSLL<E>replace(E elt, int pos): list empty");
  } else if (pos < 0 || pos > length()-1){
    throw std::runtime_error("PSLL<E>replace(E elt, int pos): index out of domain");
  } else {
    E return_this;
    if(pos == 0)
    {
      return_this = head->data;
      head->data = elt;
    } else if (pos == length()-1) {
      return_this = tail->data;
      tail->data = elt;
    } else {
      Node_psll<E> *temp = new Node_psll<E>;
      temp = head;
      int curr_pos = 0;
      while (curr_pos < pos)
      {
        temp = temp->next;
        curr_pos++;
      }
      return_this = temp->data;
      temp->data = elt;
    }
    return return_this;
  }
}

// --- remove --- //
template <typename E>
E PSLL<E>::remove(int pos)
{
  if (is_empty())
  {
    throw std::runtime_error("E PSLL<E>::remove(int pos): list empty");
  } else if (pos < 0 || pos > length()-1) {
    throw std::runtime_error("E PSLL<E>::remove(int pos): index not in domain");
  } else {
    if (pos == 0){
      return pop_front();
    } else if (pos == length()-1) {
      return pop_back();
    }  else {
      Node_psll<E> *before = new Node_psll<E>;
      Node_psll<E> *during = new Node_psll<E>;
      Node_psll<E> *after = new Node_psll<E>;
      before = head;
      during = head->next;
      after = during->next;
      int curr_pos = 1;
      while(curr_pos != pos)
      {
        before = before->next;
        during = during->next;
        after = after->next;
        curr_pos++;
      }
      before->next = after;
      E return_this = during->data;
      if (free_length() < 50)
      {
        during->next = free_head;
        free_head = during;
      } else {
        delete during;
      }

      return return_this;
    }
  }
}


// --- clear --- //
template <typename E>
void PSLL<E>::clear()
{
  while(head)
  {
    Node_psll<E> *prev = head;
    head = head->next;
    delete prev;
  }
  while (free_head)
  {
    Node_psll<E> *prev_free = free_head;
    free_head = free_head->next;
    delete prev_free;
  }
  head = nullptr;
  tail = nullptr;
  free_head = nullptr;
}

// --- print --- //
template <typename E>
void PSLL<E>::print(std::ostream & out)
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
}

// --- contains --- //
template <typename E>
bool PSLL<E>::contains(E elt, bool (*equals_fn)(const E &a, const E &b))
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
