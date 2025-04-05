/*
 * Task: Find the minimum element in a cyclically sorted (rotated) array.
 * 
 * The array was initially sorted in ascending order, then rotated at an unknown pivot.
 * The goal is to efficiently identify the minimum element.
 * 
 * Visual Example:
 * 
 * Original sorted array:
 * [1, 2, 3, 4, 5, 6, 7]
 *
 * Rotated array examples:
 * [4, 5, 6, 7, 1, 2, 3] -> Minimum: 1
 * [6, 7, 1, 2, 3, 4, 5] -> Minimum: 1
 * [1, 2, 3, 4, 5, 6, 7] -> Minimum: 1 (no rotation)
 *
 * Example Input/Output:
 * Input: [5, 6, 1, 2, 3, 4]
 * Output: 1
 *
 * Input: [2, 3, 4, 5, 6, 1]
 * Output: 1
 *
 * Input: [1, 2, 3, 4, 5]
 * Output: 1
 */

#include <algorithm>
#include <cassert>
#include <vector>
#include <iostream>

// Simple Linear Search Implementation
int findMinLinear(const std::vector<int>& nums) {
    return *std::min_element(nums.begin(), nums.end());
}

// Optimal Binary Search Implementation (O(log n))
int findMinOptimal(const std::vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] > nums[right]) {
            left = mid + 1;
        } else if (nums[mid] < nums[right]) {
            right = mid;
        } else {
            // When nums[mid] and nums[right] are equal, ambiguity arises,
            // safely decrement right as nums[right] can't be minimum.
            --right;
        }
    }

    return nums[left];
}

// Simple test cases to verify correctness
void test() {
    std::vector<std::vector<int>> testArrays = {
        {3, 4, 5, 1, 2},
        {10, 10, 2, 5, 5, 9, 9, 9},
        {-1, -1, 5, -1, -1},
        {0, 0, 0, 0, 0, 0},
        {1, 2, 3, 4, 5}, // no rotation
        {2, 3, 4, 5, 1},
        {1} // single element
    };

    for (const auto& arr : testArrays) {
        assert(findMinLinear(arr) == findMinOptimal(arr));
    }

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    test();
    return 0;
}
