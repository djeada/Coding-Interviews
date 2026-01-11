/*
 * Task: Verify whether a square matrix is a magic square.
 *
 * A magic square is an n x n matrix where:
 * - Every row sum is the same
 * - Every column sum is the same
 * - Main diagonal sum is the same
 * - Anti-diagonal sum is the same
 *
 * Example (3x3):
 *   [ 8, 1, 6 ]
 *   [ 3, 5, 7 ]
 *   [ 4, 9, 2 ]
 *   All sums = 15  -> true
 *
 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// ----------------------- 1) Simple (Brute-force) Solution --------------------
//
// Idea:
// - Compute target sum from first row.
// - Check all row sums, all column sums, then both diagonals.
//
// Time Complexity:
// - Row checks:      O(n^2)
// - Column checks:   O(n^2)
// - Diagonals:       O(n)
// => Total: O(n^2)
//
// Space Complexity:
// - O(1) extra space.
//
bool isMagicSquareSimple(const std::vector<std::vector<int>>& matrix) {
  const int n = static_cast<int>(matrix.size());
  if (n == 0) return false;

  // Validate square matrix: O(n)
  for (const auto& row : matrix) {
    if (static_cast<int>(row.size()) != n) return false;
  }

  // Target sum = first row: O(n)
  int target = 0;
  for (int v : matrix[0]) target += v;

  // Check rows: O(n^2)
  for (int i = 0; i < n; ++i) {
    int rowSum = 0;
    for (int j = 0; j < n; ++j) rowSum += matrix[i][j];
    if (rowSum != target) return false;
  }

  // Check columns: O(n^2)
  for (int j = 0; j < n; ++j) {
    int colSum = 0;
    for (int i = 0; i < n; ++i) colSum += matrix[i][j];
    if (colSum != target) return false;
  }

  // Check main diagonal: O(n)
  int diag1 = 0;
  for (int i = 0; i < n; ++i) diag1 += matrix[i][i];
  if (diag1 != target) return false;

  // Check anti-diagonal: O(n)
  int diag2 = 0;
  for (int i = 0; i < n; ++i) diag2 += matrix[i][n - 1 - i];
  if (diag2 != target) return false;

  return true;
}

// ----------------------- 2) Optimal (Single-pass) Solution -------------------
//
// Idea:
// - Compute target from first row.
// - In ONE traversal:
//   * compute each row sum and compare immediately
//   * accumulate column sums
//   * accumulate both diagonals
// - After traversal, verify diagonals + column sums.
//
// Time Complexity:
// - Single traversal of all cells: O(n^2)
// - Final column verification:     O(n)
// => Total: O(n^2)
//
// Space Complexity:
// - O(n) for column sums.
//
bool isMagicSquareOptimal(const std::vector<std::vector<int>>& matrix) {
  const int n = static_cast<int>(matrix.size());
  if (n == 0) return false;

  // Validate square matrix: O(n)
  for (const auto& row : matrix) {
    if (static_cast<int>(row.size()) != n) return false;
  }

  // Target sum = first row: O(n)
  int target = 0;
  for (int v : matrix[0]) target += v;

  std::vector<int> colSum(n, 0); // O(n) space
  int diag1 = 0, diag2 = 0;

  // Single pass over matrix: O(n^2)
  for (int i = 0; i < n; ++i) {
    int rowSum = 0;
    for (int j = 0; j < n; ++j) {
      const int val = matrix[i][j];
      rowSum += val;       // row sum
      colSum[j] += val;    // column sums
    }
    if (rowSum != target) return false; // early exit

    diag1 += matrix[i][i];           // main diagonal
    diag2 += matrix[i][n - 1 - i];   // anti-diagonal
  }

  // Diagonals: O(1) check
  if (diag1 != target || diag2 != target) return false;

  // Columns: O(n)
  for (int j = 0; j < n; ++j) {
    if (colSum[j] != target) return false;
  }

  return true;
}

// ------------------------------ Tests (2 examples) ---------------------------
//
// Time Complexity of tests is irrelevant; tiny fixed-size inputs.
//
struct TestRunner {
  int total = 0;
  int failed = 0;

  void expectEqual(bool got, bool expected, const std::string& label) {
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
    std::cout << "Tests: " << (total - failed) << " passed, " << failed
              << " failed, " << total << " total\n";
  }
};

int main() {
  // Example 1: Magic square -> true
  std::vector<std::vector<int>> magic = {
      {8, 1, 6},
      {3, 5, 7},
      {4, 9, 2},
  };

  // Example 2: Not a magic square -> false
  std::vector<std::vector<int>> notMagic = {
      {5, 3, 4},
      {1, 5, 8},
      {6, 4, 2},
  };

  TestRunner t;

  // Simple
  t.expectEqual(isMagicSquareSimple(magic), true, "simple: magic");
  t.expectEqual(isMagicSquareSimple(notMagic), false, "simple: not magic");

  // Optimal
  t.expectEqual(isMagicSquareOptimal(magic), true, "optimal: magic");
  t.expectEqual(isMagicSquareOptimal(notMagic), false, "optimal: not magic");

  t.summary();
  return (t.failed == 0) ? 0 : 1;
}
