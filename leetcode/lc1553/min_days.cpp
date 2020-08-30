#include <iostream>
#include <unordered_map>
#include <functional>

class Solution {
public:
  // Easy to follow the recursive way, but the performance might be limited
  // for even relatively small numbers.
  static int minDaysRecurse(int n) {
    if (n < 2) return 1;
    int res = minDaysRecurse(n - 1);
    if (n % 2 == 0) res = std::min(res, minDaysRecurse(n / 2));
    if (n % 3 == 0) res = std::min(res, minDaysRecurse(n / 3));
    return res + 1;
  }

  // The general strategy is the same as @minDaysRecurse, however, a new
  // memorization mechanism is added to avoid duplicate computation.
  static int minDaysMemorize(int n) {
    // Memorize the result to avoid duplicate computation.
    std::unordered_map<int, int> memo = { { 0, 1 }, { 1, 1 } };
    std::function<int(int)> minDaysMemRecurse =
        [&](int n) -> int {
          if (memo.count(n)) return memo[n];
          memo[n] = std::min(n % 2 + minDaysMemRecurse(n / 2),
                             n % 3 + minDaysMemRecurse(n / 3)) + 1;
          return memo[n];
        };
    return minDaysMemRecurse(n);
  }
  
  // A better solution compared to the previous one @minDaysRecurse. Redundant
  // function call is avoided to accelerate the algorithm. However, according
  // to the upper bound of @n, this iterative method still exceeds the limit
  // of required time complexity.
  static int minDaysBottomUp(int n) {
    // Allocation of a large array. -> The memory requirement is still very
    // large. For example, when n is 2*10^9, the size of memory space should
    // be 800MB (32-bit integer).
    int* dp = new int[n + 1];
    dp[0] = dp[1] = 1;
    for (int i = 2, end = n + 1; i < end; ++i) {
      // The following three lines are intuitive and easy to follow. Each time
      // we select the minimal one among the three (or fewer) numbers.
      dp[i] = dp[i - 1];
      if (i % 2 == 0) dp[i] = std::min(dp[i], dp[i / 2]);
      if (i % 3 == 0) dp[i] = std::min(dp[i], dp[i / 3]);
      ++dp[i];
    }
    int res = dp[n];
    
    // Free the allocated memory space.
    delete[] dp;
    return res;
  }
  
};

int main() {
  std::cout << Solution::minDaysMemorize(54748326) << std::endl;
  return 0;
}


