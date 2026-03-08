/*
 * Task: Find the contiguous subarray with the maximum sum.
 *
 * MAXIMUM SUBARRAY
 *
 * Problem:
 * Given an integer array, find the contiguous subarray with the largest sum
 * and return that sum.
 *
 * Constraints:
 * - 1 <= nums.size() <= 10^5
 * - -10^9 <= nums[i] <= 10^9
 *
 * Example:
 * Input: nums = [1,-2,3,10,-4,7,2,-5]
 * Output: 18
 */

#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <vector>

// Naive approach: Checks all possible contiguous subarrays (O(n^2) time
// complexity)
int findMaxSubarraySumNaive(const std::vector<int> &numbers) {
  int maxSum = INT_MIN;
  const int n = numbers.size();
  for (int i = 0; i < n; ++i) {
    int currentSum = 0;
    for (int j = i; j < n; ++j) {
      currentSum += numbers[j];
      maxSum = std::max(maxSum, currentSum);
    }
  }
  return maxSum;
}

// Optimal approach using Kadane's algorithm (O(n) time complexity)
int findMaxSubarraySumKadane(const std::vector<int> &numbers) {
  int currentSum = 0;
  int maxSum = INT_MIN;
  for (const auto &num : numbers) {
    currentSum = std::max(num, currentSum + num);
    maxSum = std::max(maxSum, currentSum);
  }
  return maxSum;
}

namespace {
struct TestRunner {
  int total = 0;
  int failed = 0;

  void expectEqual(int got, int expected, const std::string &label) {
    ++total;
    if (got == expected) {
      std::cout << "[PASS] " << label << "\n";
      return;
    }
    ++failed;
    std::cout << "[FAIL] " << label << " expected=" << expected
              << " got=" << got << "\n";
  }

  void summary() const {
    std::cout << "Tests: " << total - failed << " passed, " << failed
              << " failed, " << total << " total\n";
  }
};
} // namespace

void testMaxSubarraySum() {
  TestRunner runner;
  std::vector<int> testArray1{1, -2, 3, 10, -4, 7, 2, -5};
  int expected1 = 18;
  runner.expectEqual(findMaxSubarraySumNaive(testArray1), expected1,
                     "naive mixed");
  runner.expectEqual(findMaxSubarraySumKadane(testArray1), expected1,
                     "kadane mixed");

  std::vector<int> testArray2{-2, -8, -1, -5, -9};
  int expected2 = -1;
  runner.expectEqual(findMaxSubarraySumNaive(testArray2), expected2,
                     "naive all negative");
  runner.expectEqual(findMaxSubarraySumKadane(testArray2), expected2,
                     "kadane all negative");

  std::vector<int> testArray3{2, 8, 1, 5, 9};
  int expected3 = 25;
  runner.expectEqual(findMaxSubarraySumNaive(testArray3), expected3,
                     "naive all positive");
  runner.expectEqual(findMaxSubarraySumKadane(testArray3), expected3,
                     "kadane all positive");

  std::vector<int> testArray4{2};
  int expected4 = 2;
  runner.expectEqual(findMaxSubarraySumNaive(testArray4), expected4,
                     "naive single");
  runner.expectEqual(findMaxSubarraySumKadane(testArray4), expected4,
                     "kadane single");
  runner.summary();
}

int main() {
  testMaxSubarraySum();
  return 0;
}
