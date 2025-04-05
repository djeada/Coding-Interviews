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
#include <vector>

// Simple Recursive Solution
// Easy to understand but can be slower for large inputs.
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
// Avoids recursion overhead, more efficient for larger inputs.
std::vector<std::set<int>> optimalSolution(const std::vector<std::vector<int>>& input) {
    std::vector<std::set<int>> results = { { } };

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

// Test cases for correctness
void test() {
    std::vector<std::vector<int>> input1 = {{1, 2}, {3, 4}, {5, 6}};
    std::vector<std::set<int>> expected1 = {
        {1, 3, 5}, {1, 3, 6}, {1, 4, 5}, {1, 4, 6},
        {2, 3, 5}, {2, 3, 6}, {2, 4, 5}, {2, 4, 6}
    };
    auto res1_simple = simpleSolution(input1);
    auto res1_optimal = optimalSolution(input1);
    std::sort(res1_simple.begin(), res1_simple.end());
    std::sort(res1_optimal.begin(), res1_optimal.end());
    std::sort(expected1.begin(), expected1.end());
    assert(res1_simple == expected1);
    assert(res1_optimal == expected1);

    std::vector<std::vector<int>> input2 = {{1, 2, 3}};
    std::vector<std::set<int>> expected2 = {{1}, {2}, {3}};
    assert(simpleSolution(input2) == expected2);
    assert(optimalSolution(input2) == expected2);

    std::vector<std::vector<int>> input3 = {{6}, {7}, {8}, {9}};
    std::vector<std::set<int>> expected3 = {{6, 7, 8, 9}};
    assert(simpleSolution(input3) == expected3);
    assert(optimalSolution(input3) == expected3);

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
