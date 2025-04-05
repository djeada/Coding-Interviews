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

// Optimal Solution
// Uses character frequency map, O(n) complexity
bool optimalSolution(const std::string& str1, const std::string& str2) {
    if (str1.size() != str2.size()) return false;

    std::unordered_map<char, int> freq;
    for (char ch : str1) {
        freq[ch]++;
    }

    for (char ch : str2) {
        if (freq.find(ch) == freq.end() || --freq[ch] < 0) {
            return false;
        }
    }

    return true;
}

// Test cases for correctness
void test() {
    assert(optimalSolution("silent", "listen"));
    assert(optimalSolution("evil", "live"));
    assert(!optimalSolution("there", "their"));
    assert(optimalSolution("123", "321"));
    assert(!optimalSolution("hello", "bello"));

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
