#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "coprime_pairs.hpp"

int gcd(int a, int b, int c) {
  return std::__gcd(a, std::__gcd(b, c));
}

/**
 * Brute-force method to count the number of coprime triples.
 * This method is time-costing. Usually array with size of several hundreds
 * will cause long runtime.
 */
int baseline(int* arr, size_t n) {
  int cnt = 0;  
  for (size_t i = 0; i < n; ++i)
    for (size_t j = 0; j < i; ++j)
      for (size_t k = 0; k < j; ++k)
        if (gcd(arr[i], arr[j], arr[k]) == 1) ++cnt;
  return cnt;
}

int main()
{
#ifdef USE_INPUT
  int n;
#ifdef ARRAY_SIZE
  n = ARRAY_SIZE;
  std::cout << "User input (data only)." << std::endl;
#else
  std::cout << "User input (size and data)." << std::endl;
  std::cin >> n;
#endif
  std::vector<int> v(n, 0);
  for (int i = 0; i < n; ++i) std::cin >> v[i];
#else
  // Randomly generate an array with size of ARRAY_SIZE.
#ifdef ARRAY_SIZE
  int n = ARRAY_SIZE;
#else
  int n = 100000;
#endif
  std::vector<int> v(n, 0);
  srand(time(NULL));
#ifdef MAX_NUMBER
  int max = MAX_NUMBER - 1;
#else
  int max = 99999;
#endif
  for (int i = 0; i < n; i++)
    v[i] = rand() % max + 1;
  std::cout << "Array size: " << n << " (randomly generated)" << std::endl;
#endif

  // Construct the number factory object.
#ifdef USE_ARRAY
#ifdef MAX_NUMBER
  Factory<MAX_NUMBER> fac(v);
#else
  Factory<100000> fac(v);
#endif
#else
  Factory fac(v);
#endif

  // Print the count by brute-force. WARNING! this method is really time-
  // costing. So be careful to use it.
#ifdef USE_BASELINE
  std::cout << "Baseline: " << baseline(&v[0], n) << std::endl;
#endif
  // Print the result on the screen.
  std::cout << fac.compute() << std::endl;  
  return 0;
}


