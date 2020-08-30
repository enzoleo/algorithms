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
int minDaysMemorize(int n) {
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