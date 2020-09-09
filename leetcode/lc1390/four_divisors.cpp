#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

class Solution {
public:
  int sumFourDivisors(std::vector<int>& nums) {
    return 0;
  }

  // Check whether a given number is prime.
  // A lot of approaches can achieve our goal, however, their time complexity
  // varies significantly. Here as our input @num is less than 10^5, O(sqrt(n))
  // check is enough. Fermat test and Miller-Robin test should be much much
  // more efficient for extremely large numbers.
  static bool isPrime(unsigned num) {
    // Trivial cases.
    if (num < 2) return false;
    else if (num == 2) return true;
    else if (num % 2 == 0) return false;
    unsigned ub = static_cast<unsigned>(std::floor(std::sqrt(num))) + 1;

    bool res = true;
    for (unsigned k = 3; k < ub; k += 2)
      if (num % k == 0) {
        res = false;
        break;
      }
    return res;
  }
};

int main() {
  std::vector<int> nums(30, 0);
  std::iota(nums.begin(), nums.end(), 1);
  for (auto n : nums)
    std::cout << n << ": " << Solution::isPrime(n) << std::endl;
  return 0;
}

