#include <iostream>
#include <cmath>

class Solution {
public:
  // Suppose n can be represented as the sum of k consecutive integers, i.e.
  // n = a_1 + a_2 + ... + a_k, where a_{i+1} - a_i = 1.
  // Obviously, a_1 = n/k - (k-1)/2. Then we have the following two options:
  //    [1] Integer k is odd and k|n.
  //    [2] Integer k is even and k|(2*n), but k cannot divide n.
  // Besides, a_1 should be positive, so we have k(k-1) < 2n.
  // We are required to find all possible values of k for a given number n.
  static int consecutiveNumbersSum(int n) {
    // Use the conclusion that k(k+1) <= 2n to find the upper bound of k.
    // Solve the equation k^2 - k - 2*n = 0 we obtain the positive root
    // (sqrt(8*n + 1) + 1) / 2 as the upper bound.
    int ub = static_cast<int>(std::ceil(std::sqrt(2 * n + 0.25) + 0.5));
    int count = 0;
    for (int k = 1; k < ub; ++k)
      if ((2 * n - k * (k - 1)) % (2 * k) == 0) ++count;
    return count;
  }
};

int main() {
  std::cout << Solution::consecutiveNumbersSum(157895698) << std::endl;
  return 0;
}

