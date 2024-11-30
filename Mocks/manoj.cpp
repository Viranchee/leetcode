/*
Given an array of intervals where intervals[i] = [starti, endi], merge all
overlapping intervals, and return an array of the non-overlapping intervals that
cover all the intervals in the input.

Example 1:

Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].

Example 2:

Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.



Constraints:

    1 <= intervals.length <= 10^4
    intervals[i].length == 2
    0 <= starti <= endi <= 10^4


Scale: 1, 2, 3, 4 < Lowest to Highest >
Understadning: 4, Good. Asked questions.
Working solution proposed: 3 Good
Opitmized solution proposed: 4 Proposed the solution
Implementation: 3, was good at coding jumped before explaining
Time complexity: 4, commented out
Test Cases/Edge cases: 4,
Dry Run: 4
Behavioral Score: 3

*/
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
  vector<vector<int>> merge(vector<vector<int>> &intervals) {
    // v[v[2]]
    // sort that            Time O(n log n)
    sort(intervals.begin(), intervals.end(),
         [](vector<int> first, vector<int> second) {
           return first[0] < second[0];
         });
    // merge that           Time O(n)

    auto l = intervals.begin(), r = intervals.begin() + 1;
    unordered_set<vector<int>::iterator> removeList;
    // Input: intervals = [[1,3],[2,6],[3,5],[8,10],[15,18]]
    // MODIFIED. ervals = [[1,6],[2,6],[3,5],[8,10],[15,18]]
    il.r.L.R

        while (r != intervals.end()) { // O(n)
      while (*l[1] >= *r[0] && r != intervals.end()) {
        // can be merged
        *l[1] = *r[1]
                 // remove (list element) // O(n)
                 removeList.insert(r);
        r++;
      }
      l++;
    }
    // Input: intervals = [[1,6],[2,6],[8,10],[15,18]]
    // removeList: [2,6]
    // remove_all(removeList)  // N log N

    partition(intervals.begin(), intervals.end(),
              [&removeList](vector<int>::iterator current) {
                return removeList.find(current) == removeList.end();
              });
    // Input: intervals = [[1,6],[8,10],[15,18], [2,6]]
    // remove N (removeList) from the end of the array // O(1)
    for (int i = 0; i < removeList.size(); i++) { // O(N)
      intervals.pop_back();
    }

    return intervals;
  }
};

int main() { return 0; }

/*

Scale: 1, 2, 3, 4 < Lowest to Highest >
Understadning:
Working solution proposed:
Opitmized solution proposed:
Implementation:
Time complexity:
Test Cases/Edge cases:
Dry Run:
Behavioral Score:


https://leetcode.com/problems/merge-intervals

https://leetcode.com/problems/maximum-subarray
*/

// linkedin.com/in/viranchee
