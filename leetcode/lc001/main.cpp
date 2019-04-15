#include <iostream>
#include <vector>
#include <unordered_map>
#include "two_sum.hpp"

int main()
{
  std::vector<int> nums = { 2, 7, 11, 15 };
  std::vector<int> ans = Solution::twoSum(nums, 9);
  for (auto &index : ans)
    std::cout << index << " ";
  std::cout << std::endl;
  return 0;
}

