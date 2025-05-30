/*
 * REVERSE WORDS IN A STRING
 *
 * This program reverses the order of words in a given string.
 * Three solutions are provided:
 *
 * 1. Simple Solution:
 *    - Uses std::istringstream to split the input into words,
 *      reverses the vector of words, and then joins them back together.
 *    - Straightforward and highly readable, with O(n) time complexity,
 *      but uses extra memory for the words.
 *
 * 2. Optimal (Efficient) Solution:
 *    - Performs the reversal in-place on a mutable copy of the input string.
 *    - First, it reverses each word individually, and then reverses the entire string.
 *    - This solution minimizes extra memory usage and also runs in O(n) time.
 *
 * 3. Alternative Solution:
 *    - Uses modern C++ iterators and the standard library to achieve the reversal.
 *    - Splits the string with std::istream_iterator and then uses reverse iterators
 *      to build the final result.
 *
 * ASCII Illustration:
 *
 *     Input: "hello world"
 *          +----------------+
 *          |hello world     |
 *          +----------------+
 *                 |
 *        (reverse words order)
 *                 V
 *          +----------------+
 *          |world hello     |
 *          +----------------+
 *
 * Example Input/Output:
 * Input: "hello world"
 * Output: "world hello"
 *
 * Explanation:
 * The order of words is inverted so that the first word becomes the last.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

// Simple (Brute-force) Solution using string splitting.
std::string simpleSolution(const std::string &input) {
    std::istringstream iss(input);
    std::vector<std::string> words;
    std::string word;
    while (iss >> word) {
        words.push_back(word);
    }
    std::reverse(words.begin(), words.end());
    std::ostringstream oss;
    for (size_t i = 0; i < words.size(); ++i) {
        if (i > 0) oss << ' ';
        oss << words[i];
    }
    return oss.str();
}

// Optimal (Efficient) Solution: In-place reversal via two-step reverse.
void reverseSubstring(std::string &str, int left, int right) {
    while (left < right) {
        std::swap(str[left++], str[right--]);
    }
}

std::string trimSpaces(const std::string &input) {
    std::string s = input;
    int n = s.size();
    int i = 0, j = 0;
    // Skip leading spaces
    while (i < n && s[i] == ' ') i++;
    // Copy characters, collapsing spaces
    for (; i < n; ++i) {
        if (s[i] == ' ' && (j == 0 || s[j-1] == ' ')) continue;
        s[j++] = s[i];
    }
    // Remove trailing space if any
    if (j > 0 && s[j-1] == ' ') j--;
    return s.substr(0, j);
}

std::string optimalSolution(const std::string &input) {
    // First, normalize spaces
    std::string str = trimSpaces(input);
    int n = (int)str.size();
    int start = 0;

    // Reverse each word in-place
    for (int i = 0; i <= n; ++i) {
        if (i == n || str[i] == ' ') {
            reverseSubstring(str, start, i - 1);
            start = i + 1;
        }
    }
    // Reverse the whole string
    reverseSubstring(str, 0, n - 1);
    return str;
}

// Alternative using C++ iterators to split and then reverse iterate.
std::string alternativeSolution(const std::string &input) {
    std::istringstream iss(input);
    std::vector<std::string> words{
        std::istream_iterator<std::string>(iss),
        std::istream_iterator<std::string>()
    };
    std::ostringstream oss;
    for (auto it = words.rbegin(); it != words.rend(); ++it) {
        if (it != words.rbegin()) oss << ' ';
        oss << *it;
    }
    return oss.str();
}

// --- Test case struct ---
struct TestCase {
    std::string name;
    std::string input;
    std::string expected;
};

// --- Test runners ---
void testSimple(const std::vector<TestCase>& cases) {
    std::cout << "=== Testing simpleSolution ===\n";
    for (auto& tc : cases) {
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
    for (auto& tc : cases) {
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
    for (auto& tc : cases) {
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
        { "Two words",                "hello world",                "world hello" },
        { "Single word",              "adam",                       "adam" },
        { "Multiple words",           "the quick brown fox",        "fox brown quick the" },
        { "C++ phrase",               "C++ is modern",              "modern is C++" },
        { "Leading/trailing spaces",  "  trim this  ",              "this trim" },
        { "Repeated spaces",          "a  lot   of    spaces",      "spaces of lot a" }
    };

    testSimple(cases);
    testOptimal(cases);
    testAlternative(cases);

    std::cout << "All tests passed successfully!\n";
    return 0;
}

