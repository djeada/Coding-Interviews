/*
 * TASK: Identify the Majority Element
 *
 * A majority element is an element that appears more than n/2 times in an array
 * of size n. If such an element exists, return it; otherwise, indicate no majority.
 *
 * Example:
 * Input: [2, 2, 2, 1, 1]
 * Output: 2
 *
 * Input: [1, 2, 3, 4, 5]
 * Output: No majority
 */

#include <algorithm>
#include <cassert>
#include <vector>
#include <stdexcept>
#include <random>
#include <iostream>

bool isMajority(const std::vector<int>& arr, int candidate) {
    return std::count(arr.begin(), arr.end(), candidate) * 2 > arr.size();
}

// Simple counting approach (Boyer-Moore Majority Vote Algorithm, O(n))
int majorityCounting(const std::vector<int>& arr) {
    int candidate = arr[0], count = 1;
    for (size_t i = 1; i < arr.size(); ++i) {
        if (count == 0) {
            candidate = arr[i];
            count = 1;
        } else {
            count += (arr[i] == candidate) ? 1 : -1;
        }
    }

    if (!isMajority(arr, candidate))
        throw std::invalid_argument("No majority exists.");

    return candidate;
}

// Partition-based Quickselect approach (average O(n), modifies input array)
int randomIndex(int start, int end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(start, end);
    return dist(gen);
}

int partition(std::vector<int>& arr, int start, int end) {
    int pivotIdx = randomIndex(start, end);
    std::swap(arr[pivotIdx], arr[end]);

    int smaller = start;
    for (int i = start; i < end; ++i) {
        if (arr[i] < arr[end])
            std::swap(arr[i], arr[smaller++]);
    }

    std::swap(arr[smaller], arr[end]);
    return smaller;
}

int majorityPartition(std::vector<int>& arr) {
    int mid = arr.size() / 2, start = 0, end = arr.size() - 1;

    while (true) {
        int idx = partition(arr, start, end);
        if (idx == mid)
            break;
        else if (idx < mid)
            start = idx + 1;
        else
            end = idx - 1;
    }

    int candidate = arr[mid];
    if (!isMajority(arr, candidate))
        throw std::invalid_argument("No majority exists.");

    return candidate;
}

// Testing correctness
void test() {
    std::vector<int> arrNoMajority{1, 2, 3, 4, 5};
    std::vector<int> arrMajority{2, 2, 2, 1, 3};

    // Test counting approach
    try {
        majorityCounting(arrNoMajority);
        assert(false); // should not reach here
    } catch (const std::invalid_argument&) {}

    assert(majorityCounting(arrMajority) == 2);

    // Test partition approach (note: modifies array)
    try {
        auto arrCopy = arrNoMajority;
        majorityPartition(arrCopy);
        assert(false); // should not reach here
    } catch (const std::invalid_argument&) {}

    auto arrCopy = arrMajority;
    assert(majorityPartition(arrCopy) == 2);

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
