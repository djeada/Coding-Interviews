/*
 * LEVENSHTEIN DISTANCE (EDIT DISTANCE)
 *
 * Given two strings, calculate the Levenshtein distance (edit distance).
 * This distance is defined as the minimum number of operations (insertions, deletions,
 * or substitutions) needed to convert one string into the other.
 *
 * Constraints:
 * - The strings may contain uppercase and lowercase letters.
 * - Length of the strings will be at most 1000 characters.
 *
 * Visual illustration:
 *
 * Example:
 * Input: "kitten", "sitting"
 * Operations: kitten → sitten (substitute 's' for 'k'),
 *             sitten → sittin (substitute 'i' for 'e'),
 *             sittin → sitting (insert 'g')
 * Output: 3
 *
 * Example Input/Output:
 * Input: "flaw", "lawn"
 * Output: 2
 * Explanation: flaw → law (delete 'f'), law → lawn (insert 'n')
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

// Simple (Recursive) Solution
// Complexity: Exponential O(3^(max(len1, len2))) - for educational purposes only.
int simpleSolution(const std::string &s1, const std::string &s2, int i, int j) {
    if (i == 0) return j;
    if (j == 0) return i;

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

// Test cases for correctness
void test() {
    assert(optimalSolution("kitten", "kitten") == 0);
    assert(optimalSolution("bob", "bub") == 1);
    assert(optimalSolution("ROBOT", "robot") == 5);
    assert(optimalSolution("church", "ChUrCh") == 3);
    assert(optimalSolution("flaw", "lawn") == 2);
    
    // Testing simple solution on smaller inputs due to complexity
    assert(simpleSolution("abc", "yabd", 3, 4) == 2);

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
