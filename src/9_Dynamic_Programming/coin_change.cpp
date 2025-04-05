/*
 * MINIMUM COIN CHANGE PROBLEM
 *
 * Given a set of coin denominations and a target amount, determine the minimum number
 * of coins required to reach exactly that amount. If it's impossible, indicate appropriately.
 *
 * Constraints:
 * - Coin denominations are positive integers and unique.
 * - Target amount is a non-negative integer.
 * - If the amount cannot be formed, return INT_MAX.
 *
 * Visual illustration (example):
 * Coin denominations = [1, 3, 4]
 * Target amount = 6
 *
 * Possible combinations:
 * 6 = 3 + 3 (2 coins)
 * 6 = 4 + 1 + 1 (3 coins)
 * 6 = 1 + 1 + 1 + 1 + 1 + 1 (6 coins)
 *
 * Optimal solution picks 3 + 3 = 2 coins.
 *
 * Example Input/Output:
 * Input: coins = [1, 3, 4], target = 6
 * Output: 2
 * Explanation: The minimal combination is [3, 3].
 */

#include <algorithm>
#include <cassert>
#include <climits>
#include <vector>
#include <iostream>

// Simple (Brute-force) Recursive Solution
// Exponential complexity: O(n^targetAmount)
int simpleSolution(const std::vector<int>& coins, int targetAmount) {
    if (targetAmount == 0) return 0;
    if (targetAmount < 0) return INT_MAX;

    int minCoins = INT_MAX;
    for (int coin : coins) {
        int res = simpleSolution(coins, targetAmount - coin);
        if (res != INT_MAX)
            minCoins = std::min(minCoins, res + 1);
    }
    return minCoins;
}

// Optimal (Efficient) Solution using Dynamic Programming
// Complexity: O(n * targetAmount)
int optimalSolution(const std::vector<int>& coins, int targetAmount) {
    std::vector<int> dp(targetAmount + 1, INT_MAX);
    dp[0] = 0;  // 0 coins needed to make amount 0

    for (int amt = 1; amt <= targetAmount; ++amt) {
        for (int coin : coins) {
            if (amt - coin >= 0 && dp[amt - coin] != INT_MAX)
                dp[amt] = std::min(dp[amt], dp[amt - coin] + 1);
        }
    }

    return dp[targetAmount];
}

// Alternative (Greedy) Solution
// Educational: Shows greedy method limitations (not always optimal)
int greedySolution(std::vector<int> coins, int targetAmount) {
    std::sort(coins.rbegin(), coins.rend()); // Sort descending for greedy approach
    int count = 0;
    for (int coin : coins) {
        count += targetAmount / coin;
        targetAmount %= coin;
    }
    return targetAmount == 0 ? count : INT_MAX;
}

// Test cases for correctness and comparison
void test() {
    struct TestCase {
        std::vector<int> coins;
        int target;
        int expected;
    };

    std::vector<TestCase> tests = {
        {{1, 3, 4}, 6, 2},        // optimal: [3,3]
        {{1, 5, 10, 25}, 30, 2},  // optimal: [5,25]
        {{2, 4, 8}, 7, INT_MAX},  // impossible case
        {{1, 2, 5}, 11, 3},       // optimal: [5,5,1]
        {{1}, 100, 100},          // single denomination
    };

    for (const auto& test : tests) {
        int simple = simpleSolution(test.coins, test.target);
        int optimal = optimalSolution(test.coins, test.target);
        int greedy = greedySolution(test.coins, test.target);

        assert(simple == optimal);
        std::cout << "Coins: ";
        for (int c : test.coins) std::cout << c << " ";
        std::cout << "| Target: " << test.target << " | Min coins: " << optimal;
        if (greedy != optimal)
            std::cout << " (Greedy: " << (greedy == INT_MAX ? "impossible" : std::to_string(greedy)) << ")";
        std::cout << std::endl;
    }

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    test();
    return 0;
}
