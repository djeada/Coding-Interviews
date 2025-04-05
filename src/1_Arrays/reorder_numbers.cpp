/*
 * REORDER ARRAY BY ODD AND EVEN NUMBERS
 *
 * Given an integer vector, reorder it so that all odd numbers precede all even numbers.
 * The relative ordering within the odd or even groups doesn't need to be preserved.
 *
 * Constraints:
 * - The input vector length is between 0 and 10^6.
 * - Elements in the vector are integers between INT_MIN and INT_MAX.
 *
 * Example Input/Output:
 * Input: [1, 2, 3, 4, 5, 6, 7]
 * Possible Output: [1, 7, 3, 5, 4, 6, 2]
 * Explanation: All odd numbers (1,3,5,7) appear before even numbers (2,4,6).
 */

#include <algorithm>
#include <cassert>
#include <vector>
#include <iostream>

// Helper function to determine if a number is even
bool isEven(int num) {
    return (num & 1) == 0;
}

// Simple Solution
// Uses extra space for clarity, complexity O(n)
std::vector<int> simpleSolution(const std::vector<int>& arr) {
    std::vector<int> odds, evens;
    for (int num : arr) {
        if (isEven(num)) evens.push_back(num);
        else odds.push_back(num);
    }
    odds.insert(odds.end(), evens.begin(), evens.end());
    return odds;
}

// Optimal Solution
// In-place partitioning, complexity O(n)
std::vector<int> optimalSolution(std::vector<int> arr) {
    std::partition(arr.begin(), arr.end(), [](int num) { return !isEven(num); });
    return arr;
}

// Test cases for correctness
void test() {
    std::vector<int> arr1 = {1, 2, 3, 4, 5, 6, 7};
    auto result1 = optimalSolution(arr1);
    assert(std::is_partitioned(result1.begin(), result1.end(), [](int num) { return !isEven(num); }));

    std::vector<int> arr2 = {1, 3, 5, 7, 2, 4, 6};
    auto result2 = optimalSolution(arr2);
    assert(std::is_partitioned(result2.begin(), result2.end(), [](int num) { return !isEven(num); }));

    std::vector<int> arr3 = {};
    auto result3 = optimalSolution(arr3);
    assert(result3.empty());

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
