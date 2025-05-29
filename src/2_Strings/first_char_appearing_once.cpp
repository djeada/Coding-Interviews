/*
 * FIND FIRST NON-REPEATING CHARACTER
 *
 * This program finds the first non-repeating character in a given string.
 * A non-repeating character is one that appears exactly once in the string.
 * Three approaches are demonstrated:
 *   1. simpleSolution: Brute-force approach with nested loops (O(n²)).
 *   2. optimalSolution: Uses an unordered_map to count frequencies and then finds the first character with a count of one (O(n)).
 *   3. alternativeSolution: Uses a fixed-size array to store first occurrence indices and counts,
 *      then selects the character with the smallest index that occurs exactly once.
 *
 * ASCII Illustration:
 *
 *   Input String:    a   b   a   c   d   c   b
 *                    |   |   |   |   |   |   |
 *                    V   V   V   V   V   V   V
 *   Non-Repeating:   d (first character that appears only once)
 *
 * Example Input/Output:
 * Input:  "ababac"
 * Output: "c"
 * Explanation: Characters 'a' and 'b' repeat, so the first non-repeating character is 'c'.
 */

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

// --- Implementations ---

// Simple (Brute-force) Solution O(n²)
char simpleSolution(const std::string& input) {
    for (size_t i = 0; i < input.size(); ++i) {
        bool repeating = false;
        for (size_t j = 0; j < input.size(); ++j) {
            if (i != j && input[i] == input[j]) {
                repeating = true;
                break;
            }
        }
        if (!repeating) {
            return input[i];
        }
    }
    return '\0';
}

// Optimal (Hash map) Solution O(n)
char optimalSolution(const std::string& input) {
    std::unordered_map<char, int> freq;
    for (char c : input) ++freq[c];
    for (char c : input) {
        if (freq[c] == 1) return c;
    }
    return '\0';
}

// Alternative (Fixed-size array) Solution O(n), O(1) space
char alternativeSolution(const std::string& input) {
    constexpr int ASCII = 256;
    std::array<int, ASCII> firstIdx;
    firstIdx.fill(-1);
    std::array<int, ASCII> count{};
    for (int i = 0; i < (int)input.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(input[i]);
        if (firstIdx[c] == -1) firstIdx[c] = i;
        ++count[c];
    }
    int minPos = std::numeric_limits<int>::max();
    char result = '\0';
    for (int c = 0; c < ASCII; ++c) {
        if (count[c] == 1 && firstIdx[c] < minPos) {
            minPos = firstIdx[c];
            result = static_cast<char>(c);
        }
    }
    return result;
}

// --- Testing Infrastructure ---

struct TestCase {
    std::string name;
    std::string input;
    char expected;
};

void testSimple(const std::vector<TestCase>& cases) {
    std::cout << "=== Testing simpleSolution ===\n";
    for (auto& tc : cases) {
        char got = simpleSolution(tc.input);
        bool pass = (got == tc.expected);
        std::cout << tc.name
                  << ": expected='" << tc.expected
                  << "', got='"   << got
                  << "' -> "      << (pass ? "PASS" : "FAIL") << "\n";
        assert(pass);
    }
    std::cout << "\n";
}

void testOptimal(const std::vector<TestCase>& cases) {
    std::cout << "=== Testing optimalSolution ===\n";
    for (auto& tc : cases) {
        char got = optimalSolution(tc.input);
        bool pass = (got == tc.expected);
        std::cout << tc.name
                  << ": expected='" << tc.expected
                  << "', got='"   << got
                  << "' -> "      << (pass ? "PASS" : "FAIL") << "\n";
        assert(pass);
    }
    std::cout << "\n";
}

void testAlternative(const std::vector<TestCase>& cases) {
    std::cout << "=== Testing alternativeSolution ===\n";
    for (auto& tc : cases) {
        char got = alternativeSolution(tc.input);
        bool pass = (got == tc.expected);
        std::cout << tc.name
                  << ": expected='" << tc.expected
                  << "', got='"   << got
                  << "' -> "      << (pass ? "PASS" : "FAIL") << "\n";
        assert(pass);
    }
    std::cout << "\n";
}

int main() {
    std::vector<TestCase> cases = {
        { "All unique",    "abc",      'a' },
        { "Repeat at end", "ababac",   'c' },
        { "Unique first",  "xyza",     'x' },
        { "Middle unique", "lol",      'o' },
        { "No unique",     "aabbcc",   '\0' }
    };

    testSimple(cases);
    testOptimal(cases);
    testAlternative(cases);

    std::cout << "All tests passed successfully!\n";
    return 0;
}
