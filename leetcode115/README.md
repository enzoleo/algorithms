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
