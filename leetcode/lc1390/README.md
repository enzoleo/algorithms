# Leetcode 1390 - Four Divisors
Given an integer array `nums`, return the sum of divisors of the integers in that array that have exactly four divisors. *If there is no such integer in the array, return 0*. 

**Example**:

|       Input       | Output |   Explanation   |
| :---------------: | :----: | :-------------: |
| `nums = [21,4,7]` |  `32`  | `32 = 1+3+7+21` |

**Constraints**:

- `1 <= nums.length <= 10^4`
- `1 <= nums[i] <= 10^5`

## Algorithm

The idea is very intuitive. Suppose we have a number n and its prime factorization

![](http://latex.codecogs.com/svg.latex?n=p_1^{\alpha_1}p_2^{\alpha_2}\cdots{}p_m^{\alpha_m})

Then the number of its divisors is

![](http://latex.codecogs.com/svg.latex?\tau(n)=\prod_{i=1}^m(1+\alpha_i)=(1+\alpha_1)(1+\alpha_2)\cdots(1+\alpha_m))

and the sum of all its divisors is

![](http://latex.codecogs.com/svg.latex?\sigma(n)=\prod_{i=1}^m\frac{p_i^{\alpha_i+1}-1}{p_i-1}=\frac{p_i^{\alpha_i+1}-1}{p_i-1}\frac{p_2^{\alpha_2+1}-1}{p_2-1}\cdots\frac{p_m^{\alpha_m+1}-1}{p_m-1})

Therefore, if we want ![](http://latex.codecogs.com/svg.latex?\tau(n)) to be equal to 4 exactly, there only exist two options for us to select

- ![](http://latex.codecogs.com/svg.latex?n=p_1p_2) is the product of two primes.
- ![](http://latex.codecogs.com/svg.latex?n=p^3) is the cubic number of a prime.

The most intuitive algorithm is to traverse all entries in the given array and check whether this entry is covered in the above two options.

Trivial cases are numbers less than 5 and all even numbers. An even number has only 4 divisors if and only if it is a product of 2 and an odd prime or it is 8 exactly.

```c++
// Trivial cases.
if (num < 5) return 0;
if (num == 8) return 15;
if (num % 2 == 0)
  return isPrime(num / 2) ? (num + 3 + num / 2) : 0;
```

For non-trivial cases, we are required to traverse odd primes.

```c++
// Non-trivial cases. Traverse all odd numbers less than the square root.
unsigned ub = static_cast<unsigned>(std::round(std::sqrt(num))) + 1;
for (unsigned k = 3; k < ub; k += 2) {
  // Note once we have num % k == 0, it is guaranteed that k is a prime,
  // otherwise any of its prime divisor should have been visited before.
  if (num % k == 0 && num != k * k)
    return (isPrime(num / k) || num / k == k * k) ?
        (num + k + num / k + 1) : 0;
}
```

The algorithm is fast enough.