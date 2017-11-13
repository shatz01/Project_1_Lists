#ifndef _CDAL_H_
#define _CDAL_H_

#include "list.h"
#include <stdexcept>

namespace cop3530{

template <typename E>
struct Node
{
  E *data = new E[50];
  Node* next;
  Node* prev;
};

template <typename E>
class CDAL : public List<E>
{
public:
  CDAL();
  ~CDAL();
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
  void clear(); ///
  E* contents();
  std::ostream& print(std::ostream &out);
  bool contains(E elt, bool (*equals_fn)(E a, E b));
private:
  void print_contents(); // prints the array returned from contents
  Node<E>* node_at(int index);
  int num_nodes();
  Node<E>* node_at_tail();
  void shift_right();
  void shift_right_from(int index);
  void delete_half();
  int total_nodes();
  Node<E> *head_node;
  int head;
  int tail;

public:
  // ITERATOR CLASS
  template <typename DataT>
  class CDAL_Iter
  {
  public:
    // type aliases required for C++ iterator compatibility
    using value_type = DataT;
    using reference = DataT&;
    using pointer = DataT*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    // type aliases for prettier code
    using self_type = CDAL_Iter;
    using self_reference = CDAL_Iter&;

  private:
    E* here;
    Node<E>* curr;
    size_t pos = 0;

  public:
    explicit CDAL_Iter( DataT* start , Node<E> *head_node) : here( start ), curr(head_node) {}
    CDAL_Iter( const CDAL& src, Node<E> *head_node ) : here( src.here ), curr(head_node) {}

    reference operator*() const {
      return *here;
    }
    pointer operator->() const {
      return &(operator*());
    }

    self_reference operator=( CDAL_Iter<DataT> const& src ) {
      if (this == &src) {
        return *this;
      }
      here = src;
      return *this;
    }

    self_reference operator++() {
      pos++;
      if (pos%50 == 0)
      {
        curr = curr->next;
        here = curr->data;
      } else {
        here++;
      }
      return *this;
    } // preincrement

    self_type operator++(int) {
      iterator preincremented = *this;
      pos++;
      if (pos%50 == 0)
      {
        curr = curr->next;
        here = curr->data;
      } else {
        here++;
      }
      return preincremented;
    } // postincrement

    bool operator==( CDAL_Iter<DataT> const& rhs ) const {
      return here == rhs.here;
    }

    bool operator!=( CDAL_Iter<DataT> const& rhs) const {
      return here != rhs.here;
    }
  }; // end CDAL_Iter

public:
  // type aliases for prettier code:
  using iterator = CDAL_Iter<E>;
  using const_iterator = CDAL_Iter<E const>;

  // iterators over a non-const List
  iterator begin() { return iterator(head_node->data, head_node); /* iterator denoting first element */ }
  iterator end() { return iterator(node_at_tail()->data + tail%50, head_node);/* iterator denoting 1 past the last element */ }

