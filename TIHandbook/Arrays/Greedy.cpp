#include <algorithm>
#include <cassert>
#include <climits>
#include <numeric>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  int maxSubArray(vector<int> &nums) {
    int result = INT_MIN, sum = 0;
    for (int num : nums) {
      sum = max(sum + num, num);
      result = max(result, sum);
    }
    return result;
  }

  bool canJump(vector<int> &nums) {
    int maxJ = 0;
    for (int i = 0; i < nums.size(); i++) {
      if (i > maxJ)
        return false;
      maxJ = max(maxJ, i + nums[i]);
      if (maxJ > nums.size() - 1)
        break;
    }
    return true;
  }

  int jump(vector<int> &nums) {
    int jumps = 0, near = 0, far = 0;
    while (far < nums.size() - 1) {
      int nextFar = far;
      for (int i = near; i <= far; i++) {
        nextFar = max(nextFar, i + nums[i]);
      }
      jumps++;
      near = far + 1;
      far = nextFar;
    }
    return jumps;
  }

  int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    int tank = 0, start = 0;
    int gasCostT = 0;
    for (int i = 0; i < gas.size(); i++) {
      int req = gas[i] - cost[i];
      gasCostT += req;
      tank += req;
      if (tank < 0) {
        tank = 0;
        start = i + 1;
      }
    }
    if (gasCostT < 0)
      start = -1;
    return start;
  }
};