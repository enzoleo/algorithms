# Leetcode 233 - Number of Digit One
A classical dynamic programming problem.

## Algorithm
Suppose we are given a number `N=67412568`, then we create a new array to store eight numbers `8,6,5,2,1,4,7,6` in order. Let `f(n)` be the target value for the given number `n`-digit number `N`, now we try to solve the problem by dynamic programming.

First consider the number `6` in the position `10^7`. Each valid number less than `N=67412568` could have `0-6` digit in that position.

- **0 - 5**: the first digit is strictly less than 6, then no matter how you select the rest digits, this number will always be valid.
- **6**: the first digit is exactly the same as that of `n`. In this case we should be careful, as the number produced by the rest digits we select should be less than `7412568`, then it's a sub-problem.

Consider general cases where we are given an `n`-digit number `N`, the first digit should be `v[n-1]`. If the number we select has a smaller digit at this position, then the total number of all valid numbers should be

![](http://latex.codecogs.com/gif.latex?\sum_{k=1}^{n-1}k\begin{pmatrix}n-1\cr{}k\end{pmatrix}\cdot{}9^{n-1-k}=(n-1)\cdot{}10^{n-2})

In summary, we have the following formula

![](https://latex.codecogs.com/svg.latex?f%28n%29%3Df%28n-1%29&plus;%5Cleft%5C%7B%20%5Cbegin%7Barray%7D%7Bll%7D%200%26%5Ctext%7B%2C%5C%3Bif%5C%3B%7Dv_%7Bn-1%7D%3D0%5Ccr%20%28n-1%29%5Ccdot%7B%7D10%5E%7Bn-2%7D&plus;N%5Ctext%7B%5C%2Cmod%5C%2C%7D10%5E%7Bn-1%7D&plus;1%26%5Ctext%7B%2C%5C%3Bif%5C%3B%7Dv_%7Bn-1%7D%3D1%5Ccr%20%28n-1%29%5Ccdot%7B%7D10%5E%7Bn-2%7D&plus;10%5E%7Bn-1%7D%26%5Ctext%7B%2C%5C%3Belsewhere%7D%20%5Cend%7Barray%7D%5Cright.)

Use bottom-up approach or just sum up the values, we can get the answer.