  // iterators over a const List
  const_iterator begin() const { return iterator(head_node->data, head_node)/* const_iterator denoting first element */; }
  const_iterator end() const { return iterator(node_at_tail()->data + tail%50, head_node)/* const_iterator denoting 1 past the last element */; }




}; // END CLAD CLASS DEFINITION

/// --- FUNCTIONS --- ///
// --- constructor --- //
template <typename E>
CDAL<E>::CDAL()
{
  // the chain starts off containing just a single array
  Node<E> *temp = new Node<E>;
  temp->next = nullptr;
  temp->prev = nullptr;
  head = 0;
  tail = 0;
  head_node = temp;
}

template <typename E>
CDAL<E>::~CDAL()
{
  while(head_node){
    Node<E> *previous = head_node;
    head_node = head_node->next;
    delete [] previous->data;
    delete previous;
  }
}



// --- length --- //
template <typename E>
int CDAL<E>::length()
{
  return tail;
}


// --- push_front --- //
template <typename E>
void CDAL<E>::push_front(E elt)
{
  if (is_empty())
  {
    head_node->data[0] = elt;
    tail = 1;
  } else {
    shift_right();
    head_node->data[0] = elt;
  }
}

// --- push_back --- //
template <typename E>
void CDAL<E>::push_back(E elt)
{
  if (is_empty())
  {
    head_node->data[0] = elt;
    tail = 1;
  } else if ((tail+1)%50 == 0 && tail == ((num_nodes()*50)-1)) {
    // traverse until you get to the tail, make another array, add tail to it
    Node<E> *end = node_at_tail();
    end->data[49] = elt;

    // attach a new array, then increment tail
    Node<E> *new_end = new Node<E>;
    new_end->next = nullptr;
    end->next = new_end;
    new_end->prev = end;
    ++tail;
  } else {
    Node<E> *end = node_at_tail();
    end->data[tail%50] = elt;
    ++tail;
  }
}

// --- pop_front --- //
template <typename E>
E CDAL<E>::pop_front()
{
  E elt = remove(0);
  return elt;
}

// --- pop_back --- //
template <typename E>
E CDAL<E>::pop_back()
{
  E elt = remove(tail-1);
  return elt;
}

// --- peek_front --- //
template <typename E>
E CDAL<E>::peek_front()
{
  if (is_empty())
    throw std::runtime_error("E CDAL<E>::peek_front(): list empty");
  return head_node->data[0];
}

// --- peek_back --- //
template <typename E>
E CDAL<E>::peek_back()
{
  if (is_empty())
    throw std::runtime_error("E CDAL<E>::peek_back(): list empty");
  Node<E> *tail_node = node_at(tail);
  int tail_remainder = tail%50;
  return tail_node->data[tail_remainder-1];
}

// --- item_at --- //
template <typename E>
E CDAL<E>::item_at(int pos)
{
  if (is_empty())
    throw std::runtime_error("E CDAL<E>::item_at(int pos): list empty");
  if (pos < 0 || pos >= tail)
    throw std::runtime_error("E CDAL<E>::item_at(int pos): position out of range");
  Node<E> *target_node = node_at(pos);
  int pos_remainder = pos%50;
  return target_node->data[pos_remainder];
}

// --- insert --- //
template <typename E>
void CDAL<E>::insert(E elt, int pos)
{
  if (pos < 0 || pos >= tail)
  {
    throw std::runtime_error("void CDAL<E>::insert(E elt, int pos): position out of range");
  } else {
    Node<E> *list = node_at(pos);
    shift_right_from(pos);
    list->data[pos%50] = elt;
  }
}

// --- replace --- //
template <typename E>
E CDAL<E>::replace(E elt, int pos)
{
  if (is_empty())
    throw std::runtime_error("E CDAL<E>::item_at(int pos): list empty");
  if (pos < 0 || pos >= tail)
    throw std::runtime_error("E CDAL<E>::item_at(int pos): position out of range");
  Node<E> *target_node = node_at(pos);
  int pos_remainder = pos%50;
  E replaced = target_node->data[pos_remainder];
  target_node->data[pos_remainder] = elt;
  return replaced;
}

// --- remove --- //
template <typename E>
E CDAL<E>::remove(int pos)
{
  // just need to shift all elements left starting from pos
  if (pos < 0 || pos >= tail)
    throw std::runtime_error("void CDAL<E>::remove(int pos): position out of range");
  // first navigate down to the first necessary list and find tail list
  Node<E> *tail_node = node_at_tail();
  Node<E> *pos_node = node_at(pos);
  Node<E> *traverse = pos_node;
  E removed = pos_node->data[pos];

  // now start shiftin'
  // std::cout << "got here"
  while (traverse != tail_node->next)
  {
    if (traverse == pos_node && traverse == tail_node){
      for (int i = pos%50; i < tail%50-1; ++i){
        if (i < 49)
          traverse->data[i] = traverse->data[i+1];
        else
          traverse->data[49] = (traverse->next)->data[0];
      }
    } else if (traverse == pos_node) {
      for (int i = pos%50; i < 50; ++i){
        if (i < 49)
          traverse->data[i] = traverse->data[i+1];
        else
          traverse->data[49] = (traverse->next)->data[0];
      }
    } else if (traverse == tail_node) {
      for (int i = 0; i < tail%50-1; ++i)
      {
        traverse->data[i] = traverse->data[i+1];
      }
    } else {
      for (int i = 0; i < 50; ++i)
      {
        if (i < 49)
          traverse->data[i] = traverse->data[i+1];
        else
          traverse->data[49] = (traverse->next)->data[0];
      }
    }
    traverse = traverse->next;
  }
  --tail;

  if (num_nodes() >= (((tail + 1)/50)+2) )
  {
    // find last node
    Node<E> *curr = head_node;
    while(curr->next != nullptr)
    {
      curr = curr->next;
    } // now curr is at the last node in CDAL

    (curr->prev)->next = nullptr;
    delete [] curr->data;
    delete curr;
  }
  // CODE BELOW IS DEPRECIATED
  // if (num_nodes()/2 > (tail/50 + 1))
  // {
  //   // deallocate half of nodes from end of list
  //   delete_half();
  // }

  return removed;
}

// --- delete_half --- // DEPRECIATED
template <typename E>
void CDAL<E>::delete_half()
{
  // find last node
  Node<E> *curr = head_node;
  while(curr->next != nullptr)
  {
    curr = curr->next;
  } // now curr is at the last node in CDAL

  // figure out how many nodes you need to delete
  int to_delete = num_nodes()/2;

  // delete the node and its data
  for (int i = 0; i < to_delete; ++i)
  {
    curr = curr->prev;
    delete[] curr->next->data;
    delete[] curr->next;
  }
  curr->next = nullptr;
}

// --- total_nodes --- //
template <typename E>
int CDAL<E>::total_nodes()
{
  Node<E> *curr = head_node;
  int amt_nodes = 0;
  while (curr != nullptr) {
    curr = curr->next;
    ++amt_nodes;
  }
  return amt_nodes;
}


// --- node_at_tail --- //
template <typename E>
Node<E>* CDAL<E>::node_at_tail()
{
  // value of tail signifies the end of the list
  // int remain = tail%50;
  int list = tail/50;

  Node<E> *temp = head_node;

  // move temp to the last list
  for (int i = 0; i < list; ++i)
  {
    temp = temp->next;
  }
  return temp;
}

// --- is_empty --- //
template <typename E>
bool CDAL<E>::is_empty()
{
  return (head == tail);
}

// --- is_full --- //
template <typename E>
bool CDAL<E>::is_full()
{
  return false;
}

// --- shift_right --- //
template <typename E>
void CDAL<E>::shift_right()
{
  Node<E> *temp = node_at_tail();
  // if tail is 49 at somewhere, need to make new array
  if ((tail+1)%50 == 0 && tail == ((num_nodes()*50)-1))
  {
    Node<E> *new_end = new Node<E>;
    temp->next = new_end;
    new_end->prev = temp;
    new_end->next = nullptr;
  }
  Node<E> *traverse = new Node<E>;
  traverse = temp; // traverse is at the end of the list
  while (traverse != nullptr)
  {
    if(traverse == temp) {
      for (int i = tail%50; i > 0; i--)
      {
        traverse->data[i] = traverse->data[i-1];
      }
      if (traverse != head_node)
      {
        traverse->data[0] = (traverse->prev)->data[49];
      }
    } else if (traverse != head_node) {
      for (int i = 49; i > 0; i--)
      {
        traverse->data[i] = traverse->data[i-1];
      }
      traverse->data[0] = (traverse->prev)->data[49];
    } else {
      for (int i = 49; i > 0; i--)
      {
        traverse->data[i] = traverse->data[i-1];
      }
    }
    traverse = traverse->prev;
  }
  ++tail;
}

// --- shift_right_from(int index) --- //
template <typename E>
void CDAL<E>::shift_right_from(int index)
{

  int list = index/50;

  Node<E> *index_node = new Node<E>;
  index_node = head_node;

  // move index to the list that will start shift
  for (int i = 0; i < list; ++i)
  {
    index_node = index_node->next;
  }

  // now index_node should be at the right node

  Node<E> *temp = node_at_tail();
  // if tail is 49 at somewhere, need to make new array
  if ((tail+1)%50 == 0 && tail == ((num_nodes()*50)-1))
  {
    Node<E> *new_end = new Node<E>;
    temp->next = new_end;
    new_end->prev = temp;
    new_end->next = nullptr;
  }
  Node<E> *traverse = new Node<E>;
  traverse = temp; // traverse is at the end of the list
  while (traverse != nullptr)
  {
    if(traverse == temp && traverse == index_node) {
      for (int i = tail%50; i > index; i--)
      {
        traverse->data[i] = traverse->data[i-1];
      }
      if (traverse != head_node)
      {
        traverse->data[0] = (traverse->prev)->data[49];
      }
    } else if (traverse == temp) {
      for (int i = tail%50; i > 0; i--)
      {
        traverse->data[i] = traverse->data[i-1];
      }
      if (traverse != head_node)
      {
        traverse->data[0] = (traverse->prev)->data[49];
      }
    } else if (traverse != index_node) {
      // std::cout << "SHould not b here " << std::endl;
      for (int i = 49; i > 0; i--)
      {
        traverse->data[i] = traverse->data[i-1];
      }
      traverse->data[0] = (traverse->prev)->data[49];
    } else {
      // std::cout << "Should b here" << std::endl;
      for (int i = 49; i > index%50; i--)
      {
        // std::cout << "rlly should b here" << std::endl;
        traverse->data[i] = traverse->data[i-1];
      }
    }
    traverse = traverse->prev;
  }
  ++tail;
}

// --- num_nodes --- //
template <typename E>
int CDAL<E>::num_nodes()
{
  Node<E> *temp = head_node;
  int i = 0;
  while(temp != nullptr){
    i++;
    temp = temp->next;
  }
  return i;
}

// --- contents --- //
template <typename E>
E* CDAL<E>::contents()
{
  Node<E> *temp = new Node<E>;
  temp = head_node;
  E* cont = new E[tail];
  int j = 0;

  Node<E> *tail_node = node_at_tail();

  while (temp != tail_node->next)
  {
    if(temp == tail_node)
    {
      for(int i = 0; i < tail%50; ++i)
      {
        cont[j] = temp->data[i];
        ++j;
      }
    } else {
      for(int i = 0; i < 50; ++i)
      {
        cont[j] = temp->data[i];
        ++j;
      }
    }
    temp = temp->next;
  }
  return cont;
}

// --- print_contents --- //
template <typename E>
void CDAL<E>::print_contents()
{
  std::cout << "Contents: ";
  E* cont = contents();
  for (int i = 0; i < tail; i++)
  {
    if (i%50 == 0)
    {
      std::cout << std::endl;
    }
    std::cout << cont[i] << " ";
  }
  std::cout << std::endl;
}

// --- node_at --- //
template <typename E>
Node<E>* CDAL<E>::node_at(int index)
{
  int list = index/50;

  Node<E> *temp = new Node<E>;
  temp = head_node;

  // move temp to the list with the index
  for (int i = 0; i < list; ++i)
  {
    temp = temp->next;
  }
  return temp;
}

// --- clear --- //
template <typename E>
void CDAL<E>::clear()
{
  // find the last node in the list
  // delete its data
  // delete the node
  // keep doing this until you get back to the head_node
  Node<E> *last_node = head_node;
  while(last_node->next != nullptr)
  {
    last_node = last_node->next;
  }

  while(last_node->prev != nullptr){
    last_node = last_node->prev;
    delete[] last_node->next->data;
    delete last_node->next;
  }

  // now just delete the head_node
  delete[] head_node->data;

  // now make a new start to the CDAL
  Node<E> *temp = new Node<E>;
  temp->next = nullptr;
  temp->prev = nullptr;
  head = 0;
  tail = 0;
  head_node = temp;


}

// --- print --- //
template <typename E>
std::ostream& CDAL<E>::print(std::ostream &out)
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
bool CDAL<E>::contains(E elt, bool (*equals_fn)(E a, E b))
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


} // close namespace cop3530

#endif
