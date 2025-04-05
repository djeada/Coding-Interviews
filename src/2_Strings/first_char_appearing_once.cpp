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

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <array>
#include <limits>

// Simple (Brute-force) Solution
// Time Complexity: O(n²)
char simpleSolution(const std::string& input) {
    for (size_t i = 0; i < input.size(); ++i) {
        bool isRepeating = false;
        for (size_t j = 0; j < input.size(); ++j) {
            if (i != j && input[i] == input[j]) {
                isRepeating = true;
                break;
            }
        }
        if (!isRepeating) {
            return input[i];
        }
    }
    return '\0';  // Return null character if no non-repeating character exists
}

// Optimal (Efficient) Solution using unordered_map
// Time Complexity: O(n)
char optimalSolution(const std::string& input) {
    std::unordered_map<char, int> freq;
    for (char c : input) {
        ++freq[c];
    }
    for (char c : input) {
        if (freq[c] == 1) {
            return c;
        }
    }
    return '\0';
}

// Alternative Solution using a fixed-size array for counting and first occurrence tracking
// Time Complexity: O(n) with O(1) space since the array size is fixed (256 characters)
char alternativeSolution(const std::string& input) {
    constexpr int ASCII_SIZE = 256;
    std::array<int, ASCII_SIZE> firstIndex;
    firstIndex.fill(-1);
    std::array<int, ASCII_SIZE> count{};
    
    for (size_t i = 0; i < input.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(input[i]);
        if (firstIndex[c] == -1)
            firstIndex[c] = i;
        ++count[c];
    }
    
    int minIndex = std::numeric_limits<int>::max();
    char result = '\0';
    for (int i = 0; i < ASCII_SIZE; ++i) {
        if (count[i] == 1 && firstIndex[i] < minIndex) {
            minIndex = firstIndex[i];
            result = static_cast<char>(i);
        }
    }
    return result;
}

// Test cases for correctness
void test() {
    {
        std::string input = "abc";
        char expected = 'a';
        assert(simpleSolution(input) == expected);
        assert(optimalSolution(input) == expected);
        assert(alternativeSolution(input) == expected);
    }
    {
        std::string input = "ababac";
        char expected = 'c';
        assert(simpleSolution(input) == expected);
        assert(optimalSolution(input) == expected);
        assert(alternativeSolution(input) == expected);
    }
    {
        std::string input = "xyza";
        char expected = 'x';
        assert(simpleSolution(input) == expected);
        assert(optimalSolution(input) == expected);
        assert(alternativeSolution(input) == expected);
    }
    {
        std::string input = "lol";
        char expected = 'o';
        assert(simpleSolution(input) == expected);
        assert(optimalSolution(input) == expected);
        assert(alternativeSolution(input) == expected);
    }
    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
