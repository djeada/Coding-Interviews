/*
 * Task: Compute the total Hamming distance across all pairs in an array.
 *
 * TOTAL HAMMING DISTANCE
 *
 * Given an array of integers, compute the total Hamming distance between all
 * pairs of integers in the array. The Hamming distance between two numbers is
 * defined as the number of positions at which the corresponding bits are
 * different.
 *
 * Two modern C++ solutions are provided:
 *
 * 1. Simple (Brute-force) Solution:
 *    - Compares every pair of numbers and counts differing bits using bitwise
 * operations.
 *    - Complexity: O(n^2 * b), where b is the number of bits (typically 32).
 *    - This solution is straightforward but may be inefficient for large
 * arrays.
 *
 * 2. Optimal (Efficient) Solution using Bitwise Aggregation:
 *    - For each bit position, counts the number of numbers with that bit set.
 *    - Computes the contribution of that bit position as:
 *           count_ones * (n - count_ones)
 *    - Sums the contributions over all bit positions.
 *    - Complexity: O(n * b), which is efficient for large arrays.
 *
 * ASCII Illustration:
 *
 *   Consider the array: [4, 14, 2]
 *   Binary representations:
 *       4  -> 0100
 *      14  -> 1110
 *       2  -> 0010
 *
 *   Hamming Distances:
 *      4 vs 14: differences in positions: 0100 vs 1110 -> 2 differences.
 *      4 vs 2 : differences in positions: 0100 vs 0010 -> 2 differences.
 *     14 vs 2 : differences in positions: 1110 vs 0010 -> 1 difference.
 *
 *   Total Hamming Distance = 2 + 2 + 1 = 5
 *
 * Example Input/Output:
 * Input:  [4, 14, 2]
 * Output: 5
 * Explanation:
 * The pairwise Hamming distances are calculated as above and summed.
 */

#include <iostream>
#include <string>
#include <vector>

// Simple (Brute-force) Solution
// Compares every pair and counts differing bits.
int simpleSolution(const std::vector<int> &nums) {
  int total = 0;
  int n = static_cast<int>(nums.size());
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      int xorVal = nums[i] ^ nums[j];
      while (xorVal) {
        total += xorVal & 1;
        xorVal >>= 1;
      }
    }
  }
  return total;
}

// Optimal (Efficient) Solution using Bitwise Aggregation
int optimalSolution(const std::vector<int> &nums) {
  int total = 0;
  int n = static_cast<int>(nums.size());
  for (int bit = 0; bit < 32; ++bit) {
    int countOnes = 0;
    for (int num : nums) {
      if (num & (1 << bit))
        ++countOnes;
    }
    total += countOnes * (n - countOnes);
  }
  return total;
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

// Test cases for correctness
void test() {
  std::vector<std::vector<int>> testInputs = {
      {4, 14, 2}, {0, 0}, {1, 2, 3, 4}, {7, 7, 7}};
  std::vector<int> expectedOutputs = {
      6,  // For [4, 14, 2], total Hamming distance is 6.
      0,  // For [0, 0], all elements are 0, so distance is 0.
      11, //  For [1, 2, 3, 4], total Hamming distance is 11.
      0   // For [7, 7, 7], all elements are identical, so distance is 0.
  };
  TestRunner runner;

  for (size_t i = 0; i < testInputs.size(); ++i) {
    int resSimple = simpleSolution(testInputs[i]);
    int resOptimal = optimalSolution(testInputs[i]);
    runner.expectEqual(resSimple, expectedOutputs[i],
                       "simple case " + std::to_string(i + 1));
    runner.expectEqual(resOptimal, expectedOutputs[i],
                       "optimal case " + std::to_string(i + 1));
  }
  runner.summary();
}

int main() {
  test();
  return 0;
}
