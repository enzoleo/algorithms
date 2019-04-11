# Combat 001 - Coprime triples
这是一道在线笔试题目，当时没有做出来，觉得很有意思，考完回味一下这道题目，觉得有很多可以挖掘的地方。这道题目是这样的，给定一个正整数数组，数组的大小不超过99999，数组中的每个数也不超过99999，现在定义下面这样一个集合

<img src="https://github.com/enzoleo/algorithms/blob/master/combat/combat001/img/combat001_def.svg" width="500"></img>

题目要求输出上面定义的集合的特例`A1`的大小。这道题不是其他典型的算法题，有一些有趣的数学技巧。这里引入`B`集合簇的概念就是为了方便运算，因为我们的答案可以从反方向上考虑，也就是总数减去所有不互素的三元组的个数，但是`Ad`的大小是不好求的，因此转化为求`Bd`的大小，基于下面这个关系式。

<img src="https://github.com/enzoleo/algorithms/blob/master/combat/combat001/img/combat001_comp.svg" width="400"></img>

这里引入了[Möbius function](https://en.wikipedia.org/wiki/M%C3%B6bius_function)，基本的想法会在下面的内容中提到，是解决这个题目的关键所在。
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

<img src="https://github.com/enzoleo/algorithms/blob/master/combat/combat001/img/combat001_k3.svg" width="200"></img>

因此很直观地可以用容斥原理在解决这个看起来毫无头绪的问题：我们遍历所有的正整数d（当然实际上不可能做到），加上或减去能被它同时整除的三元组的个数，就能找到数组中所有的不互素三元组的个数。这么做的原因是有些三元组被重复计算，例如能被6整除的三元组一定也都能被2整除，也一定都能被3整除，所以重复计算的部分要被去除掉。能被d整除的三元组前面的符号应该是正还是负？这依赖于d的所有不同质因子数目，如果是奇数，应该加，是偶数，则应该减，可以联想到这其实就是[Möbius function](https://en.wikipedia.org/wiki/M%C3%B6bius_function)的值取负。这个想法听上去难以实现，后面会分析它的可行性。

上面的想法总结为下面的关系式。

<img src="https://github.com/enzoleo/algorithms/blob/master/combat/combat001/img/combat001_idea.svg" width="250"></img>

通过这个关系式求得`Bd`簇的大小，进而求得目标值。题目的难点在于Möbius function那段关系的推导。
# Feasibility
上面说了遍历所有正整数是不可能的，但我们也不需要遍历所有的正整数，只需要遍历在数组中出现的所有的因子。注意为什么这是可行的，题目中给出了每一个数组中的数都不超过99999，因此可以断定一点，每个数不同质因数的个数不超过6，因为`2*3*5*7*11*13*17`就已经溢出了，99999在数论中是一个不大的上界，我们可以高效地找出给定数的所有不同质因子，然而对所有质因子进行组合相乘就可以得到一个数所有的因子。为了同时计算出因子的Möbius函数值，可以用下面的方法计算30的所有因子（如果是偶数个质因子乘积，则为负）。

<table>
   <tr>
      <th>iterations</th>
      <th colspan="8" align="center">factors</th>
      <th>explanation</th>
   </tr>
   <tr>
      <th>0</th>
      <td>-1</td>
      <td colspan="7"></td>
      <td>initializion</td>
   </tr>
   <tr>
      <th>1</th>
      <td>-1</td>
      <td>2</td>
      <td colspan="6"></td>
      <td>multiplies -2</td>
   </tr>
   <tr>
      <th>2</th>
      <td>-1</td>
      <td>2</td>
      <td>3</td>
      <td>-6</td>
      <td colspan="4"></td>
      <td>multiplies -3</td>
   </tr>
   <tr>
      <th>3</th>
      <td>-1</td>
      <td>2</td>
      <td>3</td>
      <td>-6</td>
      <td>5</td>
      <td>-10</td>
      <td>-15</td>
      <td>30</td>
      <td>multiplies -5</td>
   </tr>
</table>

有一点需要注意的是，如果遇到60这样的数如何处理？按理说60有平方因子4，但是这里我们分解质因数的过程中把它看做和30等价，只用取不同的质因子就可以了。这样做会影响结果的值吗？不会，如果一个数有完全平方数作为其因子，其Möbius函数值为0，在算法中的贡献也为0；从另一方面角度考虑，如果一个数和60互素与它和30互素是完全等价的概念，因此把一个数替换成它对应的largest square-free factor，并不会产生任何影响。这里给一条Möbius函数的定义：

<img src="https://github.com/enzoleo/algorithms/blob/master/combat/combat001/img/combat001_mobius.svg" width="700"></img>

因此，我们需要做的事情是，维护一个`map`或者一个`array`，以便计算出现过的因子的次数。遍历输入数组的每一个数，对其进行质因数分解，并计算它所有square-free因子，将其在`map`或者`array`中的权重加1，这样一次遍历之后就能获得所有出现过的square-free因子的信息：数组中有多少个数能被它整除，然后最后的结果就很平凡了：只需要遍历一次这个`map`或者`array`，就能获得最后的答案。另外有一点，当数组中出现的质因子足够多的时候，`map`往往不是一个很好的选择，而应该优先使用`array`这样的顺序结构，毕竟题目中已经给出了99999这个数组大小的上界。使用`array`不像`map`可以把负数作为key，因此对于-6这样的因子，一个处理方法是让权重为负，例如给定数组中有5000个数能被6整除，那么维护的`array`（假设是`a`）在对应位置`a[6]`取值是-5000。

用一个简单的例子解释一下。假设输入数据是`{ 1, 2, 3, 4, 5, 6, 7, 8 }`，所有square-free因子包含`{ 2, 3, 5, 6, 7 }`，对应能够在数组中整除的数的个数分别为`{ 4, 2, 1, 1, 1 }`。因此总的非互素三元组的个数为`C(4, 3) = 4`，互素三元组的个数为`C(8, 3) - 4 = 52`，就是这个样例的答案。

更加详细的写法可以看代码。在`Makefile`里写了几个宏，可以修改内容决定使用`array`或者`map`作为算法实现的数据结构，还有一些其他的`USE_BASELINE`（和brute-force做比较）、`USE_INPUT`（使用用户输入）等。

