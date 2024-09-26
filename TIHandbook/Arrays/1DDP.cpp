#include <algorithm>
#include <cassert>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <regex>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// Memoization

class Solution {

public:
  int climbStairs(int n) {
    function<int(int)> recursion = [&](int n) {
      if (n == 0 || n == 1)
        return 1;
      return recursion(n - 1) + recursion(n - 2);
    };

    function<int(int)> memoization = [&](int n) {
      unordered_map<int, int> memo;
      function<int(int)> climb = [&](int n) {
        if (n == 0 || n == 1)
          return 1;
        if (memo.find(n) == memo.end())
          memo[n] = climb(n - 1) + climb(n - 2);
        return memo[n];
      };
      return climb(n);
    };

    // Bottom up approach
    function<int(int)> tabulation = [&](int n) {
      if (n == 0 || n == 1)
        return 1;
      vector<int> dp(n + 1);
      dp[0] = dp[1] = 1;
      for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
      }
      return dp.back();
    };

    function<int(int)> spaceOptimizedTabulation = [&](int n) {
      if (n == 0 || n == 1)
        return 1;
      int prev = 1, curr = 1;
      for (int i = 2; i <= n; i++) {
        swap(prev, curr);
        curr += prev;
      }
      return curr;
    };

    // return recursion(n);
    // return memoization(n);
    // return tabulation(n);
    return spaceOptimizedTabulation(n);
  }

  int minCostClimbingStairs(vector<int> &cost) {
    function<int(int)> recursive = [&](int i) {
      if (i < 0)
        return 0;
      if (i == 0 || i == 1)
        return cost[i];
      return cost[i] + min(recursive(i - 1), recursive(i - 2));
    };
    // return min(recursive(cost.size() - 1), recursive(cost.size() - 2));

    unordered_map<int, int> memo;
    function<int(int)> memoized = [&](int i) {
      if (i < 0)
        return 0;
      if (i == 0 || i == 1)
        return cost[i];
      if (memo.find(i) == memo.end())
        memo[i] = cost[i] + min(memoized(i - 1), memoized(i - 2));
      return memo[i];
    };
    // return min(memoized(cost.size() - 1), memoized(cost.size() - 2));

    function<int(void)> bottomUp = [&]() {
      vector<int> dp(cost.size());
      dp[0] = cost[0];
      dp[1] = cost[1];
      for (int i = 2; i < cost.size(); i++) {
        dp[i] = cost[i] + min(dp[i - 1], dp[i - 2]);
      }
      return min(dp.back(), dp[dp.size() - 2]);
    };
    // return bottomUp();

    function<int(void)> spaceOptimized = [&]() {
      int prev = cost[0], curr = cost[1];
      for (int i = 2; i < cost.size(); i++) {
        int temp = curr;
        curr = cost[i] + min(curr, prev);
        prev = temp;
      }
      return min(curr, prev);
    };
    return spaceOptimized();
  }

  int rob(vector<int>::iterator begin, vector<int>::iterator end) {
    int p1 = 0, p2 = 0;
    for (auto it = begin; it != end; it++) {
      int temp = p1;
      p1 = max(p1, p2 + *it);
      p2 = temp;
    }
    return p1;
  }

  int rob(vector<int> &nums) { return rob(nums.begin(), nums.end()); }

  int rob2(vector<int> &nums) {
    if (nums.size() == 1)
      return *nums.begin();
    return max(rob(nums.begin(), nums.end() - 1),
               rob(nums.begin() + 1, nums.end()));
  }

  string longestPalindrome(string s) {
    if (s.length() <= 1) {
      return s;
    }

    int maxLen = 1;
    string maxStr = s.substr(0, 1);
    s = "#" + regex_replace(s, regex(""), "#") + "#";
    vector<int> dp(s.length(), 0);
    int center = 0;
    int right = 0;

    for (int i = 0; i < s.length(); ++i) {
      if (i < right) {
        dp[i] = min(right - i, dp[2 * center - i]);
      }

      while (i - dp[i] - 1 >= 0 && i + dp[i] + 1 < s.length() &&
             s[i - dp[i] - 1] == s[i + dp[i] + 1]) {
        dp[i]++;
      }

      if (i + dp[i] > right) {
        center = i;
        right = i + dp[i];
      }

      if (dp[i] > maxLen) {
        maxLen = dp[i];
        maxStr = s.substr(i - dp[i], 2 * dp[i] + 1);
        maxStr.erase(remove(maxStr.begin(), maxStr.end(), '#'), maxStr.end());
      }
    }

    return maxStr;
  }

  int countSubstrings(string s) {
    int count = 0;
    vector<vector<bool>> dp(s.length(), vector<bool>(s.length(), false));
    for (int i = 0; i < s.length(); i++)
      dp[i][i] = true;
    count = s.length();
    for (int i = 0; i < s.length() - 1; i++) {
      dp[i][i + 1] = s[i] == s[i + 1];
      count += dp[i][i + 1];
    }
    for (int len = 3; len <= s.length(); len++) {
      for (int i = 0, j = len - 1; j < s.length(); i++, j++) {
        dp[i][j] = dp[i + 1][j - 1] && s[i] == s[j];
        count += dp[i][j];
      }
    }
    return count;
  }

  int numDecodings(string s) {
    function<int(string)> dp = [](string s) {
      if (s[0] == '0')
        return 0;
      vector<int> dp(s.length() + 2, 0);
      dp[0] = 1;
      for (int i = 0; i < s.length(); i++) {
        if (s[i] != '0') {
          dp[i + 1] += dp[i];
          if (i < s.length() - 1 &&
              ((s[i] - '0') * 10 + s[i + 1] - '0') <= 26) {
            dp[i + 2] += dp[i];
          }
        }
      }
      return dp[s.length()];
    };

    function<int(string &)> spaceOptimized = [](string &s) {
      if (s[0] == '0')
        return 0;
      int prev = 1, curr = 1;
      for (int i = 1; i < s.length(); i++) {
        int temp = curr;
        if (s[i] == '0')
          curr = 0;
        if (s[i - 1] == '1' || (s[i - 1] == '2' && s[i] <= '6'))
          curr += prev;
        prev = temp;
      }
      return curr;
    };

    // return dp(s);
    return spaceOptimized(s);
  }

  int coinChange(vector<int> &coins, int amount) {
    function<int(const vector<int> &, int)> dp = [](auto &coins, int amount) {
      vector<int> dp(amount + 1, amount + 1);
      dp[0] = 0;
      for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < coins.size(); j++) {
          if (coins[j] <= j) {
            dp[i] = min(dp[i], dp[i - coins[j]] + 1);
          }
        }
      }
      return dp[amount] > amount ? -1 : dp[amount];
    };
    return dp(coins, amount);
  }

  int maxProduct(vector<int> &nums) {
    int result = INT_MIN, maxProduct = 1, minProduct = 1;
    for (int num : nums) {
      if (num < 0)
        swap(maxProduct, minProduct);
      maxProduct = max(maxProduct * num, num);
      minProduct = min(minProduct * num, num);
      result = max(result, maxProduct);
    }
    return result;
  }

  bool wordBreak(string s, vector<string> &wordDict) {
    auto sv = string_view(s);
    vector<bool> dp(sv.length() + 1, false);
    dp[sv.length()] = true;
    for (int i = sv.length() - 1; i >= 0; i--) {
      for (auto w = wordDict.begin(); w != wordDict.end(); w++) {
        if (i + w->length() <= sv.length() && sv.substr(i, w->length()) == *w) {
          dp[i] = dp[i] || dp[i + w->length()];
        }
      }
    }
    return dp[0];
  }

  int lengthOfLIS(vector<int> &nums) {
    function<int(vector<int> &)> dp = [](auto nums) {
      vector<int> lis(nums.size(), 1);
      for (int i = nums.size() - 1; i >= 0; i--) {
        for (int j = i + 1; j < nums.size(); j++) {
          if (nums[i] < nums[j])
            lis[i] = max(lis[i], 1 + lis[j]);
        }
      }
      return *max_element(lis.begin(), lis.end());
    };
    return dp(nums);
  }
};