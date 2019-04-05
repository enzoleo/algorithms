#ifndef _EDIT_DIST_HPP_
#define _EDIT_DIST_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <array>

class Solution {
public:
  static int minDistance(const std::string& w1, const std::string& w2) {
    int len1 = w1.length(), len2 = w2.length();
    int nrows = len1 + 1, ncols = len2 + 1;
    int total = nrows * ncols;
    
    int dmat[total];
    std::fill(dmat, dmat + total, 0);

    for (int i = 1; i < nrows; ++i) dmat[i * ncols] = i;
    for (int j = 1; j < ncols; ++j) dmat[j] = j;
    for (int i = 1; i < nrows; ++i)
    {
      char ch = w1[i - 1];
      for (int j = 1; j < ncols; ++j)
      {
        bool flag = ch != w2[j - 1];
        dmat[i * ncols + j] = 1 + std::min(dmat[(i - 1) * ncols + j],
                                           dmat[i * ncols + j - 1]);
        dmat[i * ncols + j] = std::min(dmat[i * ncols + j],
                                       dmat[(i - 1) * ncols + j - 1] + flag);
      }
    }    
    return dmat[total - 1];
  }
};

#endif

