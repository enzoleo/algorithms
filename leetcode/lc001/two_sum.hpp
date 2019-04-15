#ifndef _TWO_SUM_HPP_
#define _TWO_SUM_HPP_

#include <iostream>
#include <vector>
#include <unordered_map>

class Solution {
public:
  static std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    // Note why we use std::unordered_map. It is because this data structure
    // is implemented by hash table, so each time we look for the number it
    // only takes O(1) time, so the total time complexity will be O(n).
    std::unordered_map<int, int> map;
    std::vector<int> res;
    for (int i = 0, size = nums.size(); i != size; ++i) {
      int num = target - nums[i];
      auto tmp = map.find(num);
      if (tmp != map.end()) {
        res.emplace_back(tmp->second);
        res.emplace_back(i);
        return res;
      }
      map.emplace(nums[i], i);
    }
    return res;
  }
};

#endif

