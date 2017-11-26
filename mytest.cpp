#include "SSLL.h"
#include "PSLL.h"
#include "SDAL.h"
#include "CDAL.h"
#include <iostream>

int main()
{
  cop3530::List<int> *list = new cop3530::CDAL<int>();
  for (int i = 0; i < 1001; ++i) {
    list->push_back(i);
  }

  std::cout << "First peek back: " << list->peek_back() << std::endl;
  std::cout << "Popped from back: " << list->pop_back() << std::endl;
  // std::cout << "Pop another one: " << list->pop_back() << std::endl;

  list->print(std::cout);
  std::cout << std::endl;

  std::cout << "Now peek back: " << list->peek_back() << std::endl;



  return 0;
}
