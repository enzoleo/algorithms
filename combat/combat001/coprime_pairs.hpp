#ifndef _COPRIME_PAIRS_HPP_
#define _COPRIME_PAIRS_HPP_

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>

/**
 * This function aims to do factorization for a positive integer.
 *
 * @param n the positive interger to be factorized.
 * @param v the result vector which stores the DISTINCT prime factors of n.
 *
 * Note usually factorization is a time-consuming process for a big number,
 * however, if we are informed that the input integer is not too big, e.g.
 * no more than 99,999 in some specified problems, this algorithm does not
 * cost too much time, and more importantly, the result vector will have no
 * more than 6 elements because 2 * 3 * 5 * 7 * 11 * 13 * 17 = 510510.
 */
void factorize(size_t n, std::vector<int>& v) {
  size_t number = n;
  v.clear();
  for (int i = 2; i * i <= number; ++i)
    if (number % i == 0) {
      // Push the divisor into the vector only once.
      v.emplace_back(i);
      do number /= i; while (number % i == 0);
    }
  // If the @number is 1, all divisors have been pushed into the vector.
  if (number != 1)
    v.emplace_back(number);
}

#ifdef USE_ARRAY
template<size_t N>
#endif
class Factory {
public:
  constexpr Factory() = delete;
  Factory(const int* _arr, size_t _n) : arr(_arr), n(_n) {}
  Factory(const std::vector<int>& v) : arr(&v[0]), n(v.size()) {}

  size_t compute() {
    // Register primes of each number in the array into the stat.
#ifdef USE_ARRAY
    std::array<int, N> stat;
    stat.fill(0);
#else
    std::map<int, size_t> stat;
#endif
    for (const int *p = arr, *end = arr + n; p != end; ++p) {
      std::vector<int> divs;
      factorize(*p, divs);
      divisors(divs, stat);
    }
    size_t cnt = 0;
    
    // This function computes C(x, 3) for a positive integer. Note that
    // the result is possible to be a huge number, therefore `long` type
    // is needed for input x near 10^5.
    std::function<long(long)> combination =
        [](long x) { return x * (x - 1) * (x - 2) / 6; };
    for (auto it = stat.begin(), end = stat.end(); it != end; ++it) {
#ifdef USE_ARRAY
      int num = *it;
      if (num == 0) continue;
      else if (num < 0)
        cnt -= combination(-num);
      else
        cnt += combination(num);
#else
      int num = it->second;
      cnt += ((it->first < 0) ? -1 : 1) * combination(num);
#endif
    }
    size_t total = combination(n);
    return total - cnt;
  }

private:

#ifdef USE_ARRAY
  /**
   * This function computes different combinations of primes in @data, and
   * do some basic statistics. For example, given @data { 2, 3, 5 }, this
   * function will compute all combinations except 1: { 2, 3, 5, 6, 10, 15,
   * 30 }. All numbers which can be factorized to even number of primes will
   * get negative results.
   *
   * @param data the input primes.
   * @param stat the statistics array.
   *
   * Note here we use std::vector<int> instead of std::vector<size_t>. We
   * need an extra variable to distinguish those factors that can be
   * factorized to even number of primes. For a std::map, the key could be
   * negative, but for a std::vector, the index should always be positive.
   */
  void divisors(std::vector<int>& data, std::array<int, N>& stat) {
    // Initialize the divisors vector first, the size is 2 ^ n. Therefore
    // for a large number @n, this method should be deprecated.
    size_t n = data.size();
    std::vector<int> div(1 << n, -1);
    if (!n) return;

    // The total number of subsets (except the last element of the original
    // array) is 1 << (n - 1). For a small number n (here I mean 1 << n does
    // not exceed the representation range of size_t), it will not be a
    // huge number.
    for (size_t i = 0; i < n; ++i) {
      int multiplier = -data[i];
      for (size_t j = 0, size = 1 << i; j < size; ++j) {
        int divisor = div[j] * multiplier;
        div[j + size] = divisor;
        if (divisor < 0) --stat[-divisor];
        else ++stat[divisor];
      }
    }
  }
#else
  void divisors(std::vector<int>& data, std::map<int, size_t>& stat) {
    // Initialize the divisors vector first, the size is 2 ^ n. Therefore
    // for a large number @n, this method should be deprecated.
    size_t n = data.size();
    std::vector<int> div(1 << n, -1);
    if (!n) return;

    // The total number of subsets (except the last element of the original
    // array) is 1 << (n - 1). For a small number n (here I mean 1 << n does
    // not exceed the representation range of size_t), it will not be a
    // huge number.
    for (size_t i = 0; i < n; ++i) {
      int multiplier = -data[i];
      for (size_t j = 0, size = 1 << i; j < size; ++j) {
        int divisor = div[j] * multiplier;
        div[j + size] = divisor;
        ++stat[divisor];
      }
    }
  }
#endif
  // The data pointer and size. (we don't store it as std::vector, just
  // constant data is enough to solve this problem).
  const int* arr;
  const size_t n;
};

#endif

