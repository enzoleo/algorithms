#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>

class Solution {
public:
  static constexpr int N = 1000000007;
  static int nthMagicalNumber(int n, int a, int b) {
    // Calculate the gcd and lcm of two numbers.
    long gcd_unit = std::__gcd(a, b);
    long lcm_unit = a * b / gcd_unit;

    // Here @unit is the period. For example, all integers that is divisable by
    // either 5 or 11 are periodic in fact, as they can be written as a format
    // of 55k + r where k and r < k are some integers. For each k, the number
    // of valid r values is @unit = 15.
    int unit = (a + b) / gcd_unit - 1;

    // Therefore, given @n, we can find which period nth number locates at, and
    // the inner index of it inside the period.
    long quot = n / unit, index = n % unit;
    int a0 = std::min(a, b), b0 = std::max(a, b);
    int block = static_cast<int>(quot * lcm_unit % N);

    // If @index is zero, which indicates that @n is exactly divisable of @unit
    // and nth number is divisable of @lcm_unit.
    if (index == 0) return block;

    // Now find a number k such that:
    // floor(k*b0/a0)+k <= n < floor((k+1)*b0/a0)+(k+1).
    // From the definition of the floor function, we can easily deduce that
    // k must be inside the interval (n/(r+1) - 1, (n+1)/(r+1)), where r=b0/a0.
    int k = (index * a0) / (a0 + b0);

    // Both k and k+1 are likely to be the solution according to the inequality
    // we show above. However, only one is the true solution, so we filter one.
    int rec = (k * b0) / a0 + k, rec0 = ((k + 1) * b0) / a0 + k + 1;
    if (index >= rec0) ++k, rec = rec0;

    // Now find which divisor can divide nth number. A, or B?
    if (index == rec) return (k * b0 + block) % N;
    return ((index - k) * a0 + block) % N;
  }
};

int main() {
  std::cout << Solution::nthMagicalNumber(88785979, 29977, 39953) << std::endl;
  return 0;
}

