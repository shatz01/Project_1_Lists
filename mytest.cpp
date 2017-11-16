#include "SSLL.h"
#include <iostream>
using namespace cop3530;

int main()
{
  SSLL<char> list;
  list.insert('a',0);
  // std::cout << "Length: " << list.length() << std::endl;

  // list.insert('b',1);
  list.print(std::cout);
  return 0;
}
