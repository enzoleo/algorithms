# Combat 001 - Coprime triples
This interestring problem comes from an online examination.
> You are given an array of less than 100,000 positive integers, in which each integer is smaller than 100,000. Now you are required to find the number of coprime triples in this array.

We can set up this problem in a more mathematical way. Suppose we define following sets

<img src="https://github.com/enzoleo/algorithms/blob/master/combat/combat001/img/combat001_def.svg" width="500"></img>

We need to find the size of `A1`. This problem looks so complicated that one might have to use brute-force method, however, actually it is possible to borrow some interesting tricks from number theory to solve this problem in a beautiful way.

Here we define collection `B` for convenience, because we can re-think about this problem from a completely different perspective that we find the total number of all triples that is **NOT** coprime. Considering that  size of `Ad` is difficult to calculate, we compute size of `Bd` and leverage Möbius transformation to complete our calculation.

<img src="https://github.com/enzoleo/algorithms/blob/master/combat/combat001/img/combat001_comp.svg" width="400"></img>

Here [Möbius function](https://en.wikipedia.org/wiki/M%C3%B6bius_function) is used，whose basic concepts will be briefly introduced in the following section, which is the key to solve this problem.

## Idea
Suppose we just simply consider brute-force method, obviously we have to write 3 nested loops, which leads to `O(n^3)` time complexity. When the size of array grows to a large integer, the computation cost will be significant. Of course, it is still possible to consider brute-force algorithm as a baseline so we can efficiently check the correctness on a short array.
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
Suppose we have a number *d* which is able to exactly divide *k* numbers in the given array. Apparently, the total number of triples in which all 3 integers can be divided by *d* should be

<img src="https://github.com/enzoleo/algorithms/blob/master/combat/combat001/img/combat001_k3.svg" width="200"></img>

Therefore, intuitively we can apply [inclusion-exclusion principle](https://en.wikipedia.org/wiki/Inclusion–exclusion_principle
) to solve this compilcated problem. Tranverse all positive integers (of course it is *impossible*), count the number of triples that can be divided, then we can find the total number of non-coprime triples. Note that we need the inclusion-exclusion principle because there must be a lot of duplicate calculation. For example, if a triple can be divided by 6, then it can also be divided by 2 and 3 at the same time, so we have to exclude the duplicate numbers. If a number has even number of prime factors (e.g. 6 has two different factors 2 and 3), it should be excluded, otherwise it should be included. In number theory, it resembles the formulation of [Möbius function](https://en.wikipedia.org/wiki/M%C3%B6bius_function).
Well, it looks very hard to implement, so the following section will analyze its feasibility.

We conclude the above as the following formula.

<img src="https://github.com/enzoleo/algorithms/blob/master/combat/combat001/img/combat001_idea.svg" width="250"></img>

Compute the size of `Bd` collection via this formula and further calculate the target value. The most difficult part is the derivation of mathematical formulation according to Möbius function.
# Feasibility
As mentioned above, it is impossible to traverse all positive integers. Actually only factors that can divide one of the integers in the array should be considered. 

**Why is it feasible?** We know that each number in the array is less than 100,000, so it can be guaranteed that any number in this array has no more than 6 prime factors according to the fact that `2*3*5*7*11*13*17` overflows. As 100,000 is not a large upper bound, we can efficiently find all prime factors of a specific number less than 100,000 and then compute different combination to find all factors. For example, the process we compute all factors of 30 as well as its Möbius symbol (`+` if it has even prime factors, otherwise `-`) is shown in the following table.

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

You may ask how to handle a number that has a squared factor (60 has a squared factor 4=2^2). We take 60 as a n example. Actually we just need consider it equivalent to 30 in this array because 30 is the largest square-free factor of 60.

**Are they really equivalent?** Yes. In fact, if a number has a squared factor, the value of its Möbius function will be 0, which means that it contributes nothing to this algorithm; From another perspective, proposition *"a number is coprime to 60"* is completely equivalent to *"a number is coprime to 30"*. Therefore, it does not make any change if we substitute a number with its largest square-free factor. The following is the definition of Möbius function.

<img src="https://github.com/enzoleo/algorithms/blob/master/combat/combat001/img/combat001_mobius.svg" width="700"></img>

Therefore, what we need to do is to maintain a `map` or `array` structure to count the number of factors.

- Traverse each element in the given array and do factorization.
- After factorization, we obtain its prime factors. Then, just consider all possible combination to obtain its square-free factors and add to its weight in the `map` or `array`.
- After one traversal, we obtain information of square-free factors: how many numbers in the array can be exactly divided by one factor.
- Do another traversal on this `map` or `array` and compute the target value (number of non-coprime triples) according to Möbius function.

**Note:** If an array returns you enough factors, `array` is a better choice than `map` because the upper bound 100,000 is given. But `array` does not have negative indices so correspondingly we can change the symbol of weight in this case. For example, there are 5,000 numbers can be divided by 6 in the array, the weight `a[6]` (the sixth element in the maintained array, you may use `a[5]` in most cases) can be set to -5000.

Let us take a simple example. Suppose we are given the original array `{ 1, 2, 3, 4, 5, 6, 7, 8 }`. We compute all the square-free factors `{ 2, 3, 5, 6, 7 }` and corresponding weights `{ 4, 2, 1, 1, 1 }`. As only the first one is no less than 3, we know that the number of all non-coprime triples is `C(4, 3) = 4`, the number of coprime triples is `C(8, 3) - 4 = 52`. We get the answer! Of course it's a simple example, because we did not use Möbius function.

More details can be found in the code, especially the detailed implementation of all ideas. For simplicity, I write macros in the `Makefile`, so you can custom the data structure and other algorithm by these macros `USE_BASELINE` (enable brute-force), `USE_INPUT` (enable user-input array).
