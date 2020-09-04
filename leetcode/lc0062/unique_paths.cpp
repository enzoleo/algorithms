#include <iostream>
#include <vector>
#include <functional>

class Solution {
public:
  using Mat = std::vector<std::vector<int> >;
  // A simple top-down approach with memorization.
  static int uniquePathsMem(unsigned int m, unsigned int n) {
    // The initialization of memorization array.
    Mat memo(m, std::vector<int>(n, -1));

    // Recursive lambda expression. Do not use `auto` to deduce the type.
    std::function<int(unsigned int, unsigned int)> uniquePathsRecurse =
        [&](unsigned int i, unsigned int j) -> int {
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
};

int main() {
  std::cout << Solution::uniquePathsMem(7, 3) << std::endl;
}


