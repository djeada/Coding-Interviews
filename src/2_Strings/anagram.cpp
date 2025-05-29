/*
 * CHECK IF TWO STRINGS ARE ANAGRAMS
 *
 * Determine if two given strings are anagrams of each other. An anagram is formed
 * by rearranging the letters of one word or phrase to produce another, using all
 * original letters exactly once.
 *
 * Constraints:
 * - Both strings can contain letters, digits, and spaces.
 * - Comparison is case-sensitive.
 * - Length of each string will be up to 10^5 characters.
 *
 * Example Input/Output:
 * Input: str1 = "silent", str2 = "listen"
 * Output: true
 * Explanation: "silent" is an anagram of "listen".
 */

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// Optimal Solution: checks if two strings are anagrams in O(n)
bool optimalSolution(const std::string& str1, const std::string& str2) {
    if (str1.size() != str2.size()) return false;
    std::unordered_map<char, int> freq;
    for (char ch : str1) freq[ch]++;
    for (char ch : str2) {
        if (freq.find(ch) == freq.end() || --freq[ch] < 0) {
            return false;
        }
    }
    return true;
}

struct TestCase {
    std::string name;
    std::string a, b;
    bool expected;
};

void testOptimalSolution(const std::vector<TestCase>& cases) {
    std::cout << "=== Testing optimalSolution ===\n";
    for (const auto& tc : cases) {
        bool got = optimalSolution(tc.a, tc.b);
        bool pass = (got == tc.expected);
        std::cout
            << tc.name
            << ": (\"" << tc.a << "\", \"" << tc.b << "\") "
            << "expected=" << (tc.expected ? "true" : "false")
            << ", got="    << (got       ? "true" : "false")
            << " -> "      << (pass      ? "PASS" : "FAIL")
            << "\n";
        assert(pass);
    }
    std::cout << "\n";
}

int main() {
    std::vector<TestCase> cases = {
        { "Simple anagram",        "silent",   "listen",   true  },
        { "Another anagram",       "evil",     "live",     true  },
        { "Not anagram diff len",  "there",    "theirx",   false },
        { "Same digits",           "123",      "321",      true  },
        { "Mismatch chars",        "hello",    "bello",    false },
        { "Empty strings",         "",         "",         true  },
        { "Single char true",      "a",        "a",        true  },
        { "Single char false",     "a",        "b",        false }
    };

    testOptimalSolution(cases);

    std::cout << "All tests passed successfully!\n";
    return 0;
}
