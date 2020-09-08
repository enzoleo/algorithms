# Leetcode 233 - Number of Digit One
这个题目有点动态规划的意思。

## Algorithm
假如说给了我们一个数67412568，那么可以创建一个数组依次存放8，6，5，2，1，4，7，6这八个数字。用`f(n)`来表示不超过给定数的所有正整数里面，包含的数字1的总数。尝试用动态规划去解决这个问题。考虑第一个数字6和剩下的7412568，不超过这个给定数的数，在10^7这个位置上的数字可以是0-6，我们考虑下面这两种情况。

- **0 - 5**：这种情况，后面几位的数字可以任意取多少都可以。但是恰好是1的情况要单独考虑。
- **6**：这种情况下，这一位上的数字不用考虑了，后面几位数字组成的数不能超过7412568，这就是一个典型的动态规划问题了。

假设输入的数有n位，目标是求出`f(n)`，主要考虑这一位数字`v[n-1]`比2大的情况。此时若选取的比它小的数在该位恰好比`v[n-1]`小，那么后面的数字可以任意取，也就是说包含的所有满足条件的数字中含有数字1的个数为

![](http://latex.codecogs.com/gif.latex?\sum_{k=1}^{n-1}k\begin{pmatrix}n-1\cr{}k\end{pmatrix}\cdot{}9^{n-1-k}=(n-1)\cdot{}10^{n-2})

总结一下，递推公式可以写为下面的形式

![](https://latex.codecogs.com/svg.latex?f%28n%29%3Df%28n-1%29&plus;%5Cleft%5C%7B%20%5Cbegin%7Barray%7D%7Bll%7D%200%26%5Ctext%7B%2C%5C%3Bif%5C%3B%7Dv_%7Bn-1%7D%3D0%5Ccr%20%28n-1%29%5Ccdot%7B%7D10%5E%7Bn-2%7D&plus;N%5Ctext%7B%5C%2Cmod%5C%2C%7D10%5E%7Bn-1%7D&plus;1%26%5Ctext%7B%2C%5C%3Bif%5C%3B%7Dv_%7Bn-1%7D%3D1%5Ccr%20%28n-1%29%5Ccdot%7B%7D10%5E%7Bn-2%7D&plus;10%5E%7Bn-1%7D%26%5Ctext%7B%2C%5C%3Belsewhere%7D%20%5Cend%7Barray%7D%5Cright.)

一个简单的求和，问题就解决了。



