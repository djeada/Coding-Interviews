/*
 * GENERATING ALL PERMUTATIONS OF A STRING
 *
 * Given an input string, generate all possible permutations of the characters.
 * Permutations are unique arrangements where the order of characters matters.
 *
 * Constraints:
 * - The input string may contain duplicate characters.
 * - Input length is reasonable (typically less than 10 characters) to avoid combinational explosion.
 *
 * Example:
 * Input: "abc"
 * Output: ["abc", "acb", "bac", "bca", "cab", "cba"]
 * Explanation: All unique orders of characters are returned.
 *
 * ASCII illustration for clarity:
 * Input: "ab"
 *
 *      a                b
 *      |                |
 *      b                a
 *     "ab"             "ba"
 */

#include <algorithm>
#include <cassert>
#include <vector>
#include <string>
#include <set>
#include <iostream>

// Simple (Brute-force) Solution
// Uses recursion, does not handle duplicates efficiently.
// Complexity: O(n * n!), due to recursion and copying.
void permuteSimple(std::string s, int l, int r, std::set<std::string>& results) {
    if (l == r) {
        results.insert(s);
        return;
    }
    for (int i = l; i <= r; ++i) {
        std::swap(s[l], s[i]);
        permuteSimple(s, l + 1, r, results);
        std::swap(s[l], s[i]);
    }
}

std::vector<std::string> simpleSolution(const std::string& input) {
    std::set<std::string> resultSet;
    permuteSimple(input, 0, input.size() - 1, resultSet);
    return {resultSet.begin(), resultSet.end()};
}

// Optimal (Efficient) Solution
// Uses built-in next_permutation algorithm after sorting.
// Complexity: O(n * n!), optimal for generating permutations.
std::vector<std::string> optimalSolution(const std::string& input) {
    std::vector<std::string> results;
    std::string sortedInput = input;
    std::sort(sortedInput.begin(), sortedInput.end());
    do {
        results.push_back(sortedInput);
    } while (std::next_permutation(sortedInput.begin(), sortedInput.end()));

    return results;
}

// Alternative Solution (Educational)
// Iterative permutation generation.
// Complexity: O(n * n!), educational to understand iterative vs recursive.
std::vector<std::string> alternativeSolution(const std::string& input) {
    if (input.empty()) return {};
    
    std::vector<std::string> results = {std::string(1, input[0])};

    for (size_t i = 1; i < input.size(); ++i) {
        std::vector<std::string> newPerms;
        for (const auto& str : results) {
            for (size_t pos = 0; pos <= str.size(); ++pos) {
                newPerms.push_back(str.substr(0, pos) + input[i] + str.substr(pos));
            }
        }
        results = std::move(newPerms);
    }

    // Remove duplicates (if any)
    std::set<std::string> unique(results.begin(), results.end());
    return {unique.begin(), unique.end()};
}

// Test cases for correctness
void test() {
    std::vector<std::string> testInputs = {"abc", "aab", ""};

    for (const auto& input : testInputs) {
        auto simpleRes = simpleSolution(input);
        auto optimalRes = optimalSolution(input);
        auto altRes = alternativeSolution(input);

        std::sort(simpleRes.begin(), simpleRes.end());
        std::sort(optimalRes.begin(), optimalRes.end());
        std::sort(altRes.begin(), altRes.end());

        assert(simpleRes == optimalRes && optimalRes == altRes);
    }

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
