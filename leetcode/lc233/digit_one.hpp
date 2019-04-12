#ifndef _DIGIT_ONE_HPP_
#define _DIGIT_ONE_HPP_

#include <iostream>
#include <vector>
#include <cmath>

class Solution {
public:
  
  static int countDigitOne(int number) {
    // For non-positive integers, return 0 directly.
    if (number < 1) return 0;
    int res = 0;
    long tmp = 1;
    for (int num = number, i = 0; num; num /= 10, tmp *= 10, ++i) {
      // The last digit of current number. This iteration is possible to
      // be a little bit abstract.
      int digit = num % 10;
      if (digit == 0) continue;
      res += i * (tmp / 10) * digit;
      if (digit == 1)
        res += number % tmp + 1;
      else
        res += tmp;
    }
    return res;
  }
};

#endif


