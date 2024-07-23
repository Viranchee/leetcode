#include "../internal.h"
#include "array_internal.h"
#include <cassert>
#include <vector>

int arrays() {
  auto vec = vector<int>{3, 4, 5, 6, 7};
  auto val = twoSum(vec, 7);
  auto expected = vector<int>{0, 1};
  assert(val == expected);
  //
  return -1;
}