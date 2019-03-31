# Leetcode 115 - Distinct Subsequence
典型的动态规划。

## Algorithm
可以用下面的递推式来描述整个计算过程：

![equation](https://latex.codecogs.com/gif.latex?f_%7Bs%2Ct%7D%28m%2Cn%29%3Df_%7Bs%2Ct%7D%28m-1%2Cn%29&plus;%5Cleft%5C%7B%20%5Cbegin%7Baligned%7D%20%26f_%7Bs%2Ct%7D%28m-1%2Cn-1%29%5C%5C%20%260%20%5Cend%7Baligned%7D%20%5Cbegin%7Baligned%7D%20%26%2C%5Ctext%7Bif%20%7Ds%5Bm%5D%3Dt%5Bn%5D%5C%5C%20%26%2C%5Ctext%7Belsewhere%7D%20%5Cend%7Baligned%7D%20%5Cright.)

这里的![equation](https://latex.codecogs.com/gif.latex?f_%7Bs%2Ct%7D%28m%2Cn%29)表示字符串`s`的前`m`个字符组成的子串包含`t`的前`n`个字符组成的子串的数目。这个递推很容易写出来，因为如果`s[0:m]`的最后一个字符和`t[0:n]`的最后一个字符不同，那么`s[0:m]`的最后一个字符根本就没有起到作用；如果相同，那么就要多考虑`s[0:m-1]`中包含`t[0:n-1]`的个数。如果直接写一个递推，在字符串比较小的情况下问题很好解决。
```
size_t len1 = s.length();
size_t len2 = t.length();
int num = numDistinct(s.substr(0, len1 - 1), t);
if (s[len1 - 1] == t[len2 - 1])
  num += numDistinct(s.substr(0, len1 - 1),
                     t.substr(0, len2 - 1));
```
然而事实上字符串够大的情况下采用递归的写法很容易造成`Time Limit Exceeded`。

## Optimization
从另一个角度想问题，不用递归，而是从较小的`m,n`开始慢慢构造。

|result|-|b|ba|bag|
| :--- | :---: | --- | --- | --- |
|**-**|1||||
|**b**|1||||
|**ba**|1|1|||
|**bab**|1|2|1||
|**babg**|1|2|1|1|
|**babgb**|1|3|1|1|
|**babgba**|1|3|4|1|
|**babgbag**|1|3|4|5|

上面这个表格的思路就很明显了，除了第一列和第一行，每一个位置的值都是其上面一行对应位置的值或者再加上上面一行左边一列位置的值，这取决于在该处的行列索引对应到两个字符串的字符是否相等。这样计算就大大精简了计算过程。另外也没有必要使用一整个矩阵大小的内存，两个数组就足够了，一个（下面代码的`arr`）用来存取上一行的数据，另一个（下面代码中的`buffer`）计算当前行的数据，每次计算完成交换它们的位置。
```
uint *arr = new uint[len2 + 1];
uint *buffer = new uint[len2 + 1];
std::fill(arr, arr + len2 + 1, 0);
std::fill(buffer, buffer + len2 + 1, 0);
arr[0] = 1;

for (uint i = 1; i <= len1; ++i) {
  buffer[0] = 1;
  uint ub = std::min(i, len2);
  for (uint k = 1; k <= ub; ++k) {
    buffer[k] = arr[k];
    if (s[i - 1] == t[k - 1])
       buffer[k] += arr[k - 1];
  }
  std::swap(buffer, arr);
}
uint num = arr[len2];
delete[] arr;
delete[] buffer;
```
这个`num`也就是矩阵中最右下角的数据就是要求的值。实际上还可以更精简，因为根本不需要两个数组，一个数组就够了。假设我们现在有第`m-1`行的数据，存储在`buffer`中，那么下一次更新，每一个位置的值只用到当前位置的值和前一个位置的值，因此从数组的最后一个位置倒着更新就可以了。
```
uint nrows = s.length() + 1;
uint ncols = t.length() + 1;
if (nrows < ncols) return 0;

uint buffer[ncols];
std::fill(buffer, buffer + ncols, 0);
buffer[0] = 1;
for (uint i = 1; i != nrows; ++i) {
  uint ub = std::min(i, ncols - 1);
  char ch = s[i - 1];
  for (uint k = ub; k != 0; --k)
    if (ch == t[k - 1])
       buffer[k] += buffer[k - 1];
}
uint num = buffer[ncols - 1];
return num;
```
代码足够精简，时间和空间上的效果也上佳。
