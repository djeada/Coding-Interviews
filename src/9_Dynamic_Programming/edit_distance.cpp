/*
 * Task: Compute the Levenshtein (edit) distance between two strings.
 *
 * EDIT DISTANCE
 *
 * Problem:
 * Given two strings word1 and word2, return the minimum number of insertions,
 * deletions, and substitutions required to transform word1 into word2.
 *
 * Constraints:
 * - 0 <= word1.length, word2.length <= 1000
 * - Strings contain ASCII characters.
 *
 * Example:
 * Input: word1 = "kitten", word2 = "sitting"
 * Output: 3
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Simple (Recursive) Solution
// Complexity: Exponential O(3^(max(len1, len2))) - for educational purposes
// only.
int simpleSolution(const std::string &s1, const std::string &s2, int i, int j) {
  if (i == 0)
    return j;
  if (j == 0)
    return i;

  if (s1[i - 1] == s2[j - 1])
    return simpleSolution(s1, s2, i - 1, j - 1);

  return 1 + std::min({
                 simpleSolution(s1, s2, i - 1, j),    // Remove
                 simpleSolution(s1, s2, i, j - 1),    // Insert
                 simpleSolution(s1, s2, i - 1, j - 1) // Replace
             });
}

// Optimal (Dynamic Programming) Solution
// Complexity: O(len1 * len2), efficient and practical for large inputs.
int optimalSolution(const std::string &s1, const std::string &s2) {
  int len1 = s1.size(), len2 = s2.size();
  std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1));

  for (int i = 0; i <= len1; ++i)
    dp[i][0] = i;
  for (int j = 0; j <= len2; ++j)
    dp[0][j] = j;

  for (int i = 1; i <= len1; ++i) {
    for (int j = 1; j <= len2; ++j) {
      if (s1[i - 1] == s2[j - 1])
        dp[i][j] = dp[i - 1][j - 1];
      else
        dp[i][j] = 1 + std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
    }
  }

  return dp[len1][len2];
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
  TestRunner runner;
  runner.expectEqual(optimalSolution("kitten", "kitten"), 0,
                     "optimal kitten->kitten");
  runner.expectEqual(optimalSolution("bob", "bub"), 1, "optimal bob->bub");
  runner.expectEqual(optimalSolution("ROBOT", "robot"), 5,
                     "optimal ROBOT->robot");
  runner.expectEqual(optimalSolution("church", "ChUrCh"), 3,
                     "optimal church->ChUrCh");
  runner.expectEqual(optimalSolution("flaw", "lawn"), 2, "optimal flaw->lawn");

  // Testing simple solution on smaller inputs due to complexity
  runner.expectEqual(simpleSolution("abc", "yabd", 3, 4), 2,
                     "simple abc->yabd");
  runner.summary();
}

int main() {
  test();
  return 0;
}
