# Leetcode 1553 - Minimum Number of Days to Eat N Oranges
There are `n` oranges in the kitchen and you decided to eat some of these oranges every day as follows:

- Eat one orange.
- If the number of remaining oranges (`n`) is divisible by 2 then you can eat  `n/2` oranges.
- If the number of remaining oranges (`n`) is divisible by 3 then you can eat  `2*(n/3)` oranges.

You can only choose one of the actions per day.

Return the minimum number of days to eat `n` oranges.

## Algorithm

This problem can be solved in a classical way with dynamic programming. Given a number `n`, there exists three sub-problems as the first step can take three different actions.

- Eat one orange. The sub-problem begins with `n-1`.
- Eat `n/2` oranges. The sub-problem begins with `n/2`.
- Eat `2*(n/3)` oranges. The sub-problem begins with `n/3`.

Intuitively, we can implement the top-down approach with memorization (to avoid duplicate computation).

```c++
int minDays(int n) {
    // Memorize the result to avoid duplicate computation.
    std::unordered_map<int, int> memo = { { 0, 1 }, { 1, 1 } };
    std::function<int(int)> minDaysMemRecurse =
        [&](int n) -> int {
          if (memo.count(n)) return memo[n];
          memo[n] = minDaysMemRecurse(n - 1);
          if (n % 2 == 0) memo[n] = std::min(memo[n], minDaysMemRecurse(n / 2));
          if (n % 3 == 0) memo[n] = std::min(memo[n], minDaysMemRecurse(n / 3));
          return memo[n];
        };
    return minDaysMemRecurse(n);
  }
```

Unfortunately the runtime still exceeds the limitation. To further optimize the algorithm, try thinking about the optimal iterations in the example and imagine... In each time we are allowed to eat oranges, we humans are really greedy: why not each the most oranges as long as we are allowed? For instance, we have 36 oranges, greedily it would be much much better to eat 24 apples at one time!

We come up with a new idea that **we eat `n/2` or `2*(n/3)` oranges immediately once allowed**. This strategy is greedy in fact, however it remains optimality. To comprehend this, try imaging a simplified occasion - we have two options in each iteration:

- Eat one orange. The sub-problem begins with `n-1`.
- Eat `n/2` oranges. The sub-problem begins with `n/2`.

Now we prove the following theorem.

> The optimal strategy is to eat `n/2` oranges once `n` is even.

**Proof**: Suppose that we skip a even number `n` at one iteration, *i. e.* we follow the path `PATH1: n -> n-1 -> n-2 -> ... -> n-2k -> n/2-k`. Obviously, we can find another path `PATH2: n -> n/2 -> n/2-1 -> ... -> n/2-k`. The length of `PATH1` is `2k+1` while that of `PATH2` is `k+1`. Such a result tells us that `PATH1` is not optimal.

Similarly we can extend this theorem.

> The optimal strategy when we have `n` oranges is one of the following:
>
> - Let `m` be the largest even number such that `m<=n`. We eat one orange at each iteration until we have`m` oranges left, then we eat `m/2` oranges at the next iteration.
> - Let `m` be the largest number such that `m<=n` and `3|m`. We eat one orange at each iteration until we have`m` oranges left, then we eat `2*(m/3)` oranges at the next iteration.

From the above theorem, we can avoid a lot of redundant computation. The complexity can be reduced to *logarithmic* level. We don't need to modify our code too much.

```c++
int minDays(int n) {
    // Memorize the result to avoid duplicate computation.
    std::unordered_map<int, int> memo = { { 0, 1 }, { 1, 1 } };
    std::function<int(int)> minDaysMemRecurse =
        [&](int n) -> int {
          if (memo.count(n)) return memo[n];
          memo[n] = std::min(n % 2 + minDaysMemRecurse(n / 2),
                             n % 3 + minDaysMemRecurse(n / 3)) + 1;
          return memo[n];
        };
    return minDaysMemRecurse(n);
  }
```

