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
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

struct TestCase {
    std::string name;
    std::vector<int> arr;
    int expected;
};

// Simple Linear Search Implementation
int findMinLinear(const std::vector<int>& nums) {
    return *std::min_element(nums.begin(), nums.end());
}

// Optimal Binary Search Implementation (O(log n))
int findMinOptimal(const std::vector<int>& nums) {
    int left = 0;
    int right = (int)nums.size() - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] > nums[right]) {
            left = mid + 1;
        } else if (nums[mid] < nums[right]) {
            right = mid;
        } else {
            // nums[mid] == nums[right], safely shrink
            --right;
        }
    }
    return nums[left];
}

void testLinear(const std::vector<TestCase>& cases) {
    std::cout << "=== Testing Linear Search Implementation ===\n";
    for (const auto& tc : cases) {
        int result = findMinLinear(tc.arr);
        bool pass = (result == tc.expected);
        std::cout 
            << tc.name 
            << ": expected=" << tc.expected 
            << ", got=" << result 
            << " -> " << (pass ? "PASS" : "FAIL") 
            << "\n";
        assert(pass);
    }
    std::cout << "\n";
}

void testOptimal(const std::vector<TestCase>& cases) {
    std::cout << "=== Testing Optimal Binary Search Implementation ===\n";
    for (const auto& tc : cases) {
        int result = findMinOptimal(tc.arr);
        bool pass = (result == tc.expected);
        std::cout 
            << tc.name 
            << ": expected=" << tc.expected 
            << ", got=" << result 
            << " -> " << (pass ? "PASS" : "FAIL") 
            << "\n";
        assert(pass);
    }
    std::cout << "\n";
}

int main() {
    std::vector<TestCase> cases = {
        { "Rotated middle",       {3, 4, 5, 1, 2},            1 },
        { "With duplicates",      {10, 10, 2, 5, 5, 9, 9},    2 },
        { "All identical",        {0, 0, 0, 0},               0 },
        { "Negative values",      {-1, -1, 5, -1, -1},       -1 },
        { "No rotation",          {1, 2, 3, 4, 5},            1 },
        { "Pivot at end",         {2, 3, 4, 5, 1},            1 },
        { "Single element",       {42},                       42 }
    };

    testLinear(cases);
    testOptimal(cases);

    std::cout << "All tests passed successfully!\n";
    return 0;
}

