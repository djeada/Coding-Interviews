#include <algorithm>
#include <cassert>
#include <vector>

/**
 * This program aims to find the minimum element in a cyclically sorted array,
 * assuming that the rotation is made around an ascending sorted array.
 */

int findMinInSubarray(const std::vector<int> &arr, int startIdx, int endIdx) {
  int minElement = arr[startIdx];
  for (int i = startIdx + 1; i <= endIdx; ++i) {
    minElement = std::min(minElement, arr[i]);
  }
  return minElement;
}

int findMinInRotatedArray(const std::vector<int> &arr) {
  int startIdx = 0;
  int endIdx = arr.size() - 1;
  int midIdx = startIdx;

  while (arr[startIdx] >= arr[endIdx]) {
    if (endIdx - startIdx == 1) {
      midIdx = endIdx;
      break;
    }

    midIdx = (startIdx + endIdx) / 2;

    if (arr[startIdx] == arr[endIdx] && arr[midIdx] == arr[startIdx])
      return findMinInSubarray(arr, startIdx, endIdx);

    if (arr[midIdx] >= arr[startIdx])
      startIdx = midIdx;
    else if (arr[midIdx] <= arr[endIdx])
      endIdx = midIdx;
  }

  return arr[midIdx];
}

void testFindMinInRotatedArray() {
  std::vector<int> arr1{3, 4, 5, 1, 2};
  assert(findMinInRotatedArray(arr1) == 1);

  std::vector<int> arr2{10, 10, 2, 5, 5, 9, 9, 9};
  assert(findMinInRotatedArray(arr2) == 2);

  std::vector<int> arr3{-1, -1, 5, -1, -1};
  assert(findMinInRotatedArray(arr3) == -1);

  std::vector<int> arr4{0, 0, 0, 0, 0, 0};
  assert(findMinInRotatedArray(arr4) == 0);
}

int main() {
  testFindMinInRotatedArray();
  return 0;
}
