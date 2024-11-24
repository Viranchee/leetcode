#include <algorithm>
#include <cassert>
#include <climits>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <regex>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  int uniquePaths(int m, int n) {
    if (m == 1 || n == 1)
      return 1;
    if (m < n)
      swap(m, n);
    long res = 1;
    for (int i = 1; i < n; i++) {
      res = res * m++ / i;
    }
    return res;
  }

  int maxProfit(vector<int> &prices) {
    auto dp_fast = [](vector<int> &prices) {
      int dp1_buy = 0, dp1_sell = 0;
      int dp2_buy = 0;

      for (auto it = prices.crbegin(); it != prices.crend(); it++) {
        dp1_sell = max(dp2_buy + *it, dp1_sell);
        dp2_buy = dp1_buy;
        dp1_buy = max(dp1_sell - *it, dp1_buy);
      }

      return dp1_buy;
    };

    function<int(vector<int> &)> dp_topdown = [](auto prices) {
      unordered_map<string, int> dp;
      function<int(int, bool)> dfs = [&dfs, &dp, &prices](int i, bool buying) {
        if (i >= prices.size())
          return 0;
        string key = to_string(i) + "-" + to_string(buying);
        if (dp.find(key) != dp.end())
          return dp[key];
        int cooldown = dfs(i + 1, buying);
        if (buying) {
          int buy = dfs(i + 1, false) - prices[i];
          dp[key] = max(buy, cooldown);
        } else {
          int sell = dfs(i + 2, true) + prices[i];
          dp[key] = max(sell, cooldown);
        }
        return dp[key];
      };
      return dfs(0, true);
    };

    function<int(vector<int> &)> dp_bottomup = [](auto prices) {
      vector<vector<int>> dp(prices.size() + 1, vector<int>(2, 0));
      for (int i = prices.size() - 1; i >= 0; --i) {
        int buy = dp[i + 1][0] - prices[i];
        int cooldown = dp[i + 1][1];
        dp[i][1] = max(buy, cooldown);
        int sell =
            (i + 2 < prices.size()) ? dp[i + 2][1] + prices[i] : prices[i];
        cooldown = dp[i + 1][0];
        dp[i][0] = max(sell, cooldown);
      }
      return dp[0][1];
    };
    return dp_fast(prices);
  }

  int change(int amount, vector<int> &coins) {
    vector<uint> memo(amount + 1, 0);
    memo[0] = 1;
    for (auto c = coins.crbegin(); c != coins.crend(); c++) {
      for (int target = 1; target <= amount; target++)
        if (target >= *c)
          memo[target] += memo[target - *c];
    }
    return memo[amount];
  }

  int findTargetSumWays(vector<int> &nums, int target) {
    unordered_map<int, int> memo;
    memo[0] = 1;

    for (const auto &num : nums) {
      unordered_map<int, int> nextMemo;
      for (const auto &[total, count] : memo) {
        nextMemo[total + num] += count;
        nextMemo[total - num] += count;
      }
      memo = nextMemo;
    }
    return memo[target];
  }
};