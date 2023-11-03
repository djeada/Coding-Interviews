#include <algorithm>
#include <cassert>
#include <vector>

/**
 * This program finds the smallest number in a given vector of integers.
 */

int findMinNumber(const std::vector<int> &arr) {
  return *std::min_element(arr.begin(), arr.end());
}

void testFindMinNumber() {
  std::vector<std::pair<std::vector<int>, int>> testCases = {
      {{3, 5, 1, 4, 2}, 1},
      {{-3, -5, -1, -4, -2}, -5},
      {{10, 20, 30, 40, 5}, 5},
      {{1, 1, 1, 1, 1}, 1}};

  for (const auto &[numbers, expected] : testCases) {
    assert(findMinNumber(numbers) == expected);
  }
}

int main() {
  testFindMinNumber();
  return 0;
}
