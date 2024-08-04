#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

namespace ALGORITHM {
vector<int> arr(10, 10);

void non_modifying_functions(vector<int> arr) {
  auto moreThan5 = [](int i) { return i > 5; };

  auto _ = all_of(arr.begin(), arr.end(), moreThan5);
  _ = any_of(arr.begin(), arr.end(), moreThan5);
  _ = none_of(arr.begin(), arr.end(), moreThan5);
  _ = all_of(arr.begin(), arr.end(), [](int val) { return val > INT_MIN; });
  _ = any_of(arr.begin(), arr.end(), [](int v) { return v == 0; });
  _ = none_of(arr.begin(), arr.end(), [](int v) { return v == INT_MAX; });

  const auto duplicate = arr;
  for_each(duplicate.begin(), duplicate.end(), [](int v) { return pow(v, v); });
  for (auto v : duplicate) {
    cout << v << "\t" << endl;
  }

  return;
}

} // namespace ALGORITHM

class Solution {
public:
  string longestCommonPrefix(vector<string> &words) {
    std::string commonPrefix = words[0];
    for (auto w : words) {
      commonPrefix = std::mismatch(w.begin(), w.end(), commonPrefix.begin());
    }

    return commonPrefix;
  }
};