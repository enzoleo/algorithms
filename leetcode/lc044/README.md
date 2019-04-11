# Leetcode 044 - Wildcard matching
这道题目也是比较典型的动态规划，而且很有实际意义。所给的题目是，字符`*`可以匹配任意子字符串，字符`?`可以匹配任意的单个字符。显然`?`比`*`好处理得多，问题的关键就在于如何取处理`*`的匹配。

## Algorithm
用`f(m, n)`来表示字符串`t`的前`m`个字符是否能够匹配到`s`的前`n`个字符。对于一个动态规划问题来说，下一个目标就是找到这个`f(m, n)`是怎样进行递推的。注意`t[m-1]`也就是第`m`个字符可能出现的几种情况。

- **(a) - (z)**：正常字母只能和正常字母进行匹配，也就是说，当且仅当`s[n-1] == t[m-1]`的时候结果为真，否则为假；
- **(?)**：这个字符可以和任意`s`的字符匹配，因此可以默认为最后一个字符匹配成功；
- **(*)**：这个字符可以和任意字符串进行匹配，这种情况稍微麻烦一些，但我们断定一点，只要`t`的前`m-1`个字符能和`s`的前`k`个字符匹配，那么在这种情况下`t`的前`m`个字符一定能和`s`的任意前`l`个字符匹配，只要`l>=k`即可。

如果用公式抽象一下这个递推过程，就是

![equation](https://latex.codecogs.com/gif.latex?f%28m%2Cn%29%3D%5Cleft%5C%7B%20%5Cbegin%7Barray%7D%7Bll%7D%20%5Ctext%7Bfalse%7D%26%2C%5Ctext%7Bif%20%7Dt%5Bm-1%5D%5Cneq%20s%5Bn-1%5D%5Ctext%7B%20and%20%7Dt%5Bm-1%5D%5Cneq%5Ctexttt%7B%60%3F%27%7D%5C%5C%20f%28m-1%2Cn-1%29%26%2C%5Ctext%7Bif%20%7Dt%5Bm-1%5D%3Ds%5Bn-1%5D%5Ctext%7B%20or%20%7Dt%5Bm-1%5D%3D%5Ctexttt%7B%60%3F%27%7D%5C%5C%20%5Cbigvee%5Climits_%7Bi%3D0%7D%5E%7Bn%7D%20f%28m-1%2Ci%29%20%26%2C%5Ctext%7Bif%20%7Dt%5Bm-1%5D%3D%5Ctexttt%7B%60*%27%7D%20%5Cend%7Barray%7D%20%5Cright.)

这个动态规划的式子就算完成了。程序实现只需要注意一下循环求或的步骤即可。下面给一个简单的例子来解释一下矩阵的构造过程。

|isMatch|-|a|ad|adc|adce|adceb|
| :--- | --- | --- | --- | --- | --- | --- |
|**-**|true|false|false|false|false|false|
|**\***|true|true|true|true|true|true|
|**\*a**|false|true|false|false|false|false|
|**\*a\***|false|true|true|true|true|true|
|**\*a*b**|false|false|false|false|false|true|

这个矩阵自上而下的构造然后取右下角的元素输出，就是问题的答案。
