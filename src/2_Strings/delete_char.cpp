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
std::string inplaceSolution(std::string input, const std::string& charsToDelete) {
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
    return input;
}

// Tests
void test() {
    {
        std::string input = "We are students";
        std::string charsToDelete = "aeiou";
        std::string expected = "W r stdnts";
        assert(simpleSolution(input, charsToDelete) == expected);
        assert(optimalSolution(input, charsToDelete) == expected);
        assert(alternativeSolution(input, charsToDelete) == expected);
        assert(inplaceSolution(input, charsToDelete) == expected);
    }
    {
        std::string input = "We are students";
        std::string charsToDelete = "wxyz";
        std::string expected = "We are students";
        assert(simpleSolution(input, charsToDelete) == expected);
        assert(optimalSolution(input, charsToDelete) == expected);
        assert(alternativeSolution(input, charsToDelete) == expected);
        assert(inplaceSolution(input, charsToDelete) == expected);
    }
    {
        std::string input = "8613761352066";
        std::string charsToDelete = "1234567890";
        std::string expected = "";
        assert(simpleSolution(input, charsToDelete) == expected);
        assert(optimalSolution(input, charsToDelete) == expected);
        assert(alternativeSolution(input, charsToDelete) == expected);
        assert(inplaceSolution(input, charsToDelete) == expected);
    }
    {
        std::string input = "119911";
        std::string charsToDelete = "";
        std::string expected = "119911";
        assert(simpleSolution(input, charsToDelete) == expected);
        assert(optimalSolution(input, charsToDelete) == expected);
        assert(alternativeSolution(input, charsToDelete) == expected);
        assert(inplaceSolution(input, charsToDelete) == expected);
    }
    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
