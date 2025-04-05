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

#include <iostream>
#include <string>
#include <regex>
#include <cassert>
#include <cstring>

// Simple (Brute-force) Solution using std::string.
// Iterates over each character and appends "%20" for spaces.
std::string simpleSolution(const std::string &input) {
    std::string result;
    for (char c : input) {
        result += (c == ' ') ? "%20" : std::string(1, c);
    }
    return result;
}

// Optimal (Efficient) Solution: In-place modification of a C-style string.
// Assumes the provided buffer has enough capacity for the extra characters.
void optimalSolution(char str[], int capacity) {
    if (!str || capacity <= 0) return;
    int originalLength = 0, spaceCount = 0;
    while (str[originalLength] != '\0') {
        if (str[originalLength] == ' ') spaceCount++;
        originalLength++;
    }
    int newLength = originalLength + spaceCount * 2;
    if (newLength >= capacity) return;
    str[newLength] = '\0';
    int i = originalLength - 1, j = newLength - 1;
    while (i >= 0) {
        if (str[i] == ' ') {
            str[j--] = '0';
            str[j--] = '2';
            str[j--] = '%';
        } else {
            str[j--] = str[i];
        }
        i--;
    }
}

// Alternative Solution using std::regex.
// Uses regex_replace to substitute each space with "%20".
std::string alternativeSolution(const std::string &input) {
    return std::regex_replace(input, std::regex(" "), "%20");
}

// Test cases for correctness.
void test() {
    // Test simpleSolution and alternativeSolution with std::string.
    {
        std::string input = "hello world";
        std::string expected = "hello%20world";
        assert(simpleSolution(input) == expected);
        assert(alternativeSolution(input) == expected);
    }
    {
        std::string input = "  leading and trailing  ";
        std::string expected = "%20%20leading%20and%20trailing%20%20";
        assert(simpleSolution(input) == expected);
        assert(alternativeSolution(input) == expected);
    }
    
    // Test optimalSolution with in-place modification on a C-style string.
    {
        char buffer[100] = "hello world";
        optimalSolution(buffer, 100);
        assert(std::strcmp(buffer, "hello%20world") == 0);
    }
    {
        char buffer[100] = "  hello  ";
        optimalSolution(buffer, 100);
        assert(std::strcmp(buffer, "%20%20hello%20%20") == 0);
    }
    
    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
