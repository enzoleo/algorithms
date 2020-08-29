#ifndef _CANDY_HPP_
#define _CANDY_HPP_

#include <iostream>
#include <vector>

class Solution {
public:

  /**
   * This problem is not a classical dynamic programming problem...
   * I mean, this solution is also considered as a normal method.
   * Particularly, I don't think the iteration formula works like
   * other classical dp problem.
   *
   * This problem also has a extended version, e.g. the line of
   * children can be a circle instead.
   */
  static int candy(std::vector<int>& ratings) {
    // If the input vector has no data, simply return 0.
    int size = ratings.size();
    if (size == 0) return 0;

    int* arr = new int[size];
    arr[0] = 1;
    // Now let's apply the condition rules, if a children has higher
    // rating than the previous one, it should have more candies.
    for (int i = 1; i != size; ++i)
      if (ratings[i] > ratings[i - 1])
        arr[i] = arr[i - 1] + 1;
      else arr[i] = 1;

    // The above rule ignores the children who has higher rating than
    // the next one. So another tranversal should be applied. Note
    // that this loop should from the end of array to the beginning.
    for(int i = size - 1; i != 0; --i)
      if (ratings[i - 1] > ratings[i] &&
          arr[i - 1] <= arr[i])
        arr[i - 1] = arr[i] + 1;

    // Sum all candies in the buffer.
    int total = 0;
    for (int* p = arr, *end = arr + size; p != end; ++p)
      total += *p;

    return total;
  }

};

#endif


