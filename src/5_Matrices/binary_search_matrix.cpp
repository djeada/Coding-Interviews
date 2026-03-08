/*
 * Task: Determine whether a target value exists in a sorted 2D matrix.
 *
 * SEARCH A 2D MATRIX (BINARY SEARCH)
 *
 * Problem:
 * Given an m x n matrix that is globally sorted in row-major order (each row
 * sorted, and first element of each row greater than the last of the previous
 * row), determine whether target exists in the matrix.
 *
 * Constraints:
 * - 1 <= m, n <= 10^3
 * - -10^9 <= matrix[i][j], target <= 10^9
 * - Matrix follows row-major sorted order.
 *
 * Example:
 * Input: matrix = [[1,3,5],[7,9,11],[13,15,17]], target = 7
 * Output: true
 */

#include <iostream>
#include <string>
#include <vector>

// Binary search by treating the 2D matrix as a flattened sorted array.
bool contains(const std::vector<std::vector<int>> &matrix, int value) {
  if (matrix.empty() || matrix.front().empty())
    return false;

  const int rows = static_cast<int>(matrix.size());
  const int cols = static_cast<int>(matrix.front().size());
  int start = 0;
  int end = rows * cols - 1;

  while (start <= end) {
    int mid = start + (end - start) / 2;
    int row = mid / cols;
    int col = mid % cols;
    int v = matrix[row][col];

    if (v == value) {
      return true;
    } else if (v > value) {
      end = mid - 1;
    } else {
      start = mid + 1;
    }
  }

  return false;
}

namespace {
struct TestRunner {
  int total = 0;
  int failed = 0;

  void expectEqual(bool got, bool expected, const std::string &label) {
    ++total;
    if (got == expected) {
      std::cout << "[PASS] " << label << "\n";
      return;
    }
    ++failed;
    std::cout << "[FAIL] " << label << " expected=" << std::boolalpha
              << expected << " got=" << got << "\n";
  }

  void summary() const {
    std::cout << "Tests: " << total - failed << " passed, " << failed
              << " failed, " << total << " total\n";
  }
};
} // namespace

// Test cases for correctness
void test() {
  std::vector<std::vector<int>> matrix{{1, 3, 5}, {7, 9, 11}, {13, 15, 17}};
  TestRunner runner;

  // Value exists in the matrix
  runner.expectEqual(contains(matrix, 7), true, "contains middle value");
  // Value at the beginning of the matrix
  runner.expectEqual(contains(matrix, 1), true, "contains first value");
  // Value at the end of the matrix
  runner.expectEqual(contains(matrix, 17), true, "contains last value");
  // Value does not exist in the matrix
  runner.expectEqual(contains(matrix, 6), false, "missing value");
  runner.summary();
}

int main() {
  test();
  return 0;
}
