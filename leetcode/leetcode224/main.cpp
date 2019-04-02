#include <iostream>
#include "basic_calc.hpp"

int main()
{
  std::string str("(( ( 23+ 45  - ( 38 +2))- 35))");
  std::cout << Solution::calculate(str) << std::endl;
  return 0;
}

