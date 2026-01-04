/*
 * Task: Verify whether a square matrix is a magic square.
 *
 * MAGIC SQUARE VERIFICATION
 *
 * Check if a given square matrix is a magic square. A magic square is defined
 * as an n x n matrix in which the sums of each row, each column, the main
 * diagonal, and the anti-diagonal are all equal.
 *
 * ASCII Illustration:
 *
 *         [ 8, 1, 6 ]
 *         [ 3, 5, 7 ]
 *         [ 4, 9, 2 ]
 *
 *     All rows, columns, and diagonals sum to 15.
 *
 * Example:
 *   Input:
 *       magicSquare = [ [8, 1, 6],
 *                       [3, 5, 7],
 *                       [4, 9, 2] ]
 *
 *   Output:
 *       true
 *
 *   Explanation:
 *       Each row, column, and diagonal sums to 15, hence the matrix is a magic
 * square.
 */

#include <iostream>
#include <numeric>
#include <string>
#include <vector>

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

// ----------------------- Simple (Brute-force) Solution -----------------------
bool isMagicSquareSimple(const std::vector<std::vector<int>> &matrix) {
  int n = matrix.size();
  if (n == 0)
    return false;
  // Check if matrix is square.
  for (const auto &row : matrix) {
    if (row.size() != static_cast<size_t>(n))
      return false;
  }

  // Compute the target sum from the first row.
  int target = 0;
  for (int num : matrix[0])
    target += num;

  // Check row sums.
  for (const auto &row : matrix) {
    int sum = 0;
    for (int num : row)
      sum += num;
    if (sum != target)
      return false;
  }

  // Check column sums.
  for (int j = 0; j < n; ++j) {
    int sum = 0;
    for (int i = 0; i < n; ++i)
      sum += matrix[i][j];
    if (sum != target)
      return false;
  }

  // Check main diagonal.
  int diag1 = 0;
  for (int i = 0; i < n; ++i)
    diag1 += matrix[i][i];
  if (diag1 != target)
    return false;

  // Check anti-diagonal.
  int diag2 = 0;
  for (int i = 0; i < n; ++i)
    diag2 += matrix[i][n - 1 - i];
  if (diag2 != target)
    return false;

  return true;
}

// ----------------------- Optimal (Single-pass) Solution
// -----------------------
bool isMagicSquareOptimal(const std::vector<std::vector<int>> &matrix) {
  int n = matrix.size();
  if (n == 0)
    return false;
  for (const auto &row : matrix)
    if (row.size() != static_cast<size_t>(n))
      return false;

  // Calculate target sum from the first row.
  int target = 0;
  for (int j = 0; j < n; ++j)
    target += matrix[0][j];

  int diag1 = 0, diag2 = 0;
  // Initialize column sums.
  std::vector<int> colSum(n, 0);

  for (int i = 0; i < n; ++i) {
    int rowSum = 0;
    for (int j = 0; j < n; ++j) {
      rowSum += matrix[i][j];
      colSum[j] += matrix[i][j];
    }
    if (rowSum != target)
      return false;
    diag1 += matrix[i][i];
    diag2 += matrix[i][n - 1 - i];
  }

  if (diag1 != target || diag2 != target)
    return false;

  for (int sum : colSum)
    if (sum != target)
      return false;

  return true;
}

// ----------------------- Alternative (STL-based) Solution
// -----------------------
bool isMagicSquareAlternative(const std::vector<std::vector<int>> &matrix) {
  int n = matrix.size();
  if (n == 0)
    return false;
  for (const auto &row : matrix)
    if (row.size() != static_cast<size_t>(n))
      return false;

  // Compute target sum using std::accumulate on first row.
  int target = std::accumulate(matrix[0].begin(), matrix[0].end(), 0);

  // Check rows using std::accumulate.
  for (const auto &row : matrix) {
    if (std::accumulate(row.begin(), row.end(), 0) != target)
      return false;
  }

  // Check columns.
  for (int j = 0; j < n; ++j) {
    int colSum = 0;
    for (int i = 0; i < n; ++i)
      colSum += matrix[i][j];
    if (colSum != target)
      return false;
  }

  // Check main diagonal.
  int diag1 = 0;
  for (int i = 0; i < n; ++i)
    diag1 += matrix[i][i];
  if (diag1 != target)
    return false;

  // Check anti-diagonal.
  int diag2 = 0;
  for (int i = 0; i < n; ++i)
    diag2 += matrix[i][n - 1 - i];
  if (diag2 != target)
    return false;

  return true;
}

// ----------------------- Test cases for correctness -----------------------
void test() {
  std::vector<std::vector<int>> magicSquare = {{8, 1, 6}, {3, 5, 7}, {4, 9, 2}};

  std::vector<std::vector<int>> nonMagicSquare = {
      {5, 3, 4}, {1, 5, 8}, {6, 4, 2}};
  TestRunner runner;

  // Test Simple Solution
  runner.expectEqual(isMagicSquareSimple(magicSquare), true, "simple magic");
  runner.expectEqual(isMagicSquareSimple(nonMagicSquare), false,
                     "simple non-magic");

  // Test Optimal Solution
  runner.expectEqual(isMagicSquareOptimal(magicSquare), true, "optimal magic");
  runner.expectEqual(isMagicSquareOptimal(nonMagicSquare), false,
                     "optimal non-magic");

  // Test Alternative Solution
  runner.expectEqual(isMagicSquareAlternative(magicSquare), true,
                     "alternative magic");
  runner.expectEqual(isMagicSquareAlternative(nonMagicSquare), false,
                     "alternative non-magic");
  runner.summary();
}

int main() {
  test();
  return 0;
}
