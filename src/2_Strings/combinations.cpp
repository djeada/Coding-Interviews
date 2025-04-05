/*
 * GENERATE ALL STRING COMBINATIONS
 *
 * Given a string, generate all possible combinations (subsequences) of its characters.
 * Combinations must include all subsets of characters from length 1 to N (the string length).
 * Order of combinations does not matter.
 *
 * Constraints:
 * - The input string will consist of unique lowercase letters.
 * - The length of the string will not exceed 20 characters.
 *
 * Visual illustrations:
 *
 * Example: Input: "abc"
 * 
 * Combinations:
 * a, b, c, ab, ac, bc, abc
 *
 * Example Input/Output:
 * Input: "ab"
 * Output: a, b, ab
 */

#include <algorithm>
#include <cassert>
#include <bitset>
#include <iostream>
#include <set>
#include <string>
#include <vector>

// Simple (Recursive) Solution
// Complexity: O(2^n) due to recursive exploration of all subsets.
std::set<std::string> simpleSolution(const std::string &str, int idx = 0, const std::string &curr = "") {
    std::set<std::string> result;
    if (idx == str.length()) {
        if (!curr.empty()) result.insert(curr);
        return result;
    }
    auto without = simpleSolution(str, idx + 1, curr);
    auto with = simpleSolution(str, idx + 1, curr + str[idx]);
    result.merge(without);
    result.merge(with);
    return result;
}

// Optimal (Bitset) Solution
// Complexity: O(2^n * n), more efficient memory usage, practical for larger inputs.
std::set<std::string> optimalSolution(const std::string &str) {
    std::set<std::string> result;
    const size_t len = str.length();
    const size_t total = 1 << len;

    for (size_t mask = 1; mask < total; ++mask) {
        std::string combination;
        for (size_t j = 0; j < len; ++j)
            if (mask & (1 << j))
                combination += str[j];
        result.insert(combination);
    }

    return result;
}

// Alternative Solution (Educational - STL Combination)
// Complexity: Similar O(2^n * n), demonstrates use of std::next_permutation for education.
std::set<std::string> alternativeSolution(std::string str) {
    std::set<std::string> result;
    const size_t len = str.length();
    for (size_t r = 1; r <= len; ++r) {
        std::string bitmask(r, 1); // r ones
        bitmask.resize(len, 0);    // n-r zeros

        do {
            std::string combination;
            for (size_t i = 0; i < len; ++i)
                if (bitmask[i]) combination += str[i];
            result.insert(combination);
        } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
    }

    return result;
}

// Test cases for correctness
void test() {
    std::vector<std::string> testInputs = {"a", "ab", "abc"};

    for (const auto &input : testInputs) {
        auto simple = simpleSolution(input);
        auto optimal = optimalSolution(input);
        auto alternative = alternativeSolution(input);

        assert(simple == optimal);
        assert(optimal == alternative);
    }

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
