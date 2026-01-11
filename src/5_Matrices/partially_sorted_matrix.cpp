/*
 * Task: Determine whether a target value exists in a row/column-sorted matrix.
 *
 * MATRIX VALUE SEARCH
 *
 * The matrix has the following properties:
 * - Each row is sorted left-to-right
 * - Each column is sorted top-to-bottom
 *
 * Example matrix:
 *   { 1,  2,  8,  9 }
 *   { 2,  4,  9, 12 }
 *   { 4,  7, 10, 13 }
 *   { 6,  8, 11, 15 }
 */

#include <iostream>
#include <string>
#include <vector>

// ----------------------- 1) Simple (Brute-force) Solution --------------------
// Check every element in the matrix until the target is found.
//
// Time Complexity:
// - O(n * m), where n = rows, m = columns
//
// Space Complexity:
// - O(1) extra space
//
bool searchMatrixSimple(const std::vector<std::vector<int>>& matrix, int target) {
  for (const auto& row : matrix) {
    for (int value : row) {
      if (value == target) return true;
    }
  }
  return false;
}

// ----------------------- 2) Optimal (Staircase) Solution ---------------------
//
// - Start at the top-right corner.
// - If current value > target → move left.
// - If current value < target → move down.
// - Eliminate one row or column at each step.
//
// Time Complexity:
// - O(n + m)
//   Each step removes a row or a column from consideration.
//
// Space Complexity:
// - O(1) extra space
//
bool searchMatrixOptimal(const std::vector<std::vector<int>>& matrix,
                         int target) {
  if (matrix.empty() || matrix[0].empty()) return false;

  int rows = matrix.size();
  int cols = matrix[0].size();

  int r = 0;
  int c = cols - 1;

  while (r < rows && c >= 0) {
    if (matrix[r][c] == target)
      return true;
    else if (matrix[r][c] > target)
      --c;      // move left
    else
      ++r;      // move down
  }
  return false;
}

// ------------------------------ Tests (2 examples) ---------------------------
struct TestRunner {
  int total = 0;
  int failed = 0;

  void expect(bool got, bool expected, const std::string& label) {
    ++total;
    if (got == expected) {
      std::cout << "[PASS] " << label << "\n";
    } else {
      ++failed;
      std::cout << "[FAIL] " << label << " expected=" << std::boolalpha
                << expected << " got=" << got << "\n";
    }
  }

  void summary() const {
    std::cout << "Tests: " << (total - failed) << " passed, "
              << failed << " failed, " << total << " total\n";
  }
};

int main() {
  std::vector<std::vector<int>> matrix = {
      {1, 2, 8, 9},
      {2, 4, 9, 12},
      {4, 7, 10, 13},
      {6, 8, 11, 15}
  };

  TestRunner t;

  // Example 1: target exists
  t.expect(searchMatrixSimple(matrix, 7), true, "simple: contains 7");
  t.expect(searchMatrixOptimal(matrix, 7), true, "optimal: contains 7");

  // Example 2: target does not exist
  t.expect(searchMatrixSimple(matrix, 5), false, "simple: missing 5");
  t.expect(searchMatrixOptimal(matrix, 5), false, "optimal: missing 5");

  t.summary();
  return (t.failed == 0) ? 0 : 1;
}
