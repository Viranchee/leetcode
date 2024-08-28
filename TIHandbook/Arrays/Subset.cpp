#include <algorithm>
#include <functional>
#include <string_view>
#include <vector>
using namespace std;

class Solution {
public:
  vector<vector<int>> subsets(vector<int> &nums) {
    function<vector<vector<int>>(int, vector<int>)> dfs =
        [&](int i, vector<int> s) -> vector<vector<int>> {
      if (i == nums.size()) {
        return {s};
      }
      vector<vector<int>> res;
      res = dfs(i + 1, s);
      s.push_back(nums[i]);
      vector<vector<int>> res2 = dfs(i + 1, s);
      res.insert(res.end(), res2.begin(), res2.end());
      return res;
    };
    return dfs(0, {});
  }

  vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    vector<vector<int>> result;
    function<void(int, int, vector<int>)> backtrack = [&](int start, int T,
                                                          vector<int> path) {
      if (T == 0) {
        result.push_back(path);
        return;
      }
      if (T >= 0) {
        for (int i = start; i < candidates.size(); i++) {
          path.push_back(candidates[i]);
          backtrack(i, T - candidates[i], path);
          path.pop_back();
        }
      }
    };
    backtrack(0, target, {});
    return result;
  }

  vector<vector<int>> permute(vector<int> &nums) {
    vector<vector<int>> res;
    function<void(int, vector<int>)> dfs;
    dfs = [&](auto i, auto s) {
      if (i == nums.size()) {
        res.push_back(s);
      } else {
        for (int j = 0; j <= s.size(); j++) {
          vector<int> t = s;
          t.insert(t.begin() + j, nums[i]);
          dfs(i + 1, t);
        }
      }
    };
    dfs(0, {});
    return res;
  }

  vector<vector<int>> subsetsWithDup(vector<int> &nums) {
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());

    function<void(vector<int>::iterator, vector<int>)> dfs;
    dfs = [&](auto i, auto s) {
      res.push_back(s);
      for (auto j = i; j < nums.end(); j = upper_bound(j, nums.end(), *j)) {
        s.push_back(*j);
        dfs(j + 1, s);
        s.pop_back();
      }
    };
    dfs(nums.begin(), {});

    return res;
  }

  vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> res;
    vector<int> path = {};
    function<void(vector<int>::iterator, int)> dfs;
    dfs = [&](auto i, int T) {
      if (T == 0) {
        res.push_back(path);
      } else if (T >= 0) {
        for (auto j = i; j < candidates.end();
             j = upper_bound(j, candidates.end(), *j)) {
          path.push_back(*j);
          dfs(j + 1, T - *j);
          path.pop_back();
        }
      }
    };
    dfs(candidates.begin(), target);

    return res;
  }

  bool exist(vector<vector<char>> &board, string word) {
    bool res = false;
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    function<void(int, int, int)> dfs;
    dfs = [&](int i, int j, int k) {
      // Bounds check:
      if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() ||
          board[i][j] != word[k]) {
        return;
      }
      if (k == word.size() - 1) {
        res = true;
        return;
      }
      char c = board[i][j];
      board[i][j] = '*';
      for (auto d : directions) {
        dfs(i + d.first, j + d.second, k + 1);
        if (res) {
          break;
        }
      }
      board[i][j] = c;
    };

    for (int i = 0; i < board.size(); i++) {
      for (int j = 0; j < board[0].size(); j++) {
        dfs(i, j, 0);
        if (res) {
          break;
        }
      }
    }

    return res;
  }
  vector<vector<string>> partition(string s) {
    vector<vector<string>> res;
    vector<string> p;

    function<void(int)> dfs;
    dfs = [&](int i) {
      if (i == s.size())
        res.push_back(p);
      else {
        for (int j = i; j < s.size(); j++) {
          string t = s.substr(i, j - i + 1); // Use stringview
          if (t == string(t.rbegin(), t.rend())) {
            p.push_back(t);
            dfs(j + 1);
            p.pop_back();
          }
        }
      }
    };
    dfs(0);
    return res;
  }

  vector<string> letterCombinations(string digits) {
    vector<string> res;
    if (digits.empty())
      return res;
    vector<string> dict = {"abc", "def",  "ghi", "jkl",
                           "mno", "pqrs", "tuv", "wxyz"};
    string path;
    function<void(int)> dfs;
    dfs = [&](int i) {
      if (i == digits.size()) {
        res.push_back(path);
        return;
      }
      for (char c : dict[digits[i] - '2']) {
        path.push_back(c);
        dfs(i + 1);
        path.pop_back();
      }
    };
    dfs(0);
    return res;
  }
};