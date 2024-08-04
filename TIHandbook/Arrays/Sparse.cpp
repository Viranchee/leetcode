// Sparse representation of Arrays
#include <algorithm>
#include <vector>

namespace SparseVector {
using namespace std;

template <typename T> struct Data {
  vector<int> index;
  vector<T> value;
};

// Specialize Data for float and double
template <> struct Data<float> {
  vector<int> index;
  vector<float> value;
};

template <> struct Data<double> {
  vector<int> index;
  vector<double> value;
};

template <typename T>
Data<T> sparse_add(const Data<T> &lhs, const Data<T> &rhs) {
  // Sparse Vector Addition
  Data<T> out;
  // The arrays are sorted
  // Use STL algorithms to add the two sparse arrays

  int i = 0, j = 0;
  while (i < lhs.index.size() && j < rhs.index.size()) {
    auto lV = lhs.index[i];
    auto rV = rhs.index[j];
    if (lV == rV) {
      out.index.push_back(lV);
      out.value.push_back(lhs.value[i] + rhs.value[j]);
      i++;
      j++;
    } else if (lV < rV) {
      out.index.push_back(lV);
      out.value.push_back(lhs.value[i]);
      i++;
    } else {
      out.index.push_back(rV);
      out.value.push_back(rhs.value[j]);
      j++;
    }
  }
}

} // namespace SparseVector