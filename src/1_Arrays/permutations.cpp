/*
 * GENERATE PERMUTATIONS FROM VECTOR OF INTEGER SETS
 *
 * Given a vector of integer vectors, generate all unique permutations by choosing
 * exactly one integer from each vector. Each permutation is represented as a set.
 *
 * Constraints:
 * - Each inner vector will contain distinct integers.
 * - The number of inner vectors is at least 1 and at most 10.
 * - Each inner vector has at least 1 integer and at most 10 integers.
 *
 * Input Vectors:
 * [ [1, 2],
 *   [3, 4],
 *   [5, 6] ]
 *
 * Example Permutations:
 * {1, 3, 5}, {1, 3, 6}, {1, 4, 5}, {1, 4, 6},
 * {2, 3, 5}, {2, 3, 6}, {2, 4, 5}, {2, 4, 6}
 *
 * Example Input/Output:
 * Input: [[1,2],[3,4],[5,6]]
 * Output: [{1,3,5},{1,3,6},{1,4,5},{1,4,6},{2,3,5},{2,3,6},{2,4,5},{2,4,6}]
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <string>
#include <vector>

// Simple Recursive Solution
void simpleSolutionHelper(const std::vector<std::vector<int>>& input, size_t idx,
                          std::set<int>& current, std::vector<std::set<int>>& results) {
    if (idx == input.size()) {
        results.push_back(current);
        return;
    }
    for (int num : input[idx]) {
        current.insert(num);
        simpleSolutionHelper(input, idx + 1, current, results);
        current.erase(num);
    }
}

std::vector<std::set<int>> simpleSolution(const std::vector<std::vector<int>>& input) {
    std::vector<std::set<int>> results;
    std::set<int> current;
    simpleSolutionHelper(input, 0, current, results);
    return results;
}

// Optimal Iterative Solution
std::vector<std::set<int>> optimalSolution(const std::vector<std::vector<int>>& input) {
    std::vector<std::set<int>> results = { {} };
    for (const auto& vec : input) {
        std::vector<std::set<int>> newResults;
        for (const auto& existingSet : results) {
            for (int num : vec) {
                auto newSet = existingSet;
                newSet.insert(num);
                newResults.push_back(std::move(newSet));
            }
        }
        results = std::move(newResults);
    }
    return results;
}

// --- Test case struct ---
struct TestCase {
    std::string name;
    std::vector<std::vector<int>> input;
    std::vector<std::set<int>> expected;
};

// --- Test runners ---
void testSimple(const std::vector<TestCase>& cases) {
    std::cout << "=== Testing simpleSolution ===\n";
    for (auto& tc : cases) {
        auto got = simpleSolution(tc.input);
        std::sort(got.begin(), got.end());
        auto expected = tc.expected;
        std::sort(expected.begin(), expected.end());
        bool pass = (got == expected);
        std::cout << tc.name << " -> " << (pass ? "PASS" : "FAIL") << "\n";
        assert(pass);
    }
    std::cout << "\n";
}

void testOptimal(const std::vector<TestCase>& cases) {
    std::cout << "=== Testing optimalSolution ===\n";
    for (auto& tc : cases) {
        auto got = optimalSolution(tc.input);
        std::sort(got.begin(), got.end());
        auto expected = tc.expected;
        std::sort(expected.begin(), expected.end());
        bool pass = (got == expected);
        std::cout << tc.name << " -> " << (pass ? "PASS" : "FAIL") << "\n";
        assert(pass);
    }
    std::cout << "\n";
}

int main() {
    std::vector<TestCase> cases = {
        {
            "3×2×2 grid",
            {{1,2}, {3,4}, {5,6}},
            {{1,3,5}, {1,3,6}, {1,4,5}, {1,4,6},
             {2,3,5}, {2,3,6}, {2,4,5}, {2,4,6}}
        },
        {
            "Single list",
            {{1,2,3}},
            {{1}, {2}, {3}}
        },
        {
            "All singletons",
            {{6}, {7}, {8}, {9}},
            {{6,7,8,9}}
        },
        {
            "Empty input",
            {},
            {{}}
        }
    };

    testSimple(cases);
    testOptimal(cases);

    std::cout << "All tests passed successfully!\n";
    return 0;
}

