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

// 1) Linear by hand
int findMinLinearManual(const std::vector<int>& nums) {
    assert(!nums.empty());
    int m = nums.front();
    for (const auto& n : nums) {
        if (n < m) m = n;
    }
    return m;
}

// 2) Linear via library
int findMinLinearLib(const std::vector<int>& nums) {
    assert(!nums.empty());
    return *std::min_element(nums.begin(), nums.end());
}

// 3) Binary by hand (handles duplicates)
int findMinBinaryManual(const std::vector<int>& nums) {
    assert(!nums.empty());
    int left = 0, right = (int)nums.size() - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] > nums[right]) {
            left = mid + 1;
        } else if (nums[mid] < nums[right]) {
            right = mid;
        } else {
            // nums[mid] == nums[right]; shrink safely
            --right;
        }
    }
    return nums[left];
}

template <typename F>
void runTests(const std::string& title, F algo, const std::vector<TestCase>& cases) {
    std::cout << "=== " << title << " ===\n";
    for (const auto& tc : cases) {
        int result = algo(tc.arr);
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
        { "Rotated middle",            {3, 4, 5, 1, 2},            1 },
        { "With duplicates",           {10, 10, 2, 5, 5, 9, 9},    2 },
        { "All identical",             {0, 0, 0, 0},               0 },
        { "Negative values",           {-1, -1, 5, -1, -1},       -1 },
        { "No rotation",               {1, 2, 3, 4, 5},            1 },
        { "Pivot at end",              {2, 3, 4, 5, 1},            1 },
        { "Single element",            {42},                       42 },
        // Tricky layout: last value appears on both sides of pivot
        { "Dup max on both sides",     {2, 2, 2, 0, 1, 2},         0 }
    };

    runTests("Linear (by hand)",              findMinLinearManual, cases);
    runTests("Linear (library: min_element)", findMinLinearLib,    cases);
    runTests("Binary (by hand)",              findMinBinaryManual, cases);

    std::cout << "All tests passed successfully!\n";
    return 0;
}
