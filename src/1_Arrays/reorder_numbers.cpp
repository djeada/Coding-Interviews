#include <algorithm>
#include <cassert>
#include <vector>

/**
 * This program reorders an integer vector such that all odd numbers come before
 * all even numbers. The relative order of odd numbers and even numbers is not
 * guaranteed to be preserved.
 */

bool isEven(int num) { return (num & 0x1) == 0; }

std::vector<int> reorderOddEven(std::vector<int> arr) {
  auto it = std::partition(arr.begin(), arr.end(),
                           [](int num) { return !isEven(num); });
  return arr;
}

void testReorderOddEven() {
  // Test Case 1
  {
    std::vector<int> arr{1, 2, 3, 4, 5, 6, 7};
    std::vector<int> result = reorderOddEven(arr);
    assert(std::all_of(result.begin(), result.end() - 3,
                       [](int num) { return !isEven(num); }));
    assert(std::all_of(result.end() - 3, result.end(), isEven));
  }

  // Test Case 2
  {
    std::vector<int> arr{1, 3, 5, 7, 2, 4, 6};
    std::vector<int> result = reorderOddEven(arr);
    assert(std::all_of(result.begin(), result.end() - 3,
                       [](int num) { return !isEven(num); }));
    assert(std::all_of(result.end() - 3, result.end(), isEven));
  }
}

int main() {
  testReorderOddEven();
  return 0;
}
