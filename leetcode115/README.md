# Leetcode 115 - Distinct Subsequence
典型的动态规划。

## Algorithm
可以用下面的递推式来描述整个计算过程：
![equation](https://latex.codecogs.com/gif.latex?f_%7Bs%2Ct%7D%28m%2Cn%29%3Df_%7Bs%2Ct%7D%28m-1%2Cn%29&plus;%5Cleft%5C%7B%20%5Cbegin%7Baligned%7D%20%260%5C%5C%20%26f_%7Bs%2Ct%7D%28m-1%2Cn-1%29%20%5Cend%7Baligned%7D%20%5Cbegin%7Baligned%7D%20%26%2C%5Ctext%7Bif%20%7Ds%5Bm%5D%3Dt%5Bn%5D%5C%5C%20%26%2C%5Ctext%7Belsewhere%7D%20%5Cend%7Baligned%7D%20%5Cright.)
