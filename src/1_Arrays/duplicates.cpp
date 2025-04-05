/*
 * TASK: Find and Count Duplicate Elements
 *
 * Given an integer vector, count how many duplicates exist and list the elements
 * that are duplicated.
 *
 * Example:
 * Input: [5, 10, 15, 5, 3, 3]
 * Output:
 *   - Count: 2 (elements 5 and 3)
 *   - Elements: [5, 3]
 */

#include <cassert>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <iostream>

// Simple Solution (O(n^2) complexity due to linear search)
int countDuplicatesSimple(const std::vector<int>& arr) {
    int count = 0;
    std::vector<int> duplicates;

    for (size_t i = 0; i < arr.size(); ++i) {
        if (std::count(arr.begin(), arr.end(), arr[i]) > 1 &&
            std::find(duplicates.begin(), duplicates.end(), arr[i]) == duplicates.end()) {
            duplicates.push_back(arr[i]);
            count++;
        }
    }

    return count;
}

// Optimal Solution (O(n) complexity using hashing)
int countDuplicatesOptimal(const std::vector<int>& arr) {
    std::unordered_map<int, int> frequency;
    int duplicates = 0;

    for (int num : arr)
        frequency[num]++;

    for (const auto& [key, value] : frequency)
        if (value > 1)
            duplicates++;

    return duplicates;
}

// Optimal solution to return duplicate elements (O(n))
std::vector<int> findDuplicatesOptimal(const std::vector<int>& arr) {
    std::unordered_map<int, int> frequency;
    std::vector<int> duplicates;

    for (int num : arr)
        frequency[num]++;

    for (const auto& [key, value] : frequency)
        if (value > 1)
            duplicates.push_back(key);

    return duplicates;
}

// Testing
void test() {
    std::vector<int> arr1{1, 2, 3, 4, 5};
    assert(countDuplicatesOptimal(arr1) == 0);
    assert(findDuplicatesOptimal(arr1).empty());

    std::vector<int> arr2{5, 10, 15, 5, 3, 3};
    assert(countDuplicatesOptimal(arr2) == 2);
    auto duplicates2 = findDuplicatesOptimal(arr2);
    std::sort(duplicates2.begin(), duplicates2.end());
    assert(duplicates2 == std::vector<int>({3, 5}));

    std::vector<int> arr3{3, 9, 9, 7, 3};
    assert(countDuplicatesOptimal(arr3) == 2);
    auto duplicates3 = findDuplicatesOptimal(arr3);
    std::sort(duplicates3.begin(), duplicates3.end());
    assert(duplicates3 == std::vector<int>({3, 9}));

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
