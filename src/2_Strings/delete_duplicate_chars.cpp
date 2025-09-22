/*
* REMOVE DUPLICATE CHARACTERS FROM STRING
*
* Given a string s, remove all duplicate characters while preserving 
* the order of their first occurrences.
*
* Return the resulting string.
*
* Constraints:
* - 0 <= s.length <= 10^5
* - s may consist of letters, digits, spaces, or special characters.
* - Try to achieve an efficient solution with O(n) time complexity 
*   and minimal extra space.
*
* Example 1:
* Input:  
*   s = "google"
* Output:  
*   "gole"
* Explanation:  
*   The duplicates 'o' and 'g' are removed. Only the first appearance 
*   of each character is kept.
*
* Example 2:
* Input:  
*   s = "abcabc"
* Output:  
*   "abc"
*
* Example 3:
* Input:  
*   s = "aaaa"
* Output:  
*   "a"
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

// Simple (Brute-force) Solution
// Time Complexity: O(n²)
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
// Time Complexity: Average O(n)
std::string optimalSolution(const std::string& input) {
    std::string result;
    result.reserve(input.size());
    std::unordered_set<char> seen;
    for (char c : input) {
        if (seen.insert(c).second) {
            result.push_back(c);
        }
    }
    return result;
}

// (Optional) Alternative Solution using std::remove_if
std::string alternativeSolution(const std::string& input) {
    std::string result = input;
    std::unordered_set<char> seen;
    auto new_end = std::remove_if(result.begin(), result.end(),
        [&seen](char c) {
            if (seen.count(c)) return true;
            seen.insert(c);
            return false;
        });
    result.erase(new_end, result.end());
    return result;
}

struct TestCase {
    std::string name;
    std::string input;
    std::string expected;
};

void testSimple(const std::vector<TestCase>& cases) {
    std::cout << "=== Testing simpleSolution ===\n";
    for (const auto& tc : cases) {
        std::string got = simpleSolution(tc.input);
        bool pass = (got == tc.expected);
        std::cout
            << tc.name
            << ": expected=\"" << tc.expected
            << "\", got=\"" << got
            << "\" -> " << (pass ? "PASS" : "FAIL") << "\n";
        assert(pass);
    }
    std::cout << "\n";
}

void testOptimal(const std::vector<TestCase>& cases) {
    std::cout << "=== Testing optimalSolution ===\n";
    for (const auto& tc : cases) {
        std::string got = optimalSolution(tc.input);
        bool pass = (got == tc.expected);
        std::cout
            << tc.name
            << ": expected=\"" << tc.expected
            << "\", got=\"" << got
            << "\" -> " << (pass ? "PASS" : "FAIL") << "\n";
        assert(pass);
    }
    std::cout << "\n";
}

void testAlternative(const std::vector<TestCase>& cases) {
    std::cout << "=== Testing alternativeSolution ===\n";
    for (const auto& tc : cases) {
        std::string got = alternativeSolution(tc.input);
        bool pass = (got == tc.expected);
        std::cout
            << tc.name
            << ": expected=\"" << tc.expected
            << "\", got=\"" << got
            << "\" -> " << (pass ? "PASS" : "FAIL") << "\n";
        assert(pass);
    }
    std::cout << "\n";
}

int main() {
    std::vector<TestCase> cases = {
        { "Basic repeat",        "google",                     "gole" },
        { "All same",            "aaaaaaaaaaaaaaaaaaaaa",      "a"    },
        { "Empty string",        "",                            ""    },
        { "Mixed repeats",       "abcacbbacbcacabcba",         "abc" }
    };

    testSimple(cases);
    testOptimal(cases);
    testAlternative(cases);

    std::cout << "All tests passed successfully!\n";
    return 0;
}
