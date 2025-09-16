/*
 * GENERATE CARTESIAN PRODUCT FROM VECTOR OF INTEGER LISTS
 *
 * Given a vector of integer vectors, generate all ordered tuples by choosing
 * exactly one integer from each inner vector (the Cartesian product).
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
 * Example Tuples (Cartesian product):
 * [1,3,5], [1,3,6], [1,4,5], [1,4,6],
 * [2,3,5], [2,3,6], [2,4,5], [2,4,6]
 *
 * Example Input/Output:
 * Input: [[1,2],[3,4],[5,6]]
 * Output: [[1,3,5],[1,3,6],[1,4,5],[1,4,6],[2,3,5],[2,3,6],[2,4,5],[2,4,6]]
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

// --- Recursive solution ---
void productHelper(const std::vector<std::vector<int>>& input, size_t idx,
                   std::vector<int>& current, std::vector<std::vector<int>>& results) {
    if (idx == input.size()) {
        results.push_back(current);
        return;
    }
    for (int num : input[idx]) {
        current.push_back(num);
        productHelper(input, idx + 1, current, results);
        current.pop_back();
    }
}

std::vector<std::vector<int>> cartesianProductRecursive(const std::vector<std::vector<int>>& input) {
    std::vector<std::vector<int>> results;
    std::vector<int> current;
    current.reserve(input.size());
    productHelper(input, 0, current, results);
    return results;
}

// --- Iterative solution ---
std::vector<std::vector<int>> cartesianProductIterative(const std::vector<std::vector<int>>& input) {
    std::vector<std::vector<int>> results = { {} }; // start with one empty tuple
    for (const auto& vec : input) {
        std::vector<std::vector<int>> newResults;
        newResults.reserve(results.size() * vec.size());
        for (const auto& tuple : results) {
            for (int x : vec) {
                auto t = tuple;
                t.push_back(x);
                newResults.push_back(std::move(t));
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
    std::vector<std::vector<int>> expected;
};

// --- Test runners ---
void testRecursive(const std::vector<TestCase>& cases) {
    std::cout << "=== Testing cartesianProductRecursive ===\n";
    for (auto& tc : cases) {
        auto got = cartesianProductRecursive(tc.input);
        std::sort(got.begin(), got.end());
        auto expected = tc.expected;
        std::sort(expected.begin(), expected.end());
        bool pass = (got == expected);
        std::cout << tc.name << " -> " << (pass ? "PASS" : "FAIL") << "\n";
        assert(pass);
    }
    std::cout << "\n";
}

void testIterative(const std::vector<TestCase>& cases) {
    std::cout << "=== Testing cartesianProductIterative ===\n";
    for (auto& tc : cases) {
        auto got = cartesianProductIterative(tc.input);
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
            {
                {1,3,5}, {1,3,6}, {1,4,5}, {1,4,6},
                {2,3,5}, {2,3,6}, {2,4,5}, {2,4,6}
            }
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
            "Empty input (product of zero lists)",
            {},
            {{}}
        }
    };

    testRecursive(cases);
    testIterative(cases);

    std::cout << "All tests passed successfully!\n";
    return 0;
}
