/*
 * CLIMBING STAIRS WITH VARIABLE STEPS
 *
 * Given an integer N representing a staircase with N steps and an array of allowed steps,
 * determine how many distinct ways you can reach the top. You can take steps according
 * to the values provided in the allowed steps array. Each move can only consist of
 * an allowed number of steps.
 *
 * Constraints:
 * - 1 ≤ N ≤ 1000
 * - allowedSteps contains unique positive integers.
 * - allowedSteps size ≤ 10
 *
 * Visual illustration (Example):
 *
 * N = 4, allowedSteps = [1, 3]
 *
 * Ways to climb:
 * (1, 1, 1, 1)
 * (1, 3)
 * (3, 1)
 *
 * Total ways = 3
 *
 * Example Input/Output:
 * Input: N = 5, allowedSteps = [1, 2]
 * Output: 8
 * Explanation: Ways = [11111, 1112, 1121, 1211, 2111, 122, 212, 221]
 */

#include <algorithm>
#include <cassert>
#include <vector>
#include <iostream>

// Simple (Recursive) Solution
// Complexity: O(N^M) where M is size of allowedSteps
int simpleSolution(int N, const std::vector<int>& allowedSteps) {
    if (N == 0) return 1;
    if (N < 0) return 0;

    int totalWays = 0;
    for (int step : allowedSteps) {
        totalWays += simpleSolution(N - step, allowedSteps);
    }

    return totalWays;
}

// Optimal (Dynamic Programming) Solution
// Complexity: O(N * M)
int optimalSolution(int N, const std::vector<int>& allowedSteps) {
    std::vector<int> dp(N + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= N; ++i) {
        for (int step : allowedSteps) {
            if (i - step >= 0)
                dp[i] += dp[i - step];
        }
    }

    return dp[N];
}

// Test cases for correctness
void test() {
    struct TestCase {
        int N;
        std::vector<int> allowedSteps;
        int expected;
    };

    std::vector<TestCase> tests = {
        {4, {1, 3}, 3},
        {5, {1, 2}, 8},
        {3, {2}, 0},
        {7, {1, 3, 5}, 12},
        {10, {2, 5}, 2}
    };

    for (const auto& test : tests) {
        int simple = simpleSolution(test.N, test.allowedSteps);
        int optimal = optimalSolution(test.N, test.allowedSteps);

        assert(simple == optimal);
        assert(optimal == test.expected);

        std::cout << "Stairs: " << test.N << " | Allowed Steps: ";
        for (int s : test.allowedSteps) std::cout << s << " ";
        std::cout << "| Ways: " << optimal << std::endl;
    }

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    test();
    return 0;
}
