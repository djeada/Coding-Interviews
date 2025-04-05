/*
 * TASK: Find the Minimum Number
 *
 * Given a vector of integers, identify the smallest number.
 *
 * Example:
 * Input: [3, 5, 1, 4, 2]
 * Output: 1
 */

#include <algorithm>
#include <cassert>
#include <vector>
#include <iostream>

// Simple Iterative Solution (Manual iteration, O(n))
int findMinSimple(const std::vector<int>& arr) {
    int minNum = arr[0];
    for (int num : arr)
        if (num < minNum)
            minNum = num;
    return minNum;
}

// Optimal STL Solution (Using std::min_element, concise, O(n))
int findMinOptimal(const std::vector<int>& arr) {
    return *std::min_element(arr.begin(), arr.end());
}

// Testing correctness
void test() {
    std::vector<std::pair<std::vector<int>, int>> testCases = {
        {{3, 5, 1, 4, 2}, 1},
        {{-3, -5, -1, -4, -2}, -5},
        {{10, 20, 30, 40, 5}, 5},
        {{1, 1, 1, 1, 1}, 1},
        {{42}, 42} // single element case
    };

    for (const auto& [numbers, expected] : testCases) {
        assert(findMinSimple(numbers) == expected);
        assert(findMinOptimal(numbers) == expected);
    }

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
