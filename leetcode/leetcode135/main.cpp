#include <iostream>
#include <vector>
#include "candy.hpp"

int main()
{
  int r[] = { 1, 3, 2, 2, 1 };
  std::vector<int> ratings(r, r + 5);
  std::cout << Solution::candy(ratings) << std::endl;
  return 0;
}
