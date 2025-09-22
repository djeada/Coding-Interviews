/*
* DELETE SPECIFIED CHARACTERS FROM STRING
*
* Given a string `s` and another string `charsToDelete`, 
* remove all characters from `s` that are present in `charsToDelete`.
* Return the resulting string.
*
* Constraints:
* - The input string may include letters, digits, spaces, or special characters.
* - The charsToDelete string may contain one or more characters.
* - Aim for an efficient solution without relying solely on built-in replace functions.
* - Try to achieve the result in-place, minimizing extra memory usage.
*
* ASCII Illustration:
*
*   Input String:           W  e     a  r  e     s  t  u  d  e  n  t  s
*   Characters to Delete:      a     e     i     o     u
*                              ↓     ↓     ↓     ↓     ↓
*   Resulting String:        W     r     s  t  d  n  t  s
*
* Example Input/Output:
*
* Input:  
*   str = "8613761352066"
*   charsToDelete = "1234567890"
*
* Output:  
*   ""
*
* Explanation:  
*   All numeric characters are deleted, resulting in an empty string.
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

// Helper to check and report results
bool checkResult(const std::string& got, const std::string& expected,
                 const std::string& funcName, const TestCase& tc) {
    if (got != expected) {
        std::cerr << "[FAIL] " << funcName << "\n"
                  << "  Input: \"" << tc.input << "\"\n"
                  << "  CharsToDelete: \"" << tc.charsToDelete << "\"\n"
                  << "  Expected: \"" << expected << "\"\n"
                  << "  Got:      \"" << got << "\"\n\n";
        return false;
    }
    return true;
}

void runTests() {
    std::vector<TestCase> cases = {
        {"We are students", "aeiou", "W r stdnts"},
        {"We are students", "wxyz",  "We are students"},
        {"8613761352066",   "1234567890", ""},
        {"119911",          "", "119911"}
    };

    int total = 0, passed = 0;

    for (const auto& tc : cases) {
        // Test return-by-value solutions
        total++;
        if (checkResult(simpleSolution(tc.input, tc.charsToDelete), tc.expected, "simpleSolution", tc)) passed++;

        total++;
        if (checkResult(optimalSolution(tc.input, tc.charsToDelete), tc.expected, "optimalSolution", tc)) passed++;

        total++;
        if (checkResult(alternativeSolution(tc.input, tc.charsToDelete), tc.expected, "alternativeSolution", tc)) passed++;

        // Test in-place solution
        std::string inplaceInput = tc.input;
        inplaceSolution(inplaceInput, tc.charsToDelete);
        total++;
        if (checkResult(inplaceInput, tc.expected, "inplaceSolution", tc)) passed++;
    }

    std::cout << passed << " / " << total << " tests passed.\n";
    if (passed == total) {
        std::cout << "✅ All tests passed!\n";
    } else {
        std::cout << "❌ Some tests failed.\n";
    }
}

int main() {
    runTests();
    return 0;
}
