#include "SSLL.h"
#include <iostream>
using namespace cop3530;

int main()
{
  SSLL<int> list;
  // list.insert(5,0);
  list.push_front(5);
  list.pop_front();
  // std::cout << "Length: " << list.length() << std::endl;

  // list.insert('b',1);
  list.print(std::cout);
  return 0;
}
