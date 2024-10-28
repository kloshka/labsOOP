#include <iostream>
#include "include/lab1_16.h"

int main()
{
  int lhv, rhv;
  std::cout << "enter left value:";
  std::cin  >> lhv;
  std::cout << "enter right value:";
  std::cin  >> rhv;


  std::cout << "result: " << NOD(lhv,rhv) << std::endl;

  return 0;
}