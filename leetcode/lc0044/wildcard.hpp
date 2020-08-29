#ifndef _WILDCARD_HPP_
#define _WILDCARD_HPP_

#include <iostream>
#include <string>
#include <cstring>

/**
 * Matrix definition.
 * This is just a simple matrix class for solving the given problem.
 * The kernel of this struct is the overloading of operator[].
 */
template<class T>
struct Mat {
  constexpr Mat() = delete;
  Mat(T* data_, std::size_t rows_, std::size_t cols_) :
      data(data_), rows(rows_), cols(cols_) {  }

  T* operator[](int i) { return data + i * cols; }

  std::size_t rows, cols;
  T* data;
};

class Solution {
public:

  static bool isMatch(const std::string& s, const std::string& t) {
    // The size of the matrix. Note that the '+1' is important in this case.
    int rows = t.length() + 1, cols = s.length() + 1;
    bool *arr = new bool[rows * cols]();

    // Matrix declaration and initialization.
    Mat<bool> mat(arr, rows, cols);
    mat[0][0] = true;

    for (int i = 1; i < rows; ++i) {
      bool flag = t[i - 1] == '*';
      if (flag) {
        // If the current character of string @t is '*', we only need to
        // find the first substring of @s: s.substr(0, k+1) that can be
        // perfectly matched by t.substr(0, i).
        mat[i][0] = mat[i - 1][0];
        int k = 0;
        for (; k < cols; ++k)
          if (mat[i - 1][k]) break;

        // Now we find the objective @k, now with the character t[i-1] is
        // '*', we can match all substring of @s: s.substr(0, len) with
        // len >= k perfectly.
        for (int iter = k; iter < cols; ++iter)
          mat[i][iter] = true;
        continue;
      }
      for (int j = 1; j < cols; ++j) {
        if (t[i - 1] == '?' || t[i - 1] == s[j - 1])
          mat[i][j] = mat[i - 1][j - 1];
        else mat[i][j] = false;
      }   
    }
    bool ans = mat[rows - 1][cols - 1];
    // Remember to delete the space we dynamically allocated.
    delete[] arr;
    return ans;
  }
};

#endif




