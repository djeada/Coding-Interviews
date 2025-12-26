/*
 * N-QUEENS PUZZLE (N=8)
 *
 * Find all valid arrangements to place eight chess queens on an 8×8 chessboard
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
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

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

  assert(permSol == expectedSolutions);
  assert(backSol == expectedSolutions);

  std::cout << "Permutation Solution: " << permSol << std::endl;
  std::cout << "Backtracking Solution: " << backSol << std::endl;

  std::cout << "All tests passed!" << std::endl;
}

int main() {
  test();
  return 0;
}
