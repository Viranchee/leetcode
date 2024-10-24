#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int singleNumber(vector<int> &nums) {
    int odd = 0;
    for (auto num : nums) {
      odd ^= num;
    }
    return odd;
  }
  int hammingWeight(int n) {
    int count = 0;
    while (n > 0) {
      n = n & (n - 1);
      count++;
    }
    // return __builtin_popcount(n);
    // for (int copy = 1; copy != 0; copy = copy >> 1) {
    //     int b = copy & 0x01;
    //     count += b;
    // }
    return count;
  }
  vector<int> countBits(int n) {
    vector<int> result(n + 1);
    result[0] = 0;
    for (auto i = 0; i <= n; i++)
      result[i] = result[i >> 1] + (i & 1);
    return result;
  }
  uint32_t reverseBits(uint32_t n) {
    vector<uint32_t> masks{0xffff0000, 0xff00ff00, 0xf0f0f0f0, 0xcccccccc,
                           0xaaaaaaaa};
    int8_t shift = 16;
    for (int i = 0; i < masks.size(); i++, shift >>= 1) {
      n = ((n & masks[i]) >> shift) | ((n & ~masks[i]) << shift);
      cout << i << " " << (int)shift << endl;
    }
    return n;
  }
  int missingNumber(vector<int> &nums) {
    int res = 0;
    for (int i = 0; i < nums.size(); i++)
      res ^= i ^ nums[i];
    return res ^ nums.size();
  }
  int getSum(int a, int b) {
    int carry;
    while (b != 0) {
      carry = a & b;
      a = a ^ b;
      b = carry << 1;
    }
    return a;
  }
  int reverse(int x) {
    int ans = 0;
    while (x) {
      if (ans > INT_MAX / 10 || ans < INT_MIN / 10)
        return 0;
      ans = ans * 10 + x % 10;
      x /= 10;
    }
    return ans;
  }
};