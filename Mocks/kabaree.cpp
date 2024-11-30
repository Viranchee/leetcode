/*
https://www.tryexponent.com/practice/08f46e3e-ab66-4d56-94fd-0f00f954d179

Scale: 1, 2, 3, 4 < Lowest to Highest >
Understadning:
Working solution proposed:
Opitmized solution proposed:
Implementation:
Time complexity:
Test Cases/Edge cases:
Dry Run:
Behavioral Score:
"""
'''
Given an integer array nums, rotate the array to the right by k steps, where k
is non-negative.



Example 1:

Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]
'''
 stable partition: predicate, Time C: N log N, S: 1

7 5 6.          A , size K
|
                move this pointer N times
1,2,3,4,5,6,7.  a
5,6,7_1_2_3_4
.
.
*/
#include <iostream>
#include <vector>

using namespace std;

vector<int> rotateArr(const vector<int> &arr, int k) {
  k = k % arr.size();
  vector<int> temp(k);
  for (int i = 0; i < k; i++)
    temp[i] = arr[i];
  //  temp:7 5 6
  //  arr: 7,5,6,1,2,3,4
  for (int i = 0; i < N; i++) {
    swap(arr[i], temp[i % k]);
  }
  return arr;
}

int main() { return 0; }
/*
class Solution:
    def rotate(self, nums: List[int], k: int) -> None:
        n = len(nums)
        a = [0] * n
        for i in range(n):
            a[(i + k) % n] = nums[i]

        nums[:] = a
*/

/*
Scale: 1, 2, 3, 4 < Lowest to Highest >
Understanding: 2.5, Havent seen this question before so its impressive to see
fundamentals and find somewhat optimal solution. Perhaps priotize doing brute
force for correct solution rahter than trying to find optimal Working solution
proposed: 2/4 See above Opitmized solution proposed: 3/4 I think this depends on
if you have seen the problem before . Actually you are right i think. this is
really good Implementation: Good, kinda hard to understand but thats cuz im
familiar with c++ Time complexity: Test Cases/Edge cases: 2/4, do a simpler
version and focus on breadth Dry Run: 3/4 Kinda rough, need practice Behavioral
Score: 2
*/
