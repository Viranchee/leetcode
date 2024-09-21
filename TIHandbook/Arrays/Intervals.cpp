#include <algorithm>
#include <cstdio>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> insert(vector<vector<int>> &intervals,
                             vector<int> &newInterval) {
    vector<vector<int>> result;
    int i = 0;
    while (i < intervals.size() && intervals[i][1] < newInterval[0])
      result.push_back(intervals[i++]);
    while (i < intervals.size() && intervals[i][0] <= newInterval[1]) {
      if (intervals[i][0] < newInterval[0])
        newInterval[0] = intervals[i][0];
      if (intervals[i][1] > newInterval[1])
        newInterval[1] = intervals[i][1];
      i++;
    }
    result.push_back(newInterval);
    while (i < intervals.size())
      result.push_back(intervals[i++]);
    return result;
  }
};