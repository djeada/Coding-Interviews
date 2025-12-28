/*
 * REGULAR EXPRESSION MATCHING
 *
 * Implement pattern matching with support for '.' and '*' where:
 *   '.' Matches any single character.
 *   '*' Matches zero or more occurrences of the preceding element.
 *
 * Constraints:
 * - Strings contain only lowercase English letters.
 * - Pattern may contain '.' and '*', along with lowercase English letters.
 * - Patterns like "a*" can match zero or more 'a's.
 *
 * Examples:
 * Input: str = "aab", pattern = "c*a*b"
 * Output: true
 * Explanation: 'c' can be repeated 0 times, 'a' can be repeated 2 times,
 * followed by 'b'.
 *
 * Input: str = "mississippi", pattern = "mis*is*p*."
 * Output: false
 * Explanation: pattern does not match the entire string.
 *
 * Visual Example:
 * Input: "ab", pattern: ".*"
 * Matches: '.' matches 'a', '*' allows '.' to match 'b' also.
 */

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

// --- Implementations ---

// Simple Recursive Solution (O(2^n))
bool simpleMatchHelper(const std::string &s, const std::string &p, size_t i,
                       size_t j) {
  if (j == p.size())
    return i == s.size();
  bool first_match = (i < s.size() && (p[j] == s[i] || p[j] == '.'));
  if (j + 1 < p.size() && p[j + 1] == '*') {
    return simpleMatchHelper(s, p, i, j + 2) ||
           (first_match && simpleMatchHelper(s, p, i + 1, j));
  }
  return first_match && simpleMatchHelper(s, p, i + 1, j + 1);
}

bool simpleMatch(const std::string &s, const std::string &p) {
  return simpleMatchHelper(s, p, 0, 0);
}

// Optimal Dynamic Programming Solution (O(m*n))
bool optimalMatch(const std::string &s, const std::string &p) {
  const size_t m = s.size();
  const size_t n = p.size();
  std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1, false));
  dp[0][0] = true;
  // Patterns like a*, a*b*, a*b*c* can match empty string
  for (size_t j = 2; j <= n; j += 2) {
    dp[0][j] = dp[0][j - 2] && p[j - 1] == '*';
  }
  for (size_t i = 1; i <= m; ++i) {
    for (size_t j = 1; j <= n; ++j) {
      if (p[j - 1] == '*' && j >= 2) {
        // zero occurrences or at least one
        dp[i][j] = dp[i][j - 2] ||
                   (dp[i - 1][j] && (p[j - 2] == s[i - 1] || p[j - 2] == '.'));
      } else if (p[j - 1] == '*') {
        dp[i][j] = false;
      } else {
        dp[i][j] =
            dp[i - 1][j - 1] && (p[j - 1] == s[i - 1] || p[j - 1] == '.');
      }
    }
  }
  return dp[m][n];
}

// --- Test infrastructure ---

struct TestCase {
  std::string name;
  std::string s;
  std::string p;
  bool expected;
};

template <typename Func>
void runTests(const std::string &label, const std::vector<TestCase> &cases,
              Func func) {
  std::cout << "=== Testing " << label << " ===\n";
  for (const auto &tc : cases) {
    bool got = func(tc.s, tc.p);
    bool pass = (got == tc.expected);
    std::cout << tc.name << ": " << label << "(\"" << tc.s << "\", \"" << tc.p
              << "\")" << " expected=" << (tc.expected ? "true" : "false")
              << ", got=" << (got ? "true" : "false") << " -> "
              << (pass ? "PASS" : "FAIL") << "\n";
    assert(pass);
  }
  std::cout << "\n";
}

int main() {
  std::vector<TestCase> cases = {
      {"Match c*a*b", "aab", "c*a*b", true},
      {"Mismatch mis*p*.", "mississippi", "mis*is*p*.", false},
      {"Empty against a*", "", "a*", true},
      {"Exact match", "abc", "abc", true},
      {"Wildcard .*", "ab", ".*", true},
      {"Complex mix", "aaa", "ab*a*c*a", true}};

  runTests("simpleMatch", cases, simpleMatch);
  runTests("optimalMatch", cases, optimalMatch);

  std::cout << "All tests passed successfully!\n";
  return 0;
}
