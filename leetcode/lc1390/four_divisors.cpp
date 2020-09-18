#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

class Solution {
public:
  int sumFourDivisors(const std::vector<int>& nums) {
    int sum = 0;
    for (auto n : nums) sum += fourDivisorsNum(n);
    return sum;
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
    unsigned ub = static_cast<unsigned>(std::round(std::sqrt(num))) + 1;

    // Find possible divisors.
    for (unsigned k = 3; k < ub; k += 2)
      if (num % k == 0)
        return false;
    return true;
  }

  static int fourDivisorsNum(unsigned num) {
    if (num < 5) return 0;
    if (unsigned root = static_cast<unsigned>(std::round(std::cbrt(num)));
        isPrime(root) && std::pow(root, 3) == num)
      return 1 + root + root * root + num;

    if (num % 2 == 0)
      return isPrime(num / 2) ? (num + 3 + num / 2) : 0;

    unsigned ub = static_cast<unsigned>(std::round(std::sqrt(num))) + 1;
    for (unsigned k = 3; k < ub; k += 2) {
      if (num % k == 0 && num != k * k)
        return isPrime(num / k) ? (num + k + num / k + 1) : 0;
    }
    return 0;    
  }
};

int main() {
  std::vector<int> nums(30, 0);
  std::iota(nums.begin(), nums.end(), 1);
  for (auto n : nums)
    std::cout << n << ": " << Solution::fourDivisorsNum(n) << std::endl;
  return 0;
}

