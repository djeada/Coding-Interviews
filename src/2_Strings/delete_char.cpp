/*
 * DELETE SPECIFIED CHARACTERS FROM STRING
 *
 * This program deletes specified characters from a given string using modern C++ practices.
 * It demonstrates three approaches:
 *   1. simpleSolution: Iterates through the string and checks for deletion via std::string::find.
 *      - Time Complexity: O(n*m) where n is the length of the string and m is the length of the deletion set.
 *   2. optimalSolution: Uses an unordered_set for O(1) average lookup to quickly determine whether a character should be deleted.
 *      - Time Complexity: Average O(n + m), which is more efficient for larger inputs.
 *   3. alternativeSolution: Leverages std::remove_if with a lambda to remove characters in place.
 *
 * ASCII Illustration:
 *
 *   Input String:       W  e     a  r  e     s  t  u  d  e  n  t  s
 *   Characters to Delete: a, e, i, o, u
 *                        ↓  ↓     ↓  ↓  ↓     ↓  ↓  ↓  ↓  ↓  ↓  ↓  ↓
 *   Resulting String:   W     r       s  t  d  n  t  s
 *
 * Example Input/Output:
 * Input:  str = "8613761352066", charsToDelete = "1234567890"
 * Output: ""
 * Explanation: All numeric characters are deleted, resulting in an empty string.
 */

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>

// Simple (Brute-force) Solution
std::string simpleSolution(const std::string& input, const std::string& charsToDelete) {
    std::string result;
    for (char c : input) {
        if (charsToDelete.find(c) == std::string::npos) {
            result.push_back(c);
        }
    }
    return result;
}

// Optimal (Efficient) Solution
std::string optimalSolution(const std::string& input, const std::string& charsToDelete) {
    std::unordered_set<char> deleteSet(charsToDelete.begin(), charsToDelete.end());
    std::string result;
    result.reserve(input.size());  // Reserve memory to reduce reallocations
    for (char c : input) {
        if (deleteSet.find(c) == deleteSet.end()) {
            result.push_back(c);
        }
    }
    return result;
}

// (Optional) Alternative Solution using std::remove_if
std::string alternativeSolution(const std::string& input, const std::string& charsToDelete) {
    std::unordered_set<char> deleteSet(charsToDelete.begin(), charsToDelete.end());
    std::string result = input;
    result.erase(std::remove_if(result.begin(), result.end(), [&deleteSet](char c) {
        return deleteSet.find(c) != deleteSet.end();
    }), result.end());
    return result;
}

// Test cases for correctness
void test() {
    {
        std::string input = "We are students";
        std::string charsToDelete = "aeiou";
        std::string expected = "W r stdnts";
        assert(simpleSolution(input, charsToDelete) == expected);
        assert(optimalSolution(input, charsToDelete) == expected);
        assert(alternativeSolution(input, charsToDelete) == expected);
    }
    {
        std::string input = "We are students";
        std::string charsToDelete = "wxyz";
        std::string expected = "We are students";
        assert(simpleSolution(input, charsToDelete) == expected);
        assert(optimalSolution(input, charsToDelete) == expected);
        assert(alternativeSolution(input, charsToDelete) == expected);
    }
    {
        std::string input = "8613761352066";
        std::string charsToDelete = "1234567890";
        std::string expected = "";
        assert(simpleSolution(input, charsToDelete) == expected);
        assert(optimalSolution(input, charsToDelete) == expected);
        assert(alternativeSolution(input, charsToDelete) == expected);
    }
    {
        std::string input = "119911";
        std::string charsToDelete = "";
        std::string expected = "119911";
        assert(simpleSolution(input, charsToDelete) == expected);
        assert(optimalSolution(input, charsToDelete) == expected);
        assert(alternativeSolution(input, charsToDelete) == expected);
    }
    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
