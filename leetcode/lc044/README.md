# Leetcode 044 - Wildcard matching
这道题目也是比较典型的动态规划，而且很有实际意义。所给的题目是，字符`*`可以匹配任意子字符串，字符`?`可以匹配任意的单个字符。显然`?`比`*`好处理得多，问题的关键就在于如何取处理`*`的匹配。

## Algorithm
用`f(m, n)`来表示字符串`t`的前`m`个字符是否能够匹配到`s`的前`n`个字符。对于一个动态规划问题来说，下一个目标就是找到这个`f(m, n)`是怎样进行递推的。注意`t[m-1]`也就是第`m`个字符可能出现的几种情况。

- **(a)-(z)**：正常字母只能和正常字母进行匹配，也就是说，当且仅当`s[n-1] == t[m-1]`的时候结果为真，否则为假；
- **(?)**：这个字符可以和任意`s`的字符匹配，因此可以默认为最后一个字符匹配成功；
- **(*)**：这个字符可以和任意字符串进行匹配，这种情况稍微麻烦一些，但我们断定一点，只要`t`的前`m-1`个字符能和`s`的前`k`个字符匹配，那么在这种情况下`t`的前`m`个字符一定能和`s`的任意前`l`个字符匹配，只要`l>=k`即可。

如果用公式抽象一下这个递推过程，就是

<a href="https://www.codecogs.com/eqnedit.php?latex=f(m,n)=\left\{&space;\begin{array}{ll}&space;\text{false}&,\text{if&space;}t[m-1]\neq&space;s[n-1]\text{&space;and&space;}t[m-1]\neq\texttt{`?'}\\&space;f(m-1,n-1)&,\text{if&space;}t[m-1]=s[n-1]\text{&space;or&space;}t[m-1]=\texttt{`?'}\\&space;\bigvee\limits_{i=0}^{n}&space;f(m-1,i)&space;&,\text{if&space;}t[m-1]=\texttt{`*'}&space;\end{array}&space;\right." target="_blank"><img src="https://latex.codecogs.com/gif.latex?f(m,n)=\left\{&space;\begin{array}{ll}&space;\text{false}&,\text{if&space;}t[m-1]\neq&space;s[n-1]\text{&space;and&space;}t[m-1]\neq\texttt{`?'}\\&space;f(m-1,n-1)&,\text{if&space;}t[m-1]=s[n-1]\text{&space;or&space;}t[m-1]=\texttt{`?'}\\&space;\bigvee\limits_{i=0}^{n}&space;f(m-1,i)&space;&,\text{if&space;}t[m-1]=\texttt{`*'}&space;\end{array}&space;\right." title="f(m,n)=\left\{ \begin{array}{ll} \text{false}&,\text{if }t[m-1]\neq s[n-1]\text{ and }t[m-1]\neq\texttt{`?'}\\ f(m-1,n-1)&,\text{if }t[m-1]=s[n-1]\text{ or }t[m-1]=\texttt{`?'}\\ \bigvee\limits_{i=0}^{n} f(m-1,i) &,\text{if }t[m-1]=\texttt{`*'} \end{array} \right." /></a>
