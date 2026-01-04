/*
 * Task: Find the length of the longest increasing path in a matrix.
 *
 * LONGEST INCREASING PATH IN A MATRIX
 *
 * Find the length of the longest strictly increasing path in a given 2D matrix.
 * From any cell, you can move in four directions (up, down, left, right) to a
 * neighboring cell with a higher value.
 *
 * Three solutions are provided:
 *
 * 1. Simple (Brute-force DFS) Solution:
 *    Recursively explores all paths from each cell without caching intermediate
 *    results. This approach is easy to implement but suffers from exponential
 *    time complexity.
 *
 * 2. Optimal (DFS with Memoization) Solution:
 *    Uses depth-first search (DFS) along with memoization to cache the length
 * of the longest increasing path starting from each cell, significantly
 * reducing redundant computations. Time complexity: O(m*n).
 *
 * 3. Alternative (Topological Sort) Solution:
 *    Constructs a directed acyclic graph (DAG) based on the matrix and performs
 * a topological sort (using a BFS-like approach) to compute the longest
 * increasing path. This method leverages in-degrees to start from local minima.
 *
 * ASCII Illustration:
 *
 *     Consider the matrix:
 *
 *         [ 9, 9, 4 ]
 *         [ 6, 6, 8 ]
 *         [ 2, 1, 1 ]
 *
 *     One longest increasing path is:
 *         1 -> 2 -> 6 -> 9
 *
 * Example:
 *   Input:
 *     matrix = [ [9, 9, 4],
 *                [6, 6, 8],
 *                [2, 1, 1] ]
 *
 *   Output:
 *     4
 *
 *   Explanation:
 *     The longest increasing path is of length 4, for example: 1 -> 2 -> 6
 * -> 9.
 */

#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
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

// ----------------------- Simple (Brute-force DFS) Solution
// -----------------------
int dfsSimple(const std::vector<std::vector<int>> &matrix, int i, int j,
              int prev, int m, int n) {
  // Out of bounds or not strictly increasing.
  if (i < 0 || i >= m || j < 0 || j >= n || matrix[i][j] <= prev)
    return 0;

  int up = dfsSimple(matrix, i - 1, j, matrix[i][j], m, n);
  int down = dfsSimple(matrix, i + 1, j, matrix[i][j], m, n);
  int left = dfsSimple(matrix, i, j - 1, matrix[i][j], m, n);
  int right = dfsSimple(matrix, i, j + 1, matrix[i][j], m, n);

  return 1 + std::max({up, down, left, right});
}

int simpleSolution(const std::vector<std::vector<int>> &matrix) {
  if (matrix.empty() || matrix[0].empty())
    return 0;
  int m = matrix.size(), n = matrix[0].size();
  int longest = 0;
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; ++j)
      longest = std::max(longest, dfsSimple(matrix, i, j, INT_MIN, m, n));
  return longest;
}

// ----------------------- Optimal (DFS with Memoization) Solution
// -----------------------
int dfsMemo(const std::vector<std::vector<int>> &matrix, int i, int j,
            std::vector<std::vector<int>> &memo) {
  if (memo[i][j] != 0)
    return memo[i][j];

  int m = matrix.size(), n = matrix[0].size();
  int best = 1;
  std::vector<std::pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  for (auto &d : dirs) {
    int x = i + d.first, y = j + d.second;
    if (x >= 0 && x < m && y >= 0 && y < n && matrix[x][y] > matrix[i][j]) {
      best = std::max(best, 1 + dfsMemo(matrix, x, y, memo));
    }
  }
  memo[i][j] = best;
  return best;
}

int optimalSolution(const std::vector<std::vector<int>> &matrix) {
  if (matrix.empty() || matrix[0].empty())
    return 0;
  int m = matrix.size(), n = matrix[0].size();
  int longest = 0;
  std::vector<std::vector<int>> memo(m, std::vector<int>(n, 0));
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; ++j)
      longest = std::max(longest, dfsMemo(matrix, i, j, memo));
  return longest;
}

// ----------------------- Alternative (Topological Sort) Solution
// -----------------------
int alternativeSolution(const std::vector<std::vector<int>> &matrix) {
  if (matrix.empty() || matrix[0].empty())
    return 0;

  int m = matrix.size(), n = matrix[0].size();
  std::vector<std::vector<int>> indegree(m, std::vector<int>(n, 0));
  std::vector<std::pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  // Compute in-degrees.
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; ++j)
      for (auto &d : dirs) {
        int x = i + d.first, y = j + d.second;
        if (x >= 0 && x < m && y >= 0 && y < n && matrix[x][y] < matrix[i][j])
          indegree[i][j]++;
      }

  // Queue for cells with in-degree 0.
  std::queue<std::pair<int, int>> q;
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; ++j)
      if (indegree[i][j] == 0)
        q.push({i, j});

  int level = 0;
  while (!q.empty()) {
    int size = q.size();
    ++level;
    for (int i = 0; i < size; ++i) {
      auto [r, c] = q.front();
      q.pop();
      for (auto &d : dirs) {
        int x = r + d.first, y = c + d.second;
        if (x >= 0 && x < m && y >= 0 && y < n && matrix[x][y] > matrix[r][c]) {
          if (--indegree[x][y] == 0)
            q.push({x, y});
        }
      }
    }
  }
  return level;
}

// ----------------------- Test cases for correctness -----------------------
void test() {
  std::vector<std::vector<int>> matrix1 = {{9, 9, 4}, {6, 6, 8}, {2, 1, 1}};
  int expected1 = 4; // One longest increasing path: 1 -> 2 -> 6 -> 9

  // Due to exponential time, simpleSolution is only feasible for small
  // matrices.
  int resultSimple = simpleSolution(matrix1);
  int resultOptimal = optimalSolution(matrix1);
  int resultAlternative = alternativeSolution(matrix1);

  TestRunner runner;
  runner.expectEqual(resultSimple, expected1, "simple matrix1");
  runner.expectEqual(resultOptimal, expected1, "optimal matrix1");
  runner.expectEqual(resultAlternative, expected1, "alternative matrix1");
  runner.summary();
}

int main() {
  test();
  return 0;
}
