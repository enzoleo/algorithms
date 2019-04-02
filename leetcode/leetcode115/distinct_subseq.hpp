#ifndef _DISTICT_SUBSEQ_HPP_
#define _DISTICT_SUBSEQ_HPP_

#include <iostream>
#include <string>

using uint = unsigned int;

class Solution {
public:
  static uint numDistinct(const std::string& s, const std::string& t) {

    // If the string @t is longer than @s, obviously the result is zero.
    uint nrows = s.length() + 1;
    uint ncols = t.length() + 1;
    if (nrows < ncols) return 0;

    // Now use only one array as buffer (initialize with 0).
    uint buffer[ncols];
    std::fill(buffer, buffer + ncols, 0);
    buffer[0] = 1;
    for (uint i = 1; i != nrows; ++i) {
      uint ub = std::min(i, ncols - 1);
      char ch = s[i - 1];
      for (uint k = ub; k != 0; --k)
        if (ch == t[k - 1])
          buffer[k] += buffer[k - 1];
    }
    uint num = buffer[ncols - 1];
    return num;
  }
};

#endif


