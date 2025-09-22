/*
* DELETE SPECIFIED CHARACTERS FROM STRING
*
* Write a program that deletes specified characters 
* from a given string.
*
* Constraints:
* - The input string may include letters, digits, spaces, or special characters.
* - The charsToDelete string may contain one or more characters.
* - Aim for an efficient solution without relying solely on built-in replace functions.
* - Try to achieve the result in-place, minimizing extra memory usage.
*/

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <bitset>
#include <vector>

// Simple (Brute-force) Solution | Time: O(n*m), Space: O(1)
std::string simpleSolution(const std::string& input, const std::string& charsToDelete) {
    std::string result;
    for (char c : input) {
        if (charsToDelete.find(c) == std::string::npos) {
            result.push_back(c);
        }
    }
    return result;
}

// Optimal Solution (unordered_set) | Time: O(n+m), Space: O(m)
std::string optimalSolution(const std::string& input, const std::string& charsToDelete) {
    std::unordered_set<char> deleteSet(charsToDelete.begin(), charsToDelete.end());
    std::string result;
    result.reserve(input.size());
    for (char c : input) {
        if (deleteSet.find(c) == deleteSet.end()) {
            result.push_back(c);
        }
    }
    return result;
}

// Alternative Solution (remove_if) | Time: O(n+m), Space: O(n)
std::string alternativeSolution(const std::string& input, const std::string& charsToDelete) {
    std::unordered_set<char> deleteSet(charsToDelete.begin(), charsToDelete.end());
    std::string result = input;
    result.erase(std::remove_if(result.begin(), result.end(), [&deleteSet](char c) {
        return deleteSet.find(c) != deleteSet.end();
    }), result.end());
    return result;
}

// In-place Solution (bitset lookup) | Time: O(n+m), Space: O(1)
void inplaceSolution(std::string& input, const std::string& charsToDelete) {
    std::bitset<256> deleteTable;
    for (unsigned char c : charsToDelete) {
        deleteTable.set(c);
    }
    auto write = input.begin();
    for (char c : input) {
        if (!deleteTable.test((unsigned char)c)) {
            *write++ = c;
        }
    }
    input.erase(write, input.end());
}

// Tests
struct TestCase {
    std::string input;
    std::string charsToDelete;
    std::string expected;
};

void runTests() {
    std::vector<TestCase> cases = {
        {"We are students", "aeiou", "W r stdnts"},
        {"We are students", "wxyz",  "We are students"},
        {"8613761352066",   "1234567890", ""},
        {"119911",          "", "119911"}
    };

    for (const auto& tc : cases) {
        // Test return-by-value solutions
        assert(simpleSolution(tc.input, tc.charsToDelete) == tc.expected);
        assert(optimalSolution(tc.input, tc.charsToDelete) == tc.expected);
        assert(alternativeSolution(tc.input, tc.charsToDelete) == tc.expected);

        // Test in-place solution
        std::string inplaceInput = tc.input;
        inplaceSolution(inplaceInput, tc.charsToDelete);
        assert(inplaceInput == tc.expected);
    }

    std::cout << "All tests passed!\n";
}

int main() {
    runTests();
    return 0;
}
