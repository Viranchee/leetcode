#include <queue>
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
