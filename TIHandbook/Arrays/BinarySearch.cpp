#include <algorithm>
#include <math.h>
#include <numeric>
#include <string_view>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
  int search(vector<int> &nums, int target) {
    auto l = nums.begin(), r = nums.end();
    while (l < r) {
      auto m = distance(l, r) / 2 + l;
      if (*m == target) {
        return m - nums.begin();
      } else if (*m < target) {
        l = m + 1;
      } else {
        r = m;
      }
    }
    return -1;
  }

  bool searchMatrix(vector<vector<int>> &matrix, int target) {
    // matrix 2D variation is 1...100
    int m = matrix.size(), n = matrix[0].size();
    int l = 0, r = m - 1;
    while (l < n && r >= 0) {
      if (matrix[l][r] == target)
        return true;
      else if (matrix[l][r] < target)
        r--;
      else
        l++;
    }
    return false;
  }
  int minEatingSpeed(vector<int> &piles, int h) {
    int l = 1, r = *max_element(piles.begin(), piles.end());
    while (l < r) {
      int m = l + (r - l) / 2;
      int hours = accumulate(piles.begin(), piles.end(), 0,
                             [m](int a, int b) { return a + (b + m - 1) / m; });

      if (hours > h) {
        l = m + 1;
      } else {
        r = m;
      }
    }
    return l;
  };

  int findMinRotatedVector(vector<int> &nums) {
    // 456789123
    // ^       ^

    auto l = nums.begin(), r = nums.end();
    while (l < r) {
      auto m = distance(l, r) / 2 + l;
      if (*m < *r) {
        r = m;
      } else {
        l = m + 1;
      }
    }
    return *l;
  }
};

class TimeMap {
  struct TimeValues {
    string value;
    int timestamp;
  };
  unordered_map<string, vector<TimeValues>> m;

public:
  TimeMap() {}

  void set(string key, string value, int timestamp) {
    m[key].push_back({value, timestamp});
  }

  string get(string key, int timestamp) {
    if (!m.count(key))
      return "";
    auto &v = m[key];
    auto it = upper_bound(
        v.begin(), v.end(), timestamp,
        [](int t, const TimeValues &tv) { return t < tv.timestamp; });
    return it == v.begin() ? "" : prev(it)->value;
  }
};
