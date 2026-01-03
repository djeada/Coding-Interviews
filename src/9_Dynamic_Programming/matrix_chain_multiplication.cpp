/*
 * Task: Compute the minimum scalar multiplications for a matrix chain.
 *
 * MATRIX CHAIN MULTIPLICATION OPTIMIZATION
 *
 * Determine the most efficient way to multiply a given chain of matrices. The
 * matrices are represented by a vector of dimensions where the i-th matrix has
 * dimensions dims[i-1] x dims[i]. The goal is to compute the minimum number of
 * scalar multiplications required to multiply all matrices in the chain.
 *
 * Three solutions are provided:
 *
 * 1. Simple (Brute-force) Recursive Solution:
 *    Recursively consider every possible split of the matrix chain and compute
 * the cost. This solution is simple but has exponential time complexity.
 *
 * 2. Optimal (Dynamic Programming) Solution:
 *    Uses a bottom-up DP approach to fill in a table where dp[i][j] represents
 * the minimum multiplication cost for matrices i to j. This solution runs in
 * O(n^3) time.
 *
 * 3. Alternative (Recursive with Memoization) Solution:
 *    A top-down recursive solution that uses memoization to store intermediate
 * results, reducing the number of repeated computations.
 *
 * ASCII Illustration:
 *
 *     Matrices: A1, A2, A3, A4
 *     Dimensions: {p0, p1, p2, p3, p4}
 *
 *     Optimal Parenthesization:
 *
 *         ((A1 x A2) x (A3 x A4))
 *
 * Example:
 *   Input: dims = {40, 20, 30, 10, 30}
 *   Output: 26000
 *
 *   Explanation:
 *     The optimal way to multiply four matrices of dimensions:
 *        A1: 40x20, A2: 20x30, A3: 30x10, A4: 10x30
 *     is to first multiply A1 and A2, then A3 and A4, and finally multiply the
 * results. This requires 26000 scalar multiplications.
 */

#include <cassert>
#include <climits>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// ----------------------- Simple (Brute-force) Recursive Solution
// -----------------------
int matrixChainOrderRecursive(const std::vector<int> &dims, int i, int j) {
  if (i == j)
    return 0;
  int minCost = INT_MAX;
  for (int k = i; k < j; ++k) {
    int cost = matrixChainOrderRecursive(dims, i, k) +
               matrixChainOrderRecursive(dims, k + 1, j) +
               dims[i - 1] * dims[k] * dims[j];
    if (cost < minCost)
      minCost = cost;
  }
  return minCost;
}

int simpleSolution(const std::vector<int> &dims) {
  int n = dims.size() - 1; // number of matrices
  return matrixChainOrderRecursive(dims, 1, n);
}

// ----------------------- Optimal (Dynamic Programming) Solution
// -----------------------
int optimalSolution(const std::vector<int> &dims) {
  int n = dims.size() - 1;
  // dp[i][j] represents the minimum cost to multiply matrices i...j
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, 0));

  // l is chain length.
  for (int l = 2; l <= n; ++l) {
    for (int i = 1; i <= n - l + 1; ++i) {
      int j = i + l - 1;
      dp[i][j] = INT_MAX;
      for (int k = i; k < j; ++k) {
        int cost = dp[i][k] + dp[k + 1][j] + dims[i - 1] * dims[k] * dims[j];
        if (cost < dp[i][j])
          dp[i][j] = cost;
      }
    }
  }
  return dp[1][n];
}

// ----------------------- Alternative (Recursive with Memoization) Solution
// -----------------------
int matrixChainOrderMemo(const std::vector<int> &dims, int i, int j,
                         std::vector<std::vector<int>> &memo) {
  if (i == j)
    return 0;
  if (memo[i][j] != -1)
    return memo[i][j];
  int minCost = INT_MAX;
  for (int k = i; k < j; ++k) {
    int cost = matrixChainOrderMemo(dims, i, k, memo) +
               matrixChainOrderMemo(dims, k + 1, j, memo) +
               dims[i - 1] * dims[k] * dims[j];
    if (cost < minCost)
      minCost = cost;
  }
  memo[i][j] = minCost;
  return minCost;
}

int alternativeSolution(const std::vector<int> &dims) {
  int n = dims.size() - 1;
  std::vector<std::vector<int>> memo(n + 1, std::vector<int>(n + 1, -1));
  return matrixChainOrderMemo(dims, 1, n, memo);
}

// ----------------------- Test cases for correctness -----------------------
void test() {
  // Test case 1
  std::vector<int> dims1 = {40, 20, 30, 10, 30};
  int expected1 = 26000;
  assert(simpleSolution(dims1) == expected1);
  assert(optimalSolution(dims1) == expected1);
  assert(alternativeSolution(dims1) == expected1);

  // Test case 2
  std::vector<int> dims2 = {10, 20, 30, 40, 30};
  int expected2 = 30000;
  assert(simpleSolution(dims2) == expected2);
  assert(optimalSolution(dims2) == expected2);
  assert(alternativeSolution(dims2) == expected2);

  // Test case 3: Single matrix multiplication cost is 0
  std::vector<int> dims3 = {10, 20};
  int expected3 = 0;
  assert(simpleSolution(dims3) == expected3);
  assert(optimalSolution(dims3) == expected3);
  assert(alternativeSolution(dims3) == expected3);

  std::cout << "All tests passed!\n";
}

int main() {
  test();
  return 0;
}
