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