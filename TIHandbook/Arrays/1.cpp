#include "array_internal.h"
#include <algorithm>
#include <climits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Arrays {
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
};