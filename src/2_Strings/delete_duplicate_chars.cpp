/*
 * REMOVE DUPLICATE CHARACTERS
 *
 * This program removes duplicate characters from a given string while preserving the order of first occurrences.
 * It demonstrates two main implementations:
 *   - simpleSolution: A brute-force approach that checks for each character's presence in the result string (O(n²)).
 *   - optimalSolution: An efficient approach using a hash table (std::unordered_set) to track characters (average O(n)).
 *
 * ASCII Illustration:
 *
 *   Input:   g  o  o  g  l  e
 *            |  |  |  |  |  |
 *            V  V  V  V  V  V
 *   Output:  g  o  l  e
 *
 * Example Input/Output:
 * Input: "google"
 * Output: "gole"
 * Explanation: The duplicate 'o' and 'g' characters are removed, preserving only their first appearance.
 */

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>

// Simple (Brute-force) Solution
// Time Complexity: O(n²), where n is the length of the input string.
std::string simpleSolution(const std::string& input) {
    std::string result;
    for (char c : input) {
        if (result.find(c) == std::string::npos) {
            result.push_back(c);
        }
    }
    return result;
}

// Optimal (Efficient) Solution
// Time Complexity: Average O(n) using a hash table.
std::string optimalSolution(const std::string& input) {
    std::string result;
    result.reserve(input.size());  // Reserve space to avoid reallocations.
    std::unordered_set<char> seen;
    for (char c : input) {
        if (seen.find(c) == seen.end()) {
            seen.insert(c);
            result.push_back(c);
        }
    }
    return result;
}

// (Optional) Additional Solution using std::remove_if and a lambda expression.
// This approach demonstrates an alternative modern technique even if it's not optimal for clarity.
std::string alternativeSolution(const std::string& input) {
    std::string result = input;
    std::unordered_set<char> seen;
    auto new_end = std::remove_if(result.begin(), result.end(), [&seen](char c) {
        if (seen.find(c) != seen.end())
            return true;
        seen.insert(c);
        return false;
    });
    result.erase(new_end, result.end());
    return result;
}

// Test cases for correctness
void test() {
    const std::string testInput1 = "google";
    const std::string expected1 = "gole";
    assert(simpleSolution(testInput1) == expected1);
    assert(optimalSolution(testInput1) == expected1);
    assert(alternativeSolution(testInput1) == expected1);

    const std::string testInput2 = "aaaaaaaaaaaaaaaaaaaaa";
    const std::string expected2 = "a";
    assert(simpleSolution(testInput2) == expected2);
    assert(optimalSolution(testInput2) == expected2);
    assert(alternativeSolution(testInput2) == expected2);

    const std::string testInput3 = "";
    const std::string expected3 = "";
    assert(simpleSolution(testInput3) == expected3);
    assert(optimalSolution(testInput3) == expected3);
    assert(alternativeSolution(testInput3) == expected3);

    const std::string testInput4 = "abcacbbacbcacabcba";
    const std::string expected4 = "abc";
    assert(simpleSolution(testInput4) == expected4);
    assert(optimalSolution(testInput4) == expected4);
    assert(alternativeSolution(testInput4) == expected4);

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
