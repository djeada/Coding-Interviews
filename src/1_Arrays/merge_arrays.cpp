/*
 * TASK: Merge Two Sorted Arrays
 *
 * Given two sorted arrays arr1 and arr2, merge them into a single sorted array.
 * The merged array replaces the contents of arr1.
 *
 * Example:
 * Input: arr1 = [1, 3, 5], arr2 = [2, 4, 6]
 * Output: arr1 = [1, 2, 3, 4, 5, 6]
 */

#include <algorithm>
#include <cassert>
#include <vector>
#include <iostream>

// Simple Implementation (O((n+m)log(n+m)), straightforward)
void mergeSortedSimple(std::vector<int>& arr1, const std::vector<int>& arr2) {
    arr1.insert(arr1.end(), arr2.begin(), arr2.end());
    std::sort(arr1.begin(), arr1.end());
}

// Optimal Merge Implementation (O(n+m), efficient merging)
void mergeSortedOptimal(std::vector<int>& arr1, const std::vector<int>& arr2) {
    int idx1 = arr1.size() - 1;
    int idx2 = arr2.size() - 1;
    int idxMerged = arr1.size() + arr2.size() - 1;

    arr1.resize(idxMerged + 1);

    while (idx1 >= 0 && idx2 >= 0) {
        arr1[idxMerged--] =
            (arr1[idx1] >= arr2[idx2]) ? arr1[idx1--] : arr2[idx2--];
    }

    // Copy remaining elements from arr2, if any
    while (idx2 >= 0) {
        arr1[idxMerged--] = arr2[idx2--];
    }
}

// Testing correctness
void test() {
    std::vector<std::tuple<std::vector<int>, std::vector<int>, std::vector<int>>> testCases = {
        {{1, 3, 5}, {2, 4, 6}, {1, 2, 3, 4, 5, 6}},
        {{1, 2, 3}, {4, 5, 6}, {1, 2, 3, 4, 5, 6}},
        {{2, 4, 6}, {1, 3, 5}, {1, 2, 3, 4, 5, 6}},
        {{1, 1, 1}, {1, 1, 1}, {1, 1, 1, 1, 1, 1}},
        {{}, {1, 2, 3}, {1, 2, 3}},
    };

    for (const auto& [arr1, arr2, expected] : testCases) {
        auto arrSimple = arr1;
        mergeSortedSimple(arrSimple, arr2);
        assert(arrSimple == expected);

        auto arrOptimal = arr1;
        mergeSortedOptimal(arrOptimal, arr2);
        assert(arrOptimal == expected);
    }

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
