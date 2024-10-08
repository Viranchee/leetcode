#include <algorithm>
#include <cassert>
#include <climits>
#include <functional>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
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

  bool isNStraightHand(vector<int> &hand, int groupSize) {
    // Check if dividing is possible
    if (hand.size() % groupSize != 0)
      return false;
    // write to a dictionary
    map<int, int> dict;
    for (int i : hand)
      dict[i]++;
    //
    int start = 0, curr = 0;
    while (!dict.empty()) {
      curr = dict.begin()->first;
      for (int i = 0; i < groupSize; i++) {
        if (dict[curr + i] == 0)
          return false;
        dict[curr + i]--;
        if (dict[curr + i] == 0)
          dict.erase(curr + i);
      }
    }
    return true;
  }
  bool mergeTriplets(vector<vector<int>> &triplets, vector<int> &t) {
    vector<int> a = {-1, -1, -1};
    for (int i = 0; i < triplets.size(); i++) {
      for (int k = 0; k < 3; k++) {
        if (triplets[i][k] == t[k] && triplets[i][k + 1] <= t[k + 1] &&
            triplets[i][k + 2] <= t[k + 2]) {
          a[k] = max(a[k], t[k]);
        }
      }
    }
    if (a == t)
      return true;

    return false;
  }
  vector<int> partitionLabels(string s) {
    vector<int> lastIndex(26, 0);
    function<int(int)> charID = [&s](int c) { return s[c] - 'a'; };
    vector<int> ans;
    for (int i = 0; i < s.length(); i++) {
      lastIndex[charID(i)] = i;
    }
    int start = 0, end = 0;
    for (int i = 0; i < s.length(); i++) {
      end = max(end, lastIndex[charID(i)]);
      if (i == end) {
        ans.push_back(end - start + 1);
        start = i + 1;
      }
    }
    return ans;
  }

  bool checkValidString(string s) {
    set<int> star_ind;
    for (int i = 0; i < int(s.size()); i++) {
      if (s[i] == '*')
        star_ind.insert(i);
    }
    stack<pair<char, int>> st;
    for (int i = 0; i < int(s.size()); i++) {
      if (s[i] == '*')
        continue;
      if (!st.empty()) {
        if (st.top().first == '(') {
          if (s[i] == ')')
            st.pop();
          else
            st.push({s[i], i});
        } else {
          st.push({s[i], i});
        }
      } else {
        st.push({s[i], i});
      }
    }

    while (!st.empty() && (int(star_ind.size())) > 0) {
      int idx = st.top().second;
      char ch = st.top().first;
      if (ch == '(') {
        auto lb = star_ind.lower_bound(idx);
        if (lb == star_ind.end())
          break;
        else {
          st.pop();
          star_ind.erase(lb);
        }
      } else {
        auto lb = star_ind.lower_bound(idx);
        if (lb == star_ind.begin()) {
          break;
        } else {
          st.pop();
          lb--;
          star_ind.erase(lb);
        }
      }
    }
    if (st.empty())
      return true;
    return false;
  }
};