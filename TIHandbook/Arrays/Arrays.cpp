#include <algorithm>
#include <cassert>
#include <climits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Arrays {
  // https://www.techinterviewhandbook.org/algorithms/array/
public:
  Arrays() {}
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

    // Left pass
    {
      int running = 1;
      for (int i = 0; i < nums.size(); i++) {
        out[i] *= running;
        running *= nums[i];
      }
    }

    // Right pass
    {
      int running = 1;
      for (int i = nums.size() - 1; i >= 0; i--) {
        out[i] *= running;
        running *= nums[i];
      }
    }

    return out;
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
