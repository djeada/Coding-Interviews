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
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

// Simple Implementation (O((n+m) log(n+m)))
void mergeSortedSimple(std::vector<int>& arr1, const std::vector<int>& arr2) {
    arr1.insert(arr1.end(), arr2.begin(), arr2.end());
    std::sort(arr1.begin(), arr1.end());
}

// Optimal Merge Implementation (O(n+m))
void mergeSortedOptimal(std::vector<int>& arr1, const std::vector<int>& arr2) {
    int i = (int)arr1.size() - 1;
    int j = (int)arr2.size() - 1;
    int k = (int)arr1.size() + (int)arr2.size() - 1;

    arr1.resize(k + 1);

    while (i >= 0 && j >= 0) {
        if (arr1[i] >= arr2[j]) {
            arr1[k--] = arr1[i--];
        } else {
            arr1[k--] = arr2[j--];
        }
    }
    while (j >= 0) {
        arr1[k--] = arr2[j--];
    }
}

// --- Test case struct ---
struct TestCaseMerge {
    std::string name;
    std::vector<int> a;
    std::vector<int> b;
    std::vector<int> expected;
};

// --- Test runners ---
void testMergeSimple(const std::vector<TestCaseMerge>& cases) {
    std::cout << "=== Testing mergeSortedSimple ===\n";
    for (auto& tc : cases) {
        auto got = tc.a;
        mergeSortedSimple(got, tc.b);
        bool pass = (got == tc.expected);
        std::cout
            << tc.name
            << ": expected={";
        for (size_t i = 0; i < tc.expected.size(); ++i) {
            std::cout << tc.expected[i] 
                      << (i+1 < tc.expected.size() ? "," : "");
        }
        std::cout << "}, got={";
        for (size_t i = 0; i < got.size(); ++i) {
            std::cout << got[i] 
                      << (i+1 < got.size() ? "," : "");
        }
        std::cout << "} -> " << (pass ? "PASS" : "FAIL") << "\n";
        assert(pass);
    }
    std::cout << "\n";
}

void testMergeOptimal(const std::vector<TestCaseMerge>& cases) {
    std::cout << "=== Testing mergeSortedOptimal ===\n";
    for (auto& tc : cases) {
        auto got = tc.a;
        mergeSortedOptimal(got, tc.b);
        bool pass = (got == tc.expected);
        std::cout
            << tc.name
            << ": expected={";
        for (size_t i = 0; i < tc.expected.size(); ++i) {
            std::cout << tc.expected[i] 
                      << (i+1 < tc.expected.size() ? "," : "");
        }
        std::cout << "}, got={";
        for (size_t i = 0; i < got.size(); ++i) {
            std::cout << got[i] 
                      << (i+1 < got.size() ? "," : "");
        }
        std::cout << "} -> " << (pass ? "PASS" : "FAIL") << "\n";
        assert(pass);
    }
    std::cout << "\n";
}

int main() {
    std::vector<TestCaseMerge> cases = {
        { "Interleaved",    {1,3,5},      {2,4,6},      {1,2,3,4,5,6} },
        { "All before",     {1,2,3},      {4,5,6},      {1,2,3,4,5,6} },
        { "All after",      {4,5,6},      {1,2,3},      {1,2,3,4,5,6} },
        { "All equal",      {1,1,1},      {1,1,1},      {1,1,1,1,1,1} },
        { "Empty first",    {},           {1,2,3},      {1,2,3} },
        { "Empty second",   {4,5,6},      {},           {4,5,6} },
        { "Single elements",{2},          {1},          {1,2} }
    };

    testMergeSimple(cases);
    testMergeOptimal(cases);

    std::cout << "All tests passed successfully!\n";
    return 0;
}
