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
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

bool isMajority(const std::vector<int>& arr, int candidate) {
    return std::count(arr.begin(), arr.end(), candidate) * 2 > static_cast<int>(arr.size());
}

// ---- Implementations ----

// Boyer–Moore Majority Vote (O(n), no modifications)
int majorityCounting(const std::vector<int>& arr) {
    if (arr.empty()) throw std::invalid_argument("Array is empty.");
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

// Quickselect-based partition (average O(n), modifies array)
int randomIndex(int start, int end) {
    static std::mt19937 gen{std::random_device{}()};
    std::uniform_int_distribution<> dist(start, end);
    return dist(gen);
}

int partition(std::vector<int>& arr, int start, int end) {
    int pivotIdx = randomIndex(start, end);
    std::swap(arr[pivotIdx], arr[end]);
    int store = start;
    for (int i = start; i < end; ++i) {
        if (arr[i] < arr[end]) {
            std::swap(arr[i], arr[store++]);
        }
    }
    std::swap(arr[store], arr[end]);
    return store;
}

int majorityPartition(std::vector<int>& arr) {
    if (arr.empty()) throw std::invalid_argument("Array is empty.");
    int mid = arr.size() / 2, lo = 0, hi = arr.size() - 1;
    while (true) {
        int idx = partition(arr, lo, hi);
        if (idx == mid) break;
        if (idx < mid) lo = idx + 1;
        else           hi = idx - 1;
    }
    int candidate = arr[mid];
    if (!isMajority(arr, candidate))
        throw std::invalid_argument("No majority exists.");
    return candidate;
}

// ---- Testing infrastructure ----

struct TestCase {
    std::string name;
    std::vector<int> arr;
    bool expectException;
    int expected;  // only meaningful if expectException == false
};

void testMajorityCounting(const std::vector<TestCase>& cases) {
    std::cout << "=== Testing majorityCounting ===\n";
    for (auto& tc : cases) {
        bool passed = false;
        try {
            int result = majorityCounting(tc.arr);
            if (!tc.expectException && result == tc.expected) {
                passed = true;
            }
        } catch (const std::invalid_argument&) {
            if (tc.expectException) passed = true;
        }
        std::cout
            << tc.name
            << " -> " << (passed ? "PASS" : "FAIL")
            << "\n";
        assert(passed);
    }
    std::cout << "\n";
}

void testMajorityPartition(const std::vector<TestCase>& cases) {
    std::cout << "=== Testing majorityPartition ===\n";
    for (auto& tc : cases) {
        bool passed = false;
        try {
            auto copy = tc.arr;               // partition modifies in-place
            int result = majorityPartition(copy);
            if (!tc.expectException && result == tc.expected) {
                passed = true;
            }
        } catch (const std::invalid_argument&) {
            if (tc.expectException) passed = true;
        }
        std::cout
            << tc.name
            << " -> " << (passed ? "PASS" : "FAIL")
            << "\n";
        assert(passed);
    }
    std::cout << "\n";
}


int main() {
    std::vector<TestCase> cases = {
        { "No majority",       {1,2,3,4,5},           true,  0 },
        { "Simple majority",   {2,2,2,1,3},          false, 2 },
        { "Even split",        {1,1,2,2},            true,  0 },
        { "All same",          {7,7,7,7},            false, 7 },
        { "Single element",    {42},                 false, 42 },
        { "Large random no",   []{
               std::vector<int> v(100);
               for(int i = 0; i < 100; ++i)
                   v[i] = i % 2;    // 50 zeros, 50 ones
               return v;
           }(),                  true, 0 },
        { "Large random yes",  []{
               std::vector<int> v(101, 1);
               for(int i = 0; i < 50; ++i)
                   v[i] = 0;
               return v;
           }(),                  false, 1 }
    };

    testMajorityCounting(cases);
    testMajorityPartition(cases);

    std::cout << "All tests passed successfully!\n";
    return 0;
}
