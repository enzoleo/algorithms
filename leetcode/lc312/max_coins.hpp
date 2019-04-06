#ifndef _MAX_COINS_HPP_
#define _MAX_COINS_HPP_

#include <iostream>
#include <vector>
#include <string.h>

class Solution {
public:

  // Clear the coins data for dynamic programming
  void clearCoins() {
    memset(coins, -1, sizeof(coins));
  }
  
  int maxCoins(const std::vector<int>& v) {
    if (v.empty()) return 0;
    this->ptr = &v[0];
    this->n = v.size();
    this->clearCoins();
    return maxCoins(0, n);
  }
  
  int maxCoins(size_t lb, size_t ub) {
    // This step is very important, because recursion goes time-consuming
    // dramatically as the array size increases. If one value has already
    // been computed, there is no need to do recursion to re-compute it.
    if (coins[lb][ub] != -1) return coins[lb][ub];
    if (lb >= ub) {
      coins[lb][ub] = 0;
      return 0;
    }
    // Compute the maximum coins. Note that before deleting all elements in
    // [lb, ub), there must be only one element in [lb, ub), we need to find
    // which element is last deleted from the array to maximize coins.
    int s = 0;
    for (size_t i = lb; i < ub; ++i) {
      int tmp = maxCoins(lb, i) + maxCoins(i + 1, ub)
          + ((lb == 0) ? 1 : ptr[lb - 1])
          * ((ub == n) ? 1 : ptr[ub]) * ptr[i];
      if (tmp > s) s = tmp;
    }
    // Record the coins once computed!
    coins[lb][ub] = s;
    return s;
  }

private:

  const int* ptr;
  size_t n;
  
  int coins[500][500];
  
};

#endif



