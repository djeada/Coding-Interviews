#include <algorithm>
#include <cassert>
#include <vector>

/**
 * This program merges two sorted arrays, arr1 and arr2, into a single sorted
 * array. The merged array replaces the contents of arr1.
 */

void mergeSortedArrays(std::vector<int> &arr1, const std::vector<int> &arr2) {
  int idx1 = arr1.size() - 1;
  int idx2 = arr2.size() - 1;
  int idxMerged = arr1.size() + arr2.size() - 1;

  arr1.resize(idxMerged + 1);

  while (idx1 >= 0 && idx2 >= 0) {
    arr1[idxMerged--] =
        (arr1[idx1] >= arr2[idx2]) ? arr1[idx1--] : arr2[idx2--];
  }

  // Copy the remaining elements from arr2
  std::copy(arr2.begin(), arr2.begin() + idx2 + 1,
            arr1.begin() + idxMerged - idx2);
}

void testMergeSortedArrays() {
  std::vector<std::tuple<std::vector<int>, std::vector<int>, std::vector<int>>>
      testCases = {
          {{1, 3, 5, 7, 9}, {2, 4, 6, 8, 10}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}},
          {{2, 4, 6, 8, 10}, {1, 3, 5, 7, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}},
          {{2, 4, 6, 8, 10},
           {2, 4, 6, 8, 10},
           {2, 2, 4, 4, 6, 6, 8, 8, 10, 10}},
          {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}};

  for (const auto &[arr1, arr2, expected] : testCases) {
    std::vector<int> mergedArr = arr1;
    mergeSortedArrays(mergedArr, arr2);
    assert(mergedArr == expected);
  }
}

int main() {
  testMergeSortedArrays();
  return 0;
}
