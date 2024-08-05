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
};