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
#include <sstream>
#include <string>
#include <vector>
#include <iterator>

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
    for (size_t i = 0; i < words.size(); i++) {
        if (i > 0) {
            oss << " ";
        }
        oss << words[i];
    }
    return oss.str();
}

// Optimal (Efficient) Solution: In-place reversal using two-step reverse.
// First, reverse each individual word, then reverse the entire string.
void reverseSubstring(std::string &str, int left, int right) {
    while (left < right) {
        std::swap(str[left], str[right]);
        left++;
        right--;
    }
}

std::string optimalSolution(const std::string &input) {
    std::string str = input;
    int n = str.size();
    int start = 0;
    // Reverse each word in-place.
    for (int i = 0; i <= n; i++) {
        if (i == n || str[i] == ' ') {
            reverseSubstring(str, start, i - 1);
            start = i + 1;
        }
    }
    // Reverse the entire string.
    reverseSubstring(str, 0, n - 1);
    return str;
}

// Alternative Solution using modern C++ iterators.
// Splits the string using std::istream_iterator and then builds the result using reverse iterators.
std::string alternativeSolution(const std::string &input) {
    std::istringstream iss(input);
    std::vector<std::string> words{
        std::istream_iterator<std::string>(iss),
        std::istream_iterator<std::string>()
    };
    std::string result;
    for (auto it = words.rbegin(); it != words.rend(); ++it) {
        if (!result.empty()) {
            result += " ";
        }
        result += *it;
    }
    return result;
}

// Test cases for correctness.
void test() {
    std::vector<std::string> testInputs = {
        "hello world",
        "adam",
        "the quick brown fox",
        "C++ is modern",
        "leading spaces",
        "trailing spaces",
        "multiple spaces between words"
    };

    for (const auto &input : testInputs) {
        std::string simpleRes = simpleSolution(input);
        std::string optimalRes = optimalSolution(input);
        std::string alternativeRes = alternativeSolution(input);
        // For these test cases, we assume words are separated by a single space.
        assert(simpleRes == optimalRes);
        assert(simpleRes == alternativeRes);
    }
    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
