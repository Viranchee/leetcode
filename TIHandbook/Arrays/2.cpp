#include <algorithm>
#import <iostream>
#import <vector>

using namespace std;

vector<int> absSort(const vector<int> &arr) {
  //
  auto copy = arr;
  sort(copy.begin(), copy.end(), [](int a, int b) {
    auto absA = abs(a);
    auto absB = abs(b);
    if (absA == absB) {
      return a < b;
    } else {
      return absA < absB;
    }
  });
  return copy;
}
