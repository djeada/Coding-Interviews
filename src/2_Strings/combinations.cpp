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
#include <iostream>
#include <set>
#include <string>
#include <vector>

// Simple (Recursive) Solution
std::set<std::string> simpleSolutionHelper(const std::string &str, int idx, const std::string &curr) {
    std::set<std::string> result;
    if (idx == (int)str.size()) {
        if (!curr.empty()) result.insert(curr);
        return result;
    }
    // Exclude current character
    auto without = simpleSolutionHelper(str, idx + 1, curr);
    // Include current character
    auto with = simpleSolutionHelper(str, idx + 1, curr + str[idx]);
    result.merge(without);
    result.merge(with);
    return result;
}

std::set<std::string> simpleSolution(const std::string &str) {
    return simpleSolutionHelper(str, 0, "");
}

// Optimal (Bitmask) Solution
std::set<std::string> optimalSolution(const std::string &str) {
    std::set<std::string> result;
    int n = (int)str.size();
    int total = 1 << n;
    for (int mask = 1; mask < total; ++mask) {
        std::string comb;
        for (int j = 0; j < n; ++j) {
            if (mask & (1 << j)) comb += str[j];
        }
        result.insert(comb);
    }
    return result;
}

// Alternative (STL Combinations) Solution
std::set<std::string> alternativeSolution(std::string str) {
    std::set<std::string> result;
    int n = (int)str.size();
    for (int r = 1; r <= n; ++r) {
        std::string bitmask(r, '1');
        bitmask.resize(n, '0');
        do {
            std::string comb;
            for (int i = 0; i < n; ++i) {
                if (bitmask[i] == '1') comb += str[i];
            }
            result.insert(comb);
        } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
    }
    return result;
}

struct TestCase {
    std::string name;
    std::string input;
    std::set<std::string> expected;
};

void testSimple(const std::vector<TestCase>& cases) {
    std::cout << "=== Testing simpleSolution ===\n";
    for (auto& tc : cases) {
        auto got = simpleSolution(tc.input);
        bool pass = (got == tc.expected);
        std::cout << tc.name << " -> " << (pass ? "PASS" : "FAIL") << "\n";
        assert(pass);
    }
    std::cout << "\n";
}

void testOptimal(const std::vector<TestCase>& cases) {
    std::cout << "=== Testing optimalSolution ===\n";
    for (auto& tc : cases) {
        auto got = optimalSolution(tc.input);
        bool pass = (got == tc.expected);
        std::cout << tc.name << " -> " << (pass ? "PASS" : "FAIL") << "\n";
        assert(pass);
    }
    std::cout << "\n";
}

void testAlternative(const std::vector<TestCase>& cases) {
    std::cout << "=== Testing alternativeSolution ===\n";
    for (auto& tc : cases) {
        auto got = alternativeSolution(tc.input);
        bool pass = (got == tc.expected);
        std::cout << tc.name << " -> " << (pass ? "PASS" : "FAIL") << "\n";
        assert(pass);
    }
    std::cout << "\n";
}

int main() {
    std::vector<TestCase> cases = {
        {
            "Single char",
            "a",
            {"a"}
        },
        {
            "Two chars",
            "ab",
            {"a","b","ab"}
        },
        {
            "Three chars",
            "abc",
            {"a","b","c","ab","ac","bc","abc"}
        }
    };

    testSimple(cases);
    testOptimal(cases);
    testAlternative(cases);

    std::cout << "All tests passed successfully!\n";
    return 0;
}
