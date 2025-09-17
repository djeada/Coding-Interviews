/*
 * SMALLEST K NUMBERS EXTRACTION
 *
 * This program finds the smallest 'k' numbers from a given list of numbers.
 * It demonstrates three modern C++ implementations:
 *
 * 1. Simple Sort Method:
 *    - Sorts the entire list and then takes the first k numbers.
 *    - Time Complexity: O(n log n)
 *
 * 2. Max Heap (Priority Queue) Method:
 *    - Maintains a max heap of size k, inserting numbers and removing the
 *      largest when the heap exceeds size k.
 *    - Time Complexity: O(n log k)
 *
 * 3. nth_element Method:
 *    - Uses std::nth_element to partition the vector so that the first k elements
 *      are the smallest, then sorts those k numbers.
 *    - Average Time Complexity: O(n)
 *
 * Edge Cases:
 *  - If k is 0, an empty vector is returned.
 *  - If k is greater than or equal to the input size, the entire sorted list is returned.
 *
 * Visual Illustration:
 *  Given the input:
 *      [4, 5, 1, 6, 2, 7, 3, 8]
 *  and k = 4,
 *
 *  The smallest 4 numbers are:
 *      [1, 2, 3, 4]
 *
 * Example Input/Output:
 *  Input:  {4, 5, 1, 6, 2, 7, 3, 8}, k = 4
 *  Output: {1, 2, 3, 4}
 *  Explanation: After processing using any of the three methods, the result is the
 *               four smallest numbers in sorted order.
 */

#include <algorithm>
#include <cassert>
#include <queue>
#include <vector>

// Implementation 1: Simple Sort
std::vector<int> findSmallestKNumbersSort(const std::vector<int>& input, int k) {
    if (k >= static_cast<int>(input.size())) {
        std::vector<int> result = input;
        std::sort(result.begin(), result.end());
        return result;
    }
    std::vector<int> result = input;
    std::sort(result.begin(), result.end());
    result.resize(k);
    return result;
}

// Implementation 2: Max Heap (Priority Queue) Approach
std::vector<int> findSmallestKNumbersHeap(const std::vector<int>& input, int k) {
    if (k <= 0) return {};
    if (k >= static_cast<int>(input.size())) {
        std::vector<int> result = input;
        std::sort(result.begin(), result.end());
        return result;
    }
    std::priority_queue<int> maxHeap;
    for (const auto& num : input) {
        if (maxHeap.size() < static_cast<size_t>(k)) {
            maxHeap.push(num);
        } else if (num < maxHeap.top()) {
            maxHeap.pop();
            maxHeap.push(num);
        }
    }
    std::vector<int> result;
    while (!maxHeap.empty()) {
        result.push_back(maxHeap.top());
        maxHeap.pop();
    }
    std::sort(result.begin(), result.end());
    return result;
}

// Implementation 3: nth_element Approach
std::vector<int> findSmallestKNumbersNthElement(const std::vector<int>& input, int k) {
    if (k <= 0) return {};
    if (k >= static_cast<int>(input.size())) {
        std::vector<int> result = input;
        std::sort(result.begin(), result.end());
        return result;
    }
    std::vector<int> result = input;
    std::nth_element(result.begin(), result.begin() + k, result.end());
    result.resize(k);
    std::sort(result.begin(), result.end());
    return result;
}

void testFindSmallestKNumbers() {
    std::vector<int> testArray1 {4, 5, 1, 6, 2, 7, 3, 8};
    std::vector<int> expected1 {1, 2, 3, 4};

    // Test Simple Sort Method
    assert(findSmallestKNumbersSort(testArray1, 4) == expected1);
    // Test Max Heap Method
    assert(findSmallestKNumbersHeap(testArray1, 4) == expected1);
    // Test nth_element Method
    assert(findSmallestKNumbersNthElement(testArray1, 4) == expected1);

    std::vector<int> testArray2 {4, 5, 1, 6, 2, 7, 3, 8};
    std::vector<int> expected2 {1, 2, 3, 4, 5, 6, 7, 8};
    assert(findSmallestKNumbersSort(testArray2, 8) == expected2);
    assert(findSmallestKNumbersHeap(testArray2, 8) == expected2);
    assert(findSmallestKNumbersNthElement(testArray2, 8) == expected2);

    std::vector<int> testArray3 {4, 5, 1, 6, 2, 7, 3, 8};
    std::vector<int> expected3 {1};
    assert(findSmallestKNumbersSort(testArray3, 1) == expected3);
    assert(findSmallestKNumbersHeap(testArray3, 1) == expected3);
    assert(findSmallestKNumbersNthElement(testArray3, 1) == expected3);

    std::vector<int> testArray4 {4, 5, 1, 6, 2, 7, 2, 8};
    std::vector<int> expected4 {1, 2};
    assert(findSmallestKNumbersSort(testArray4, 2) == expected4);
    assert(findSmallestKNumbersHeap(testArray4, 2) == expected4);
    assert(findSmallestKNumbersNthElement(testArray4, 2) == expected4);
}

int main() {
    testFindSmallestKNumbers();
    return 0;
}
