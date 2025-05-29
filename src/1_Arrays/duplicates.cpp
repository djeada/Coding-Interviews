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

#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

// Simple Solution (O(n^2) complexity)
int countDuplicatesSimple(const std::vector<int>& arr) {
    int count = 0;
    std::vector<int> seen;
    for (size_t i = 0; i < arr.size(); ++i) {
        // if this value occurs more than once, and we haven't counted it yet
        if (std::count(arr.begin(), arr.end(), arr[i]) > 1 &&
            std::find(seen.begin(), seen.end(), arr[i]) == seen.end()) {
            seen.push_back(arr[i]);
            ++count;
        }
    }
    return count;
}

// Optimal Solution (O(n) using hashing)
int countDuplicatesOptimal(const std::vector<int>& arr) {
    std::unordered_map<int,int> freq;
    for (int x : arr) freq[x]++;
    int duplicates = 0;
    for (auto& [key, val] : freq)
        if (val > 1) ++duplicates;
    return duplicates;
}

// Optimal solution to return duplicate elements (O(n))
std::vector<int> findDuplicatesOptimal(const std::vector<int>& arr) {
    std::unordered_map<int,int> freq;
    for (int x : arr) freq[x]++;
    std::vector<int> duplicates;
    for (auto& [key, val] : freq)
        if (val > 1)
            duplicates.push_back(key);
    return duplicates;
}

// --- Test case structs ---
struct TestCaseCount {
    std::string name;
    std::vector<int> arr;
    int expectedCount;
};

struct TestCaseList {
    std::string name;
    std::vector<int> arr;
    std::vector<int> expectedList;
};

// --- Test runners ---
void testCountSimple(const std::vector<TestCaseCount>& cases) {
    std::cout << "=== Testing countDuplicatesSimple ===\n";
    for (auto& tc : cases) {
        int got = countDuplicatesSimple(tc.arr);
        bool pass = (got == tc.expectedCount);
        std::cout
            << tc.name
            << ": expected=" << tc.expectedCount
            << ", got=" << got
            << " -> " << (pass ? "PASS" : "FAIL")
            << "\n";
        assert(pass);
    }
    std::cout << "\n";
}

void testCountOptimal(const std::vector<TestCaseCount>& cases) {
    std::cout << "=== Testing countDuplicatesOptimal ===\n";
    for (auto& tc : cases) {
        int got = countDuplicatesOptimal(tc.arr);
        bool pass = (got == tc.expectedCount);
        std::cout
            << tc.name
            << ": expected=" << tc.expectedCount
            << ", got=" << got
            << " -> " << (pass ? "PASS" : "FAIL")
            << "\n";
        assert(pass);
    }
    std::cout << "\n";
}

void testFindDuplicatesOptimal(const std::vector<TestCaseList>& cases) {
    std::cout << "=== Testing findDuplicatesOptimal ===\n";
    for (auto& tc : cases) {
        auto got = findDuplicatesOptimal(tc.arr);
        std::sort(got.begin(), got.end());
        auto expected = tc.expectedList;
        std::sort(expected.begin(), expected.end());
        bool pass = (got == expected);
        std::cout
            << tc.name
            << ": expected={";
        for (size_t i = 0; i < expected.size(); ++i) {
            std::cout << expected[i] << (i+1<expected.size()? ",":"");
        }
        std::cout << "}, got={";
        for (size_t i = 0; i < got.size(); ++i) {
            std::cout << got[i] << (i+1<got.size()? ",":"");
        }
        std::cout << "}"
                  << " -> " << (pass ? "PASS" : "FAIL")
                  << "\n";
        assert(pass);
    }
    std::cout << "\n";
}

int main() {
    std::vector<TestCaseCount> countCases = {
        { "No duplicates",      {1,2,3,4,5},             0 },
        { "Two pairs",          {5,10,15,5,3,3},         2 },
        { "Overlapping dups",   {3,9,9,7,3},             2 },
        { "All same",           {8,8,8,8},               1 },
        { "Single element",     {42},                    0 }
    };

    std::vector<TestCaseList> listCases = {
        { "No duplicates",      {1,2,3,4,5},             {} },
        { "Two values",         {5,10,15,5,3,3},         {3,5} },
        { "Two values",         {3,9,9,7,3},             {3,9} },
        { "All same",           {8,8,8,8},               {8} },
        { "Single element",     {42},                    {} }
    };

    testCountSimple(countCases);
    testCountOptimal(countCases);
    testFindDuplicatesOptimal(listCases);

    std::cout << "All tests passed successfully!\n";
    return 0;
}
