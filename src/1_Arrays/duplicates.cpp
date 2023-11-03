#include <cassert>
#include <unordered_set>
#include <vector>

/**
 * This program finds and counts the duplicate elements in a given integer
 * vector.
 */

int countDuplicates(const std::vector<int> &arr) {
  int duplicatesCount = 0;
  std::unordered_set<int> seenElements;

  for (const auto &num : arr) {
    if (seenElements.count(num)) {
      duplicatesCount++;
    } else {
      seenElements.insert(num);
    }
  }

  return duplicatesCount;
}

std::vector<int> findDuplicates(const std::vector<int> &arr) {
  std::vector<int> duplicates;
  std::unordered_set<int> seenElements;

  for (const auto &num : arr) {
    if (seenElements.count(num) &&
        std::find(duplicates.begin(), duplicates.end(), num) ==
            duplicates.end()) {
      duplicates.push_back(num);
    } else {
      seenElements.insert(num);
    }
  }

  return duplicates;
}

void testDuplicateFunctions() {
  std::vector<int> arr1{1, 2, 3, 4, 5};
  assert(countDuplicates(arr1) == 0);
  assert(findDuplicates(arr1).empty());

  std::vector<int> arr2{5, 10, 15, 5, 3, 3};
  assert(countDuplicates(arr2) == 2);
  assert(findDuplicates(arr2) == std::vector<int>{5, 3});

  std::vector<int> arr3{3, 9, 9, 7, 3};
  assert(countDuplicates(arr3) == 2);
  assert(findDuplicates(arr3) == std::vector<int>{9, 3});
}

int main() {
  testDuplicateFunctions();
  return 0;
}
