#include "SSLL.h"
#include "PSLL.h"
#include <iostream>
using namespace cop3530;

int main()
{
  PSLL<int> list;
  // list.insert(5,0);
  list.insert(4,0);
  list.pop_front();
  // list.print(std::cout);
  // list.pop_front();
  // std::cout << "Length: " << list.length() << std::endl;

  // list.insert('b',1);
  // list.print(std::cout);
  return 0;
}
