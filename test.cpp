
#include <iostream>
// #include "SSLL.h"
// #include "SDAL.h"
// #include "PSLL.h"
#include "CDAL.h"
// #include "CBL.h"
#include <vector>
using namespace cop3530;

template <typename D>
bool comparison_fn(D a, D b) {
  return (a == b) ? 1 : 0;
}


int main()
{
  CDAL<int> list;
  // list.push_front(5);
  // list.push_front(4);
  // list.push_front(3);
  // list.push_front(2);
  // list.push_front(1);
  // list.pop_front();
  // list.pop_back();

  for (int i = 0; i < 50; ++i)
  {
    list.push_back(12);
  }

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
