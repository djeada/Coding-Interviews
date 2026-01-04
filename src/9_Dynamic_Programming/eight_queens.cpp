/*
 * Task: Count all valid arrangements of 8 queens on an 8x8 chessboard.
 *
 * N-QUEENS PUZZLE (N=8)
 *
 * Find all valid arrangements to place eight chess queens on an 8x8 chessboard
 * such that no two queens threaten each other. Queens threaten each other if
 * they share the same row, column, or diagonal.
 *
 * Constraints:
 * - Chessboard is 8×8 (fixed size).
 * - Exactly one queen per row, column, and diagonal.
 *
 * Visual illustration (example of valid arrangement for smaller N=4):
 *
 * . Q . .
 * . . . Q
 * Q . . .
 * . . Q .
 *
 * Example Input/Output:
 * Input: N = 8
 * Output: 92
 * Explanation: There are exactly 92 distinct solutions for the 8-queens
 * problem.
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

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

// Simple (Permutation-based) Recursive Solution
// Complexity: O(N! * N^2), generates all permutations and checks diagonals
int permutationSolution(int N) {
  std::vector<int> columns(N);
  for (int i = 0; i < N; ++i)
    columns[i] = i;

  int solutionCount = 0;

  auto isValid = [](const std::vector<int> &cols, int length) {
    for (int i = 0; i < length; ++i) {
      for (int j = i + 1; j < length; ++j) {
        if (abs(cols[i] - cols[j]) == abs(i - j))
          return false;
      }
    }
    return true;
  };

  do {
    if (isValid(columns, N))
      solutionCount++;
  } while (std::next_permutation(columns.begin(), columns.end()));

  return solutionCount;
}

// Optimal (Backtracking) Solution
// Complexity: O(N!), more efficient pruning early invalid branches
int backtrackingSolution(int N) {
  int solutionCount = 0;

  std::function<void(int, std::vector<int> &, std::vector<bool> &,
                     std::vector<bool> &, std::vector<bool> &)>
      solve = [&](int row, std::vector<int> &cols, std::vector<bool> &diag1,
                  std::vector<bool> &diag2, std::vector<bool> &columns) {
        if (row == N) {
          solutionCount++;
          return;
        }

        for (int col = 0; col < N; ++col) {
          if (columns[col] || diag1[row + col] || diag2[row - col + N - 1])
            continue;
          columns[col] = diag1[row + col] = diag2[row - col + N - 1] = true;
          cols[row] = col;
          solve(row + 1, cols, diag1, diag2, columns);
          columns[col] = diag1[row + col] = diag2[row - col + N - 1] = false;
        }
      };

  std::vector<int> cols(N);
  std::vector<bool> columns(N, false), diag1(2 * N - 1, false),
      diag2(2 * N - 1, false);
  solve(0, cols, diag1, diag2, columns);

  return solutionCount;
}

// Test cases to validate correctness
void test() {
  int N = 8;
  int expectedSolutions = 92;

  int permSol = permutationSolution(N);
  int backSol = backtrackingSolution(N);

  TestRunner runner;
  runner.expectEqual(permSol, expectedSolutions, "permutation solution");
  runner.expectEqual(backSol, expectedSolutions, "backtracking solution");

  std::cout << "Permutation Solution: " << permSol << std::endl;
  std::cout << "Backtracking Solution: " << backSol << std::endl;

  runner.summary();
}

int main() {
  test();
  return 0;
}
