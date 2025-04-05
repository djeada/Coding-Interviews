/*
 * MAXIMUM SUBARRAY PROBLEM
 *
 * This task is to find the contiguous subarray within a one-dimensional array of
 * numbers that has the largest sum.
 *
 * We provide two implementations:
 *  1. Naive Approach (Easy to implement) that computes the sum of every possible
 *     contiguous subarray. It has a quadratic time complexity: O(n^2).
 *  2. Optimal Approach using Kadane's algorithm, which computes the result in
 *     linear time: O(n).
 *
 * Edge Cases:
 *  - Arrays with all negative numbers (should return the maximum single element).
 *  - Arrays with a single element.
 *
 * Visual Illustration:
 *  Given the array:
 *     [ 1, -2, 3, 10, -4, 7, 2, -5 ]
 *
 *  The contiguous subarray with the maximum sum is:
 *     [ 3, 10, -4, 7, 2 ]
 *
 * Example Input/Output:
 *  Input:  [ 1, -2, 3, 10, -4, 7, 2, -5 ]
 *  Output: 18
 *  Explanation: The sum of the subarray [ 3, 10, -4, 7, 2 ] equals 18, which is
 *               the maximum achievable sum among all contiguous subarrays.
 */

#include <cassert>
#include <climits>
#include <vector>
#include <algorithm>

// Naive approach: Checks all possible contiguous subarrays (O(n^2) time complexity)
int findMaxSubarraySumNaive(const std::vector<int>& numbers) {
    int maxSum = INT_MIN;
    const int n = numbers.size();
    for (int i = 0; i < n; ++i) {
        int currentSum = 0;
        for (int j = i; j < n; ++j) {
            currentSum += numbers[j];
            maxSum = std::max(maxSum, currentSum);
        }
    }
    return maxSum;
}

// Optimal approach using Kadane's algorithm (O(n) time complexity)
int findMaxSubarraySumKadane(const std::vector<int>& numbers) {
    int currentSum = 0;
    int maxSum = INT_MIN;
    for (const auto& num : numbers) {
        currentSum = std::max(num, currentSum + num);
        maxSum = std::max(maxSum, currentSum);
    }
    return maxSum;
}

void testMaxSubarraySum() {
    std::vector<int> testArray1 {1, -2, 3, 10, -4, 7, 2, -5};
    int expected1 = 18;
    assert(findMaxSubarraySumNaive(testArray1) == expected1);
    assert(findMaxSubarraySumKadane(testArray1) == expected1);

    std::vector<int> testArray2 {-2, -8, -1, -5, -9};
    int expected2 = -1;
    assert(findMaxSubarraySumNaive(testArray2) == expected2);
    assert(findMaxSubarraySumKadane(testArray2) == expected2);

    std::vector<int> testArray3 {2, 8, 1, 5, 9};
    int expected3 = 25;
    assert(findMaxSubarraySumNaive(testArray3) == expected3);
    assert(findMaxSubarraySumKadane(testArray3) == expected3);

    std::vector<int> testArray4 {2};
    int expected4 = 2;
    assert(findMaxSubarraySumNaive(testArray4) == expected4);
    assert(findMaxSubarraySumKadane(testArray4) == expected4);
}

int main() {
    testMaxSubarraySum();
    return 0;
}
