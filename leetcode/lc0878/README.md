# Leetcode 878 - Consecutive Numbers Sum
A positive integer is magical if it is divisible by either `A` or `B`.

Return the `N`-th magical number.  Since the answer may be very large, return it modulo `10^9 + 7`.

- **Example 1**:

| **N** | **A** | **B** | **Result** |
| :---: | :---: | :---: | :--------: |
|   1   |   2   |   3   |     2      |

- **Example 2**

| **N** | **A** | **B** | **Result** |
| :---: | :---: | :---: | :--------: |
|   4   |   2   |   3   |     6      |

- **Example 3**

| **N** | **A** | **B** | **Result** |
| :---: | :---: | :---: | :--------: |
|   5   |   2   |   4   |     10     |

- **Example 4**

| **N** | **A** | **B** | **Result** |
| :---: | :---: | :---: | :--------: |
|   3   |   6   |   4   |     8      |

*Note*: `1 <= N <= 10 ^ 9, 2 <= A <= 40000, 2 <= B <= 40000`.

## Algorithm

There is a quick algorithm to solve this mathematic problem. Unlike other algorithms, the one we use is based on pure math. The time complexity is *almost* `O(1)`. Here I say *almost* because we still need to find the greatest common divisor of two input integers `A` and `B`, which actually requires `O(log min(A,B))` time with [**Euclidean Algorithm**](https://mathworld.wolfram.com/EuclideanAlgorithm.html).

In our implementation we directly use built-in function `std::__gcd` defined in header [`<algorithm>`](https://en.cppreference.com/w/cpp/header/algorithm). But note that this function is not a part of standard library, instead it is provided by `gcc`. Besides of that, another template built-in function [`std::gcd`](https://en.cppreference.com/w/cpp/numeric/gcd), defined in header [`<numeric>`](https://en.cppreference.com/w/cpp/header/numeric), is provided to compute the greatest common divisor of two integers since `C++17` . Of course we can also write our own `gcd` function easily... Well, I trust the built-in one, after all I'm a lazy guy :)

To illustrate our algorithm, let's take `A=10, B=28` as an example. Obviously the greatest common divisor of them is `gcd=2`, and so the period of *magic* numbers is `lcm=140`.

> **Theorem 1**: there are `(A+B)/gcd` *magic* numbers that are no larger than `lcm`.

**Proof**: a magic number `m` must be exactly divided by either `A` or `B`. Suppose `m<lcm`, then we claim that only one of `A|m` and `B|m` can be satisfied, otherwise `lcm|m` is satisfied and it's contradict to `m<lcm`. Therefore the number of *magic* numbers that is no larger than `lcm` is equal to the sum of multipliers of `A` and `B`.

Apparently, there are `lcm/A=B/gcd` multipliers of `A`, and similarly `A/gcd` multipliers of `B` that are no larger than `lcm`. Hence, the required number is `(A+B)/gcd`.

>**Theorem 2**: if `m<lcm` is a magic number, then `m+k*lcm` is also a magic number, where `k` is a positive integer. 

**Proof**: this theorem is quite simple. According to the given condition, we know that `A|m` or `B|m`.

- If `A|m`, then `(m+k*lcm)/A = m/A + k * (lcm/A)` should be an integer and we have `A|(m+k*lcm)`.
- If `B|m`, then `(m+k*lcm)/B = m/B + k * (lcm/B)` should be an integer and we have `B|(m+k*lcm)`.

Therefore, `m+k*lcm` must be a valid *magic* number.