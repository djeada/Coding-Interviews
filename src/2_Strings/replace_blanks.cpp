/*
 * REPLACE SPACES IN A STRING
 *
 * This task requires replacing every space in a given string with the sequence "%20".
 * Three solutions are provided:
 *
 * 1. Simple Solution:
 *    - Uses std::string to build a new string by iterating through the input.
 *    - Straightforward implementation with O(n) time complexity.
 *
 * 2. Optimal (Efficient) Solution:
 *    - Performs in-place modification on a C-style string provided there is enough capacity.
 *    - Employs a two-pointer technique to reduce extra memory usage.
 *
 * 3. Alternative Solution:
 *    - Demonstrates modern C++ regex usage to replace spaces.
 *
 * ASCII Illustration:
 *
 *        "hello world"
 *              |
 *    replace ' ' with "%20"
 *              |
 *       "hello%20world"
 *
 * Example Input/Output:
 * Input (as C-style string with capacity): "hello world", capacity: 100
 * Output: "hello%20world"
 *
 * Explanation:
 * Each space is substituted by the characters '%', '2', and '0'. The simple and alternative
 * solutions create a new string, while the optimal solution modifies the input array in-place.
 */

#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

// --- Implementations ---

// Simple (Brute-force) Solution using std::string
std::string simpleSolution(const std::string &input) {
    std::string result;
    for (char c : input) {
        result += (c == ' ') ? "%20" : std::string(1, c);
    }
    return result;
}

// Alternative Solution using std::regex
std::string alternativeSolution(const std::string &input) {
    return std::regex_replace(input, std::regex(" "), "%20");
}

// Optimal (In-place) Solution on C-string buffer
void optimalSolution(char str[], int capacity) {
    if (!str || capacity <= 0) return;
    int origLen = 0, spaces = 0;
    while (str[origLen]) {
        if (str[origLen] == ' ') spaces++;
        origLen++;
    }
    int newLen = origLen + spaces * 2;
    if (newLen >= capacity) return;
    str[newLen] = '\0';
    for (int i = origLen - 1, j = newLen - 1; i >= 0; --i) {
        if (str[i] == ' ') {
            str[j--] = '0';
            str[j--] = '2';
            str[j--] = '%';
        } else {
            str[j--] = str[i];
        }
    }
}

// --- Testing Infrastructure ---

struct StrTestCase {
    std::string name, input, expected;
};

struct CStrTestCase {
    std::string name;
    const char *initial;
    std::string expected;
};

void testSimpleAndAlternative(const std::vector<StrTestCase> &cases) {
    std::cout << "=== Testing simpleSolution & alternativeSolution ===\n";
    for (auto &tc : cases) {
        std::string s1 = simpleSolution(tc.input);
        std::string s2 = alternativeSolution(tc.input);
        bool p1 = (s1 == tc.expected);
        bool p2 = (s2 == tc.expected);
        std::cout 
            << tc.name 
            << ": simple=\""      << s1 
            << "\" alt=\""        << s2 
            << "\" expected=\""  << tc.expected 
            << "\" -> simple "   << (p1 ? "PASS" : "FAIL")
            << ", alternative "  << (p2 ? "PASS" : "FAIL")
            << "\n";
        assert(p1 && p2);
    }
    std::cout << "\n";
}

void testOptimal(const std::vector<CStrTestCase> &cases) {
    std::cout << "=== Testing optimalSolution (in-place) ===\n";
    for (auto &tc : cases) {
        char buffer[100];
        std::strncpy(buffer, tc.initial, sizeof(buffer));
        buffer[sizeof(buffer)-1] = '\0';
        optimalSolution(buffer, sizeof(buffer));
        bool pass = (std::string(buffer) == tc.expected);
        std::cout
            << tc.name
            << ": got=\"" << buffer 
            << "\" expected=\"" << tc.expected 
            << "\" -> " << (pass ? "PASS" : "FAIL")
            << "\n";
        assert(pass);
    }
    std::cout << "\n";
}

int main() {
    std::vector<StrTestCase> stringCases = {
        { "Single space",     "hello world",                "hello%20world" },
        { "Leading/trailing", "  lead and trail  ",        "%20%20lead%20and%20trail%20%20" },
        { "No spaces",        "nospace",                    "nospace" },
        { "All spaces",       "   ",                        "%20%20%20" }
    };

    std::vector<CStrTestCase> cstrCases = {
        { "In-place single",     "hello world",           "hello%20world" },
        { "In-place leading",    "  hello  ",             "%20%20hello%20%20" },
        { "In-place no spaces",  "nospace",               "nospace" },
        { "In-place all spaces", "   ",                   "%20%20%20" }
    };

    testSimpleAndAlternative(stringCases);
    testOptimal(cstrCases);

    std::cout << "All tests passed successfully!\n";
    return 0;
}

