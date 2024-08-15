#include <algorithm>
#include <deque>
#include <iterator>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  int maxProfit(vector<int> &prices) {
    auto min = prices.begin();
    auto maxProfit = 0;
    for (auto it = prices.begin(); it != prices.end(); it++) {
      if (*it < *min)
        min = it;
      int profit = *it - *min;
      if (profit > maxProfit)
        maxProfit = profit;
    }
    return maxProfit;
  }

  int lengthOfLongestSubstring(string s) {
    unordered_set<char> uniques;
    auto l = s.begin(), r = s.begin();
    int maxLen = 1;

    while (r != s.end()) {
      if (uniques.find(*r) == uniques.end()) {
        uniques.insert(*r);
        r++;
        int len = r - l;
        if (len > maxLen)
          maxLen = len;
      } else {
        uniques.erase(*l);
        l++;
      }
    }
    return maxLen;
  }

  int characterReplacement(string s, int k) {
    // vector<int> freq(26, 0);
    unordered_map<char, int> freq;
    int maxLen = 0;

    auto l = s.begin(), r = l;
    char mostFreqChar = *r;
    while (r != s.end()) {
      freq[*r]++;
      r++;
      if (freq[*r] > freq[mostFreqChar])
        mostFreqChar = *r;
      int len = distance(l, r);
      int replacements = len - freq[mostFreqChar];
      while (distance(l, r) + 1 - freq[mostFreqChar] > k) {
        freq[*l]--;
        l++;
      }
      if (len > maxLen)
        maxLen = len;
    }
    return maxLen;
  }

  bool checkInclusion(string s1, string s2) {
    if (s1.size() > s2.size())
      return false;
    auto pos = [](char c) { return c - 'a'; };
    vector<int> freq(26, 0);
    for_each(s1.begin(), s1.end(), [&](char c) { freq[pos(c)]--; });
    int diff =
        count_if(freq.begin(), freq.end(), [](const int &v) { return v < 0; });

    auto l = s2.begin(), r = s2.begin();
    while (r < s2.end()) {
      auto R = pos(*r++);
      freq[R]++;
      if (freq[R] == 0)
        diff--;
      while (freq[R] > 0) {
        auto L = pos(*l++);
        freq[L]--;
        if (freq[L] == -1)
          diff++;
      }
      if (diff == 0)
        return true;
    }

    return false;
  }

  string minWindow(string s, string t) {
    struct Window {
      string::iterator l, r;
    };
    if (t.size() > s.size())
      return "";

    unordered_map<char, int> req;
    for_each(t.begin(), t.end(), [&req](char c) { req[c]--; });
    Window w = {s.begin(), s.begin()};
    Window minW = w;

    int diff = req.size();

    while (w.r != s.end()) {
      auto R = *w.r++;
      if (req.find(R) != req.end() && ++req[R] == 0)
        diff--;
      while (diff == 0) {
        if (minW.l != minW.r && distance(w.l, w.r) < distance(minW.l, minW.r)) {
          minW = w;
        }
        auto L = *w.l++;
        if (req.find(L) != req.end() && --req[L] == -1)
          diff++;
      }
    }

    return string(minW.l, minW.r);
  }
  vector<int> maxSlidingWindow(vector<int> &nums, int k) {
    vector<int> res(nums.size() - k + 1);
    deque<int> q;
    for (int i = 0; i < nums.size(); i++) {
      while (!q.empty() && nums[i] >= nums[q.back()])
        q.pop_back();
      q.push_back(i);
      if (i >= k - 1) {
        res[i - k + 1] = nums[q.front()];
        if (q.front() == i - k + 1)
          q.pop_front();
      }
    }
    return res;
  }
};