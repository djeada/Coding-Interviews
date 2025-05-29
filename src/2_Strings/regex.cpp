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
 * Explanation: 'c' can be repeated 0 times, 'a' can be repeated 2 times, followed by 'b'.
 *
 * Input: str = "mississippi", pattern = "mis*is*p*."
 * Output: false
 * Explanation: pattern does not match the entire string.
 *
 * Visual Example:
 * Input: "ab", pattern: ".*"
 * Matches: '.' matches 'a', '*' allows '.' to match 'b' also.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

// --- Implementations ---

// Simple Recursive Solution (O(2^n))
bool simpleMatchHelper(const std::string &s, const std::string &p, int i, int j) {
    if (j == (int)p.size()) return i == (int)s.size();
    bool first_match = (i < (int)s.size() && (p[j] == s[i] || p[j] == '.'));
    if (j + 1 < (int)p.size() && p[j + 1] == '*') {
        // Skip '*' or consume one char and stay on '*'
        return simpleMatchHelper(s, p, i, j + 2) ||
               (first_match && simpleMatchHelper(s, p, i + 1, j));
    } else {
        return first_match && simpleMatchHelper(s, p, i + 1, j + 1);
    }
}

bool simpleMatch(const std::string &s, const std::string &p) {
    return simpleMatchHelper(s, p, 0, 0);
}

// Optimal Dynamic Programming Solution (O(m*n))
bool optimalMatch(const std::string &s, const std::string &p) {
    int m = s.size(), n = p.size();
    std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1, false));
    dp[0][0] = true;
    // Patterns like a*, a*b*, a*b*c* can match empty string
    for (int j = 2; j <= n; j += 2) {
        dp[0][j] = dp[0][j - 2] && p[j - 1] == '*';
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (p[j - 1] == '*') {
                // zero occurrences or at least one
                dp[i][j] = dp[i][j - 2] ||
                           (dp[i - 1][j] && (p[j - 2] == s[i - 1] || p[j - 2] == '.'));
            } else {
                dp[i][j] = dp[i - 1][j - 1] &&
                           (p[j - 1] == s[i - 1] || p[j - 1] == '.');
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

void testSimpleMatch(const std::vector<TestCase>& cases) {
    std::cout << "=== Testing simpleMatch ===\n";
    for (const auto& tc : cases) {
        bool got = simpleMatch(tc.s, tc.p);
        bool pass = (got == tc.expected);
        std::cout << tc.name
                  << ": simpleMatch(\"" << tc.s << "\", \"" << tc.p << "\")"
                  << " expected=" << (tc.expected ? "true" : "false")
                  << ", got="    << (got       ? "true" : "false")
                  << " -> "      << (pass      ? "PASS" : "FAIL")
                  << "\n";
        assert(pass);
    }
    std::cout << "\n";
}

void testOptimalMatch(const std::vector<TestCase>& cases) {
    std::cout << "=== Testing optimalMatch ===\n";
    for (const auto& tc : cases) {
        bool got = optimalMatch(tc.s, tc.p);
        bool pass = (got == tc.expected);
        std::cout << tc.name
                  << ": optimalMatch(\"" << tc.s << "\", \"" << tc.p << "\")"
                  << " expected=" << (tc.expected ? "true" : "false")
                  << ", got="    << (got       ? "true" : "false")
                  << " -> "      << (pass      ? "PASS" : "FAIL")
                  << "\n";
        assert(pass);
    }
    std::cout << "\n";
}

int main() {
    std::vector<TestCase> cases = {
        { "Match c*a*b",       "aab",         "c*a*b",      true  },
        { "Mismatch mis*p*.", "mississippi", "mis*is*p*.", false },
        { "Empty against a*",  "",            "a*",         true  },
        { "Exact match",      "abc",         "abc",        true  },
        { "Wildcard .*",      "ab",          ".*",         true  },
        { "Complex mix",      "aaa",         "ab*a*c*a",   true  }
    };

    testSimpleMatch(cases);
    testOptimalMatch(cases);

    std::cout << "All tests passed successfully!\n";
    return 0;
}
