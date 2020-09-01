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

There is a quick algorithm to solve this mathematic problem.