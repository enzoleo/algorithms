# Combat 001 - Coprime triples
这是一道在线笔试题目，当时没有做出来，觉得很有意思，考完回味一下这道题目，觉得有很多可以挖掘的地方。这道题目是这样的，给定一个正整数数组，数组的大小不超过99999，数组中的每个数也不超过99999，现在定义下面这样一个集合

![equation](https://latex.codecogs.com/gif.latex?A%3A%3D%5C%7B%28i%2Cj%2Ck%29%7C0%5Cleqslant%20i%3Cj%3Ck%5Cleqslant%20n-1%2C%5Ctext%7Bgcd%7D%28a_i%2Ca_j%2Ca_k%29%3D1%5C%7D)

题目要求输出这个集合的大小。这道题不是其他典型的算法题，有一些有趣的数学技巧。
## Idea
假如想到用brute-force做，三层循环遍历所有可能，显然这是`O(n^3)`的做法，对于一个长度可以达到99999的数组来说，计算代价太高。但是可以作为一个baseline检测后续算法的正确性，在数组长度只有几百的时候，这种方法还是很有效的。
```
int baseline(int* arr, size_t n) {
  int cnt = 0;  
  for (size_t i = 0; i < n; ++i)
    for (size_t j = 0; j < i; ++j)
      for (size_t k = 0; k < j; ++k)
        if (gcd(arr[i], arr[j], arr[k]) == 1) ++cnt;
  return cnt;
}
```
从其他角度来看这个问题，假设现在我们手中有这样一个数d，在数组中可以找出k个数能被它整除，显然，我们可以在数组中找到能被d同时整除的三元组的个数应该为

![equation](https://latex.codecogs.com/gif.latex?%5Cleft%28%5Cbegin%7Baligned%7Dk%5C%5C3%5Cend%7Baligned%7D%5Cright%29%3D%5Cfrac%7Bk%28k-1%29%28k-2%29%7D%7B6%7D)

因此很直观地可以用容斥原理在解决这个看起来毫无头绪的问题：我们遍历所有的正整数d（当然实际上不可能做到），加上或减去能被它同时整除的三元组的个数（这依赖于d的所有质因子数目，如果是奇数，应该加，是偶数，则应该减），就能找到数组中所有的不互素三元组。

