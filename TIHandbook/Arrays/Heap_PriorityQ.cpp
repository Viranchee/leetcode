#include <algorithm>
#include <cstdio>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <vector>

using namespace std;

class KthLargest {
private:
  int k;
  priority_queue<int, vector<int>, greater<int>> pq;

public:
  KthLargest(int k, vector<int> &nums) {
    this->k = k;
    for (int n : nums) {
      add(n);
    }
  }

  int add(int val) {
    if (pq.size() < k) {
      pq.push(val);
    } else if (pq.top() < val) {
      pq.pop();
      pq.push(val);
    }
    return pq.top();
  }
};

class Solution {
public:
  int lastStoneWeight(vector<int> &stones) {
    priority_queue<int> pq(stones.begin(), stones.end());
    while (pq.size() > 1) {
      int y = pq.top();
      pq.pop();
      int x = pq.top();
      pq.pop();
      if (x != y) {
        pq.push(y - x);
      }
    }
    return pq.empty() ? 0 : pq.top();
  }

  vector<vector<int>> kClosest(vector<vector<int>> &points, int k) {
    // Point = pair<int, int>
    typedef pair<int, int> Point;
    Point origin = {0, 0};
    priority_queue<Point> pq;
    for (int i = 0; i < points.size(); i++) {
      int x = points[i][0];
      int y = points[i][1];
      int dist = x * x + y * y;
      pq.push({dist, i});
      if (pq.size() > k) {
        pq.pop();
      }
    }
    vector<vector<int>> res;
    while (!pq.empty()) {
      res.push_back(points[pq.top().second]);
      pq.pop();
    }
    return res;
  }

  int findKthLargest(vector<int> &nums, int k) {
    priority_queue<int> pq(nums.begin(), nums.end());
    for (int i = 0; i < k - 1; i++) {
      pq.pop();
    }
    return pq.top();
  }

  int leastInterval(vector<char> &tasks, int n) {
    vector<int> freq(26, 0);
    for (char task : tasks) {
      freq[task - 'A']++;
    }
    sort(freq.begin(), freq.end());
    int chunk = freq.back() - 1;
    freq.pop_back();
    int idle = chunk * n;
    for (int f : freq) {
      idle -= min(chunk, f);
    }
    return tasks.size() + max(0, idle);
  }
};

class Twitter {

public:
  Twitter() {}

  void postTweet(int userId, int tweetId) {}

  vector<int> getNewsFeed(int userId) {}

  void follow(int followerId, int followeeId) {}

  void unfollow(int followerId, int followeeId) {}
};

// Pure virtual

struct X {
  virtual void foo() = 0;
};