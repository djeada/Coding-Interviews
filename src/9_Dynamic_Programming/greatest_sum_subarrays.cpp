/**
 * This program finds the contiguous subarray within a one-dimensional array of
 * numbers that has the largest sum. This problem is also known as the "Maximum
 * Subarray Problem." The implementation uses Kadane's algorithm, which runs in
 * linear time.
 */

#include <cassert>
#include <climits>
#include <vector>

int findMaxSubarraySum(const std::vector<int> &numbers) {
  int currentSum = 0;
  int maxSum = INT_MIN;

  for (const auto &num : numbers) {
    currentSum = std::max(num, currentSum + num);
    maxSum = std::max(maxSum, currentSum);
  }

  return maxSum;
}

void testMaxSubarraySum() {
  assert(findMaxSubarraySum({1, -2, 3, 10, -4, 7, 2, -5}) == 18);
  assert(findMaxSubarraySum({-2, -8, -1, -5, -9}) == -1);
  assert(findMaxSubarraySum({2, 8, 1, 5, 9}) == 25);
  assert(findMaxSubarraySum({2}) == 2);
}

int main() {
  testMaxSubarraySum();
  return 0;
}
