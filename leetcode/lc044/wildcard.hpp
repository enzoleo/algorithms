#ifndef _WILDCARD_HPP_
#define _WILDCARD_HPP_

#include <iostream>
#include <string>
#include <cstring>

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
    int rows = t.length() + 1, cols = s.length() + 1;
    bool *arr = new bool[rows * cols]();

    Mat<bool> mat(arr, rows, cols);
    mat[0][0] = true;

    for (int i = 1; i < rows; ++i) {
      bool flag = t[i - 1] == '*';
      if (flag) mat[i][0] = mat[i - 1][0];
      for (int j = 1; j < cols; ++j) {
        if (flag) {
          for (int k = 0; k <= j; ++k)
            if (mat[i - 1][k])
              mat[i][j] = true;
        }
        else if (t[i - 1] == '?' || t[i - 1] == s[j - 1])
          mat[i][j] = mat[i - 1][j - 1];
        else mat[i][j] = false;
      }   
    }
    bool ans = mat[rows - 1][cols - 1];
    delete[] arr;
    return ans;
  }
};

#endif




