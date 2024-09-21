#include <algorithm>
#include <cassert>
#include <climits>
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

  bool canJump(vector<int> &nums) {}
};