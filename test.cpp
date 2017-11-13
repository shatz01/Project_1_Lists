
#include <iostream>
// #include "SSLL.h"
// #include "SDAL.h"
#include "PSLL.h"
// #include "CDAL.h"
// #include "CBL.h"
using namespace cop3530;

template <typename D>
bool comparison_fn(D a, D b) {
  return (a == b) ? 1 : 0;
}


int main()
{

  PSLL<int> list;
  for (int i = 1; i < 11; ++i)
  {
    list.push_back(i);
  }
  // list.insert(99, 2);
  // list.insert(99, 0);
  list.insert(88, 9);
  list.replace(101, 4);
  list.remove(4);
  list.pop_back();
  list.pop_front();
  list.remove(2);

  list.push_front(8);

  for (auto &ptr : list)
  {
    ptr = 5;
  }
  std::cout << std::endl;


  list.print(std::cout);
  std::cout << std::endl;

  // std::cout << list.item_at() << std::endl;

  // for (int i = 0; i < 50; ++i)
  // {
  //   list.push_back(12);
  // }

  // list.print(std::cout);

  // std::cout << list.contains(2, comparison_fn) << std::endl;

  // for (auto &elt : list)
  // {
  //   elt = 99;
  // }
  // for (auto elt : list)
  // {
  //   std::cout << elt << std::endl;
  // }
  // std::cout << std::endl;

  // list.print(std::cout);
  // std::cout << list.contains(12, comparison_fn) << std::endl;

  return 0;
}
