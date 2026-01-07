/*
 * Task: Determine whether a target value exists in a row/column-sorted matrix.
 *
 * Matrix Value Search
 *
 * Given a matrix where each row and each column is sorted in ascending order,
 * determine if a given target value exists within the matrix.
 *
 * Constraints and Expectations:
 * - Each row is sorted left-to-right.
 * - Each column is sorted top-to-bottom.
 * - The task is to implement two solutions:
 *   1. A Simple (Divide and Conquer) Approach: Uses recursion to narrow down
 * the search space.
 *   2. An Optimal (Staircase) Approach: Iteratively searches from the top-right
 * corner.
 * - An alternative brute-force solution is also provided for educational
 * comparison.
 *
 * ASCII Illustration of the Matrix:
 *       +----+----+----+----+
 *       |  1 |  2 |  8 |  9 |
 *       +----+----+----+----+
 *       |  2 |  4 |  9 | 12 |
 *       +----+----+----+----+
 *       |  4 |  7 | 10 | 13 |
 *       +----+----+----+----+
 *       |  6 |  8 | 11 | 15 |
 *       +----+----+----+----+
 *
 * Example:
 * Input: Matrix as shown above, Target = 7
 * Output: true
 * Explanation: The value 7 is located at row 3, column 2 (0-indexed) of the
 * matrix.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Simple (Divide and Conquer) Solution
// Recursive approach: divides the matrix into submatrices based on the middle
// element. Average complexity may be better than brute-force, though worst-case
// may involve overlapping searches.
bool simpleSolutionHelper(const std::vector<std::vector<int>> &matrix,
                          int value, int row1, int col1, int row2, int col2) {
  if (row1 > row2 || col1 > col2)
    return false;

  // If target is outside the current submatrix's range, skip search.
  if (value < matrix[row1][col1] || value > matrix[row2][col2])
    return false;

  // Directly check boundaries.
  if (value == matrix[row1][col1] || value == matrix[row2][col2])
    return true;

  int midRow = (row1 + row2) / 2;
  int midCol = (col1 + col2) / 2;

  if (matrix[midRow][midCol] == value)
    return true;

  if (value < matrix[midRow][midCol]) {
    // Exclude the bottom-right quadrant.
    return simpleSolutionHelper(matrix, value, row1, col1, midRow,
                                midCol - 1) ||
           simpleSolutionHelper(matrix, value, row1, midCol, midRow - 1,
                                col2) ||
           simpleSolutionHelper(matrix, value, midRow + 1, col1, row2,
                                midCol - 1);
  }

  // value > mid: exclude the top-left quadrant.
  return simpleSolutionHelper(matrix, value, midRow, midCol + 1, row2, col2) ||
         simpleSolutionHelper(matrix, value, midRow + 1, col1, row2, midCol) ||
         simpleSolutionHelper(matrix, value, row1, midCol + 1, midRow - 1,
                              col2);
}

bool simpleSolution(const std::vector<std::vector<int>> &matrix, int value) {
  if (matrix.empty() || matrix.front().empty())
    return false;
  return simpleSolutionHelper(matrix, value, 0, 0,
                              static_cast<int>(matrix.size()) - 1,
                              static_cast<int>(matrix[0].size()) - 1);
}

// Optimal (Staircase) Solution
// Iterative approach starting from the top-right corner, reducing the search
// space at each step. Complexity: O(n + m), where n is the number of rows and m
// is the number of columns.
bool optimalSolution(const std::vector<std::vector<int>> &matrix, int value) {
  if (matrix.empty() || matrix.front().empty())
    return false;

  int rows = matrix.size(), cols = matrix[0].size();
  int row = 0, col = cols - 1;

  while (row < rows && col >= 0) {
    if (matrix[row][col] == value)
      return true;
    else if (matrix[row][col] > value)
      --col;
    else
      ++row;
  }

  return false;
}

// (Optional) Alternative Solution
// Brute-force search for educational purposes. Complexity: O(n * m)
bool alternativeSolution(const std::vector<std::vector<int>> &matrix,
                         int value) {
  for (const auto &row : matrix)
    for (const auto &elem : row)
      if (elem == value)
        return true;
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
  std::vector<std::vector<int>> matrix{
      {1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
  TestRunner runner;

  // Test for a value that exists in the matrix.
  runner.expectEqual(simpleSolution(matrix, 7), true, "simple contains 7");
  runner.expectEqual(optimalSolution(matrix, 7), true, "optimal contains 7");
  runner.expectEqual(alternativeSolution(matrix, 7), true,
                     "alternative contains 7");

  // Test for a value that does not exist.
  runner.expectEqual(simpleSolution(matrix, 5), false, "simple missing 5");
  runner.expectEqual(optimalSolution(matrix, 5), false, "optimal missing 5");
  runner.expectEqual(alternativeSolution(matrix, 5), false,
                     "alternative missing 5");

  // Test boundaries.
  runner.expectEqual(simpleSolution(matrix, 1), true, "simple contains 1");
  runner.expectEqual(optimalSolution(matrix, 1), true, "optimal contains 1");
  runner.expectEqual(alternativeSolution(matrix, 1), true,
                     "alternative contains 1");

  runner.expectEqual(simpleSolution(matrix, 15), true, "simple contains 15");
  runner.expectEqual(optimalSolution(matrix, 15), true, "optimal contains 15");
  runner.expectEqual(alternativeSolution(matrix, 15), true,
                     "alternative contains 15");
  runner.summary();
}

int main() {
  test();
  return 0;
}
