#include <iostream>
#include <vector>
#include <functional>

class Solution {
public:
  using Mat = std::vector<std::vector<int> >;
  // A simple top-down approach with memorization.
  static int uniquePathsMem(unsigned m, unsigned n) {
    // The initialization of memorization array.
    Mat memo(m, std::vector<int>(n, -1));

    // Recursive lambda expression. Do not use `auto` to deduce the type.
    std::function<int(unsigned, unsigned)> uniquePathsRecurse =
        [&](unsigned i, unsigned j) -> int {
          // If the target is already calculated, skip and return.
          // Besides, directly return 1 if the search reaches the boundary.
          if (memo[i][j] > -1) return memo[i][j];
          if (i == 0 || j == 0) return memo[i][j] = 1;

          // The dynamic programming strategy.
          return memo[i][j] = uniquePathsRecurse(i - 1, j)
              + uniquePathsRecurse(i, j - 1);
        };
    return uniquePathsRecurse(m - 1, n - 1);
  }

  // A bottom-up approach to save memory.
  static int uniquePathsBottomUp(unsigned m, unsigned n) {
    std::vector<int> prev(m, 1), curr(m, 1);
    for (unsigned r = 1; r < n; ++r) {
      // Find the result of current row.
      for (unsigned i = 1; i < m; ++i)
        curr[i] = curr[i - 1] + prev[i];
      
      // Swap two rows, and now @curr becames previous row.
      std::swap(prev, curr);
    }
    return prev.back();
  }

  // A quick approach based on pure maths
  static int uniquePaths(unsigned m, unsigned n) {
    // You might have noticed that the result is exactly
    // Combination(n + m - 2, min(m, n) - 1).
    return ncomb(n + m - 2, std::min(m, n) - 1);
  }

  // A sample code to calculate combinatorial numbers.
  static unsigned ncomb(unsigned n, unsigned k) {
    // Corner cases.
    if (k > n) return 0;
    if (k == 0) return 1;

    // The symmetry of combinatorial numbers.
    if (k * 2 > n) k = n - k;
    long long res = n;
    for(unsigned i = 2, end = k + 1; i != end; ++i) {
      // Note the following division is always guaranteed to produce an int
      // result, so don't worry about exact division problems.
      // However, overflow after multiplication should be carefully handled.
      res *= (n - i + 1);
      res /= i;
    }
    return static_cast<int>(res);
  }
};

int main() {
  std::cout << Solution::uniquePaths(51, 9) << std::endl;
}


