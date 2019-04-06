#include <iostream>
#include <vector>
#include <string.h>
#include "max_coins.hpp"

int main()
{
  std::vector<int> v { 3, 1, 5, 8 };
  Solution sol;
  std::cout << sol.maxCoins(v) << std::endl;
  
  return 0;
}

