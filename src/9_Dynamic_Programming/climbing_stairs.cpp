/*
 * Task: Count the number of ways to climb N steps with allowed step sizes.
 *
 * CLIMBING STAIRS WITH CUSTOM STEPS
 *
 * Problem:
 * Given an integer N and a list of allowed step sizes, return the number of
 * distinct ordered ways to reach exactly step N.
 *
 * Constraints:
 * - 0 <= N <= 1000
 * - 1 <= allowedSteps.size() <= 10
 * - Each allowed step is a positive integer.
 *
 * Example:
 * Input: N = 5, allowedSteps = [1,2]
 * Output: 8
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Simple (Recursive) Solution
// Complexity: O(N^M) where M is size of allowedSteps
int simpleSolution(int N, const std::vector<int> &allowedSteps) {
  if (N == 0)
    return 1;
  if (N < 0)
    return 0;

  int totalWays = 0;
  for (int step : allowedSteps) {
    totalWays += simpleSolution(N - step, allowedSteps);
  }

  return totalWays;
}

// Optimal (Dynamic Programming) Solution
// Complexity: O(N * M)
int optimalSolution(int N, const std::vector<int> &allowedSteps) {
  std::vector<int> dp(N + 1, 0);
  dp[0] = 1;

  for (int i = 1; i <= N; ++i) {
    for (int step : allowedSteps) {
      if (i - step >= 0)
        dp[i] += dp[i - step];
    }
  }

  return dp[N];
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
  struct TestCase {
    int N;
    std::vector<int> allowedSteps;
    int expected;
  };

  std::vector<TestCase> tests = {{4, {1, 3}, 3},
                                 {5, {1, 2}, 8},
                                 {3, {2}, 0},
                                 {7, {1, 3, 5}, 12},
                                 {10, {2, 5}, 2}};
  TestRunner runner;

  for (const auto &test : tests) {
    int simple = simpleSolution(test.N, test.allowedSteps);
    int optimal = optimalSolution(test.N, test.allowedSteps);

    runner.expectEqual(simple, optimal,
                       "simple == optimal for N=" + std::to_string(test.N));
    runner.expectEqual(optimal, test.expected,
                       "expected ways for N=" + std::to_string(test.N));

    std::cout << "Stairs: " << test.N << " | Allowed Steps: ";
    for (int s : test.allowedSteps)
      std::cout << s << " ";
    std::cout << "| Ways: " << optimal << std::endl;
  }

  runner.summary();
}

int main() {
  test();
  return 0;
}
