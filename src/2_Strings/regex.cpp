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

#include <cassert>
#include <vector>
#include <string>
#include <iostream>

// Simple Recursive Solution
// Complexity: Exponential O(2^n) due to recursion, suitable only for short strings.
bool simpleMatch(const std::string &s, const std::string &p, int i = 0, int j = 0) {
    if (j == p.size()) return i == s.size();

    bool first_match = (i < s.size() && (p[j] == s[i] || p[j] == '.'));

    if (j + 1 < p.size() && p[j + 1] == '*') {
        return (simpleMatch(s, p, i, j + 2) ||
                (first_match && simpleMatch(s, p, i + 1, j)));
    } else {
        return first_match && simpleMatch(s, p, i + 1, j + 1);
    }
}

// Optimal Dynamic Programming Solution
// Complexity: O(m*n), optimal for practical use.
bool optimalMatch(const std::string &s, const std::string &p) {
    int m = s.size(), n = p.size();
    std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1, false));

    dp[0][0] = true;
    for (int j = 2; j <= n; j += 2)
        dp[0][j] = dp[0][j - 2] && p[j - 1] == '*';

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (p[j - 1] == '*') {
                dp[i][j] = dp[i][j - 2] ||
                           (dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
            } else {
                dp[i][j] = dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
            }
        }
    }

    return dp[m][n];
}

// Testing correctness
void runTests() {
    std::vector<std::pair<std::string, std::string>> testCases{
        {"aab", "c*a*b"},
        {"mississippi", "mis*is*p*."},
        {"", "a*"},
        {"abc", "abc"},
        {"ab", ".*"},
        {"aaa", "ab*a*c*a"}
    };

    std::vector<bool> expected{true, false, true, true, true, true};

    for (size_t i = 0; i < testCases.size(); ++i) {
        bool simple_res = simpleMatch(testCases[i].first, testCases[i].second);
        bool optimal_res = optimalMatch(testCases[i].first, testCases[i].second);
        assert(simple_res == expected[i]);
        assert(optimal_res == expected[i]);
    }

    std::cout << "All tests passed!\n";
}

int main() {
    runTests();
    return 0;
}
