#include "SSLL.h"
#include "PSLL.h"
#include "SDAL.h"
#include <iostream>

int main()
{
  cop3530::List<char> * list  = new cop3530::SDAL<char>();
  // for (int i = 0; i < 11; ++i){
  //   list->insert(i, 0);
  // }
  // list->insert(1,0);
  // list->clear();
  //
  // list->insert(9,0);
  // std::cout << list->peek_front() << std::endl;
  // std::cout << list->peek_back() << std::endl;
  // list->insert(5,0);
  // list-
  list->insert('A', 0);
  // list->push_back('A');
  std::cout << list->length() << std::endl;
  list->print(std::cout);
  return 0;
}
