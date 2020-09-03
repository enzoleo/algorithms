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

In our implementation we directly use built-in function `__gcd` defined in header [`<algorithm>`](https://en.cppreference.com/w/cpp/header/algorithm). But note that this function is not a part of standard library, instead it is provided by `gcc`. Besides of that, another template built-in function [`std::gcd`](https://en.cppreference.com/w/cpp/numeric/gcd), defined in header [`<numeric>`](https://en.cppreference.com/w/cpp/header/numeric), is provided to compute the greatest common divisor of two integers since `C++17` . Of course we can also write our own `gcd` function easily... Well, I trust the built-in one, after all I'm a lazy guy :)

To illustrate our algorithm, let's take `A=10, B=28` as an example. Obviously the greatest common divisor of them is `gcd=2`, and so the period of *magic* numbers is `lcm=140`.

> **Theorem 1**: there are `(A+B)/gcd` *magic* numbers that are no larger than `lcm`.

**Proof**: a magic number `m` must be exactly divided by either `A` or `B`. Suppose `m<lcm`, then we claim that only one of `A|m` and `B|m` can be satisfied, otherwise `lcm|m` is satisfied and it's contradict to `m<lcm`. Therefore the number of *magic* numbers that is no larger than `lcm` is equal to the sum of multipliers of `A` and `B`.

Apparently, there are `lcm/A=B/gcd` multipliers of `A`, and similarly `A/gcd` multipliers of `B` that are no larger than `lcm`. Hence, the required number is `(A+B)/gcd`.

>**Theorem 2**: if `m<lcm` is a magic number, then `m+k*lcm` is also a magic number, where `k` is a positive integer. 

**Proof**: this theorem is quite simple. According to the given condition, we know that `A|m` or `B|m`.

- If `A|m`, then `(m+k*lcm)/A = m/A + k * (lcm/A)` should be an integer and we have `A|(m+k*lcm)`.
- If `B|m`, then `(m+k*lcm)/B = m/B + k * (lcm/B)` should be an integer and we have `B|(m+k*lcm)`.

Therefore, `m+k*lcm` must be a valid *magic* number.

>**Theorem 3**: if `m<lcm` is the `i`th magic number, then `m+k*lcm` is also the `i+k*unit`-th magic number, where `unit=(A+B)/gcd` is the total number of magic numbers in one period. 

**Proof**: this theorem is an extension of theorem 2. Note that each period has and only has `unit` magic numbers according to theorem 2. Now `m` is the `i`th magic number, then `m+lcm` is a magic number in the second period. For each magic number `m1<m` in the first period, `m1+lcm<m+lcm` is a magic number in the second period, therefore in the second period, there are `i-1` magic numbers less than `m+lcm` and `unit-i` magic numbers larger than `m+lcm`, which indicates that `m+lcm` is exactly the `i`th magic number in the second period, and the `i+unit`-th magic number in all.

Similarly we can make further extension. By mathematical induction, we can easily prove the conclusion provided by theorem 3.

From the above three theorems we know that the distribution of *magic* numbers is periodic. This helps us convert the problem of big numbers into problem of relatively small numbers. For example, we want to find the `n`th *magic* number given `A` and `B`, where `n` is very large. Let `unit` be `(A+B)/gcd`, then we do a simple modulo on `n`: `n = quot * unit + index`, where `index < unit`. Now we find the `index`-th *magic* number `p`. From **theorem 3**, we know that `p + quot * lcm` is exactly the `n`th *magic* number.

The problem now is very simple: *how to find the n-th magic number in the first period?*  This problem can be solved based on pure math in `O(1)` time once the greatest common divisor of two given integers is determined. Let's take the example above.

| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 10   |    | 20   |    | 30   | 40   |    | 50   |    | 60   | 70   |
|      | 14 |  | 28 |      |      | 42 |      | 56 |      | 70 |

This is all magic numbers in the first period. Here we always suppose `A<B`. We can find the indices of all multipliers of `B=14`. For example, there are `A/gcd=5` multipliers of `B` in the first period, and for `i=1,2,3,4,5`, we know that the `i`th multiplier of `B` has a index of `floor((i*B)/A)+i`, *e. g.* the index of 42 is `floor((3*14)/10)+3=7`. Therefore, our target is to find `i` such that the `n`th magic number is between `i`th and `i+1`-th multiplier of `B`.

We are going to solve the following inequality:

![](http://latex.codecogs.com/gif.latex?\left\lfloor\frac{kB}{A}+k\right\rfloor\leq n<\left\lfloor\frac{(k+1)B}{A}+k+1\right\rfloor)

The floor function has some special properties as its value locates between two integers. From the above inequality we get

![](http://latex.codecogs.com/gif.latex?\frac{nA}{A+B}-1<k<\frac{(n+1)A}{A+B})

We obtain the lower bound and upper bound of the target value. However, unfortunately, these two bounds are not tight enough for us to determine the valid integer, as there might be two integers that are not beyond the bounds.