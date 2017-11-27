#include "SSLL.h"
#include "PSLL.h"
#include "SDAL.h"
#include "CDAL.h"
#include "CBL.h"
#include <iostream>
using namespace cop3530;

int main()
{
  // cop3530::List<int> *list = new cop3530::SSLL<int>();
  CBL<int> list;
  list.push_front(5);
  list.push_front(6);
  list.print(std::cout);
  std::cout << std::endl;

  CBL<int> list_cpy = list;

  std::cout << "List 1: ";
  list.print(std::cout);
  std::cout << std::endl;

  std::cout << "Copy:   ";
  list_cpy.print(std::cout);
  std::cout << std::endl;







  std::cout << std::endl;
  std::cout << "Pushing to list 1" << std::endl;
  list.push_back(88);

  std::cout << "List 1: ";
  list.print(std::cout);
  std::cout << std::endl;

  std::cout << "Copy:   ";
  list_cpy.print(std::cout);
  std::cout << std::endl;

  std::cout << std::endl;
  std::cout << "Pushing to Copy: " << std::endl;
  list_cpy.push_back(99);

  std::cout << "List 1: ";
  list.print(std::cout);
  std::cout << std::endl;

  std::cout << "Copy:   ";
  list_cpy.print(std::cout);
  std::cout << std::endl;




  return 0;
}
