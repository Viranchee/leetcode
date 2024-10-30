#include <algorithm>
#include <bit>
#include <cassert>
#include <climits>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  // https://www.techinterviewhandbook.org/algorithms/array/
public:
  vector<int> twoSum(vector<int> &nums, int target) {
    // https://leetcode.com/problems/two-sum/
    unordered_map<int, int> walked;
    vector<int> out(2);
    for (int i = 0; i < nums.size(); i++) {
      int pair = target - nums[i];
      auto search = walked.find(pair);
      if (search == walked.end()) {
        walked[nums[i]] = i;
      } else {
        out[0] = i;
        out[1] = nums[pair];
        break;
      }
    }
    return out;
  }

  int maxProfit(vector<int> &prices) {
    // https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
    int maxProfit = 0;
    int runningLowest = INT_MAX;
    for (auto p : prices) {
      if (runningLowest > p) {
        runningLowest = p;
      }
      int profit = p - runningLowest;
      if (maxProfit < profit) {
        maxProfit = profit;
      }
    }
    return maxProfit;
  }
  vector<int> productExceptSelf(vector<int> &nums) {
    // https://leetcode.com/problems/product-of-array-except-self/description/
    // Pass from Left then Pass from Right
    // Use division: Tradeoff: Hardware is slow
    vector<int> out(nums.size(), 1);

    // // Left pass
    // {
    //   int running = 1;
    //   for (int i = 0; i < nums.size(); i++) {
    //     out[i] *= running;
    //     running *= nums[i];
    //   }
    // }

    // // Right pass
    // {
    //   int running = 1;
    //   for (int i = nums.size() - 1; i >= 0; i--) {
    //     out[i] *= running;
    //     running *= nums[i];
    //   }
    // }
    // Combined pass
    int prefix = 1, suffix = 1;
    int N = nums.size();
    for (int i = 0; i < N; i++) {
      int rI = N - i - 1;
      out[i] *= prefix;
      out[rI] *= suffix;
      prefix *= nums[i];
      suffix *= nums[rI];
    }
    return out;
  }

  int trap(vector<int> &height) {
    int sum = 0;
    auto l = height.begin(), r = height.end() - 1;
    int lMax = 0, rMax = 0;
    while (l < r) {
      lMax = max(lMax, *l);
      rMax = max(rMax, *r);

      if (lMax < rMax) {
        sum += lMax - *l;
        l++;
      } else {
        sum += rMax - *r;
        r--;
      }
    }
    return sum;
  }

  int maxSubArray(vector<int> &nums) {
    // https://leetcode.com/problems/maximum-subarray/
    // Kadane's algorithm
    int max_val = INT_MIN;
    int running_total = 0;
    for (auto n : nums) {
      running_total = max(n, running_total + n);
      max_val = max(max_val, running_total);
    }

    return max_val;
  }

  bool containsDuplicate(vector<int> &nums) {
    // https://leetcode.com/problems/contains-duplicate/
    unordered_set<int> walked;
    for (auto n : nums) {
      if (walked.find(n) == walked.end()) {
        walked.insert(n);
      } else {
        return true;
      }
    }
    return false;
  }
  int maxProduct(vector<int> &nums) {
    // https://leetcode.com/problems/maximum-product-subarray/description/

    // Subarray with largest product
    int maxP = INT_MIN;
    int pr = 1, su = 1;
    int N = nums.size();
    for (int i = 0; i < N; i++) {
      pr *= nums[i];
      su *= nums[N - 1 - i];
      maxP = max({maxP, pr, su});
      pr = pr != 0 ? pr : 1;
      su = su != 0 ? su : 1;
    }

    return maxP;
  }

  int searchRotatedSortedArray(vector<int> &nums, int target) {
    // https://leetcode.com/problems/search-in-rotated-sorted-array/
    int l = 0, r = nums.size() - 1;
    while (l <= r) {
      int m = (l + r) / 2;

      if (target == nums[m]) {
        return m;
      }
      if (nums[l] <= nums[m]) {
        if (nums[l] <= target && target < nums[m]) {
          r = m - 1;
        } else {
          l = m + 1;
        }
      } else {
        if (nums[m] < target && target <= nums[r]) {
          l = m + 1;
        } else {
          r = m - 1;
        }
      }
    }

    return -1;
  }

  vector<vector<int>> threeSum(vector<int> &nums) {
    // https://leetcode.com/problems/3sum/
    sort(nums.begin(), nums.end());

    vector<vector<int>> o;
    for (auto it = nums.begin(); it != nums.end(); it++) {
      int target = 0 - *it;
      auto l = it + 1, r = nums.end() - 1;
      while (l < r) {
        int sum = *l + *r;
        if (sum < target) {
          l++;
        } else if (sum > target) {
          r--;
        } else if (sum == target) {
          o.push_back({*it, *l, *r});
          while (l < r && *l == *(l + 1))
            l++;
          while (l < r && *r == *(r - 1))
            r--;
          l++;
          r--;
        }
      }
      while (it + 1 != nums.end() && *it == *(it + 1))
        it++;
    }
    return o;
  }

  // int maxArea(vector<int> &height) {}

  vector<int> absSort(const vector<int> &arr) {
    // Found on Pramp, not on leetcode
    auto copy = arr;
    sort(copy.begin(), copy.end(), [](int a, int b) {
      auto absA = abs(a);
      auto absB = abs(b);
      if (absA == absB) {
        return a < b;
      } else {
        return absA < absB;
      }
    });
    return copy;
  }
};

// Serialize and Deserialize a Matrix

class MatrixStorage {
public:
  string filename;
  void store(vector<vector<float>> matrix) {
    int rows = matrix.size(), cols = matrix[0].size();
    auto F = fstream(filename, ios::out);
    F << rows << " " << cols << endl;
    for (auto row : matrix) {
      for (auto val : row) {
        F << val << " ";
      }
      F << endl;
    }
    F.close();
  }

  vector<vector<float>> retrive() {
    auto F = fstream(filename, ios::in);
    int rows, cols;
    F >> rows >> cols;
    vector<vector<float>> matrix(rows, vector<float>(cols));
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        F >> matrix[i][j];
      }
    }
    F.close();
    return matrix;
  }
};

int arrays() { return 0; }