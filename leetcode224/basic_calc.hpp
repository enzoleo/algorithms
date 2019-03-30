#ifndef _BASIC_CALC_HPP_
#define _BASIC_CALC_HPP_

#include <iostream>
#include <string>
#include <stack>

/**
 * Note this method is not good enough in time and space both. The feedback
 * of leetcode tells that this program beats 0.00% of all submitted ones.
 *
 * Why? The stack element type is std::pair, which costs too much memory
 * space. Actually the original problem does not need such data structure,
 * because std::stack<int> or even just an index is enough to solve the
 * problem (after all there is no multiplication or division).
 */
using Stack = std::stack<std::pair<int, char> >;

class Solution {
public:
  
  static int calculate(const std::string& s) {
    // Initialize the stack with zeros.
    Stack stack;
    stack.emplace(0, 0);
    char* p = const_cast<char*>(&s[0]);
    char* end = p + s.length();
    for (; p != end; ++p) {
      char ch = *p;
      int tmp = 0;

      // If the current character is a number, we calculate the true number
      // hidden in the string. Note that we always assume the input string
      // is good enough so that we do not need to check whether it's valid.
      if (ch > 47 && ch < 58) {
        while (*p > 47 && *p < 58) {
          tmp = tmp * 10 + (*p - 48);
          ++p;
        }
        --p;
        // Update the stack with the new value.
        update(stack, tmp);
      } else {
        switch (ch) {
          case ' ': continue;
          case '+': stack.top().second = '+'; break;
          case '-': stack.top().second = '-'; break;
          case '(': stack.emplace(0, NULL); break;
          case ')':
            // If the current character is ')', we need the merge the last
            // two entries of the stack.
            tmp = stack.top().first;
            stack.pop();
            update(stack, tmp);
            break;
          default: exit(1);
        }
      }
    }
    return stack.top().first;
  }

private:

  static void update(Stack& stack, int num) {
    std::pair<int, char>& item = stack.top();
    char ch = item.second;
    item.second = 0;
    switch (ch) {
      case '+': item.first += num; break;
      case '-': item.first -= num; break;
      case 0: item.first = num; break;
      default: exit(1);
    }
  }
};

#endif


