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
#include <unordered_set>
#include <vector>
#include <string>
#include <functional>

// Simple Solution (O(n^2) complexity)
int countDuplicatesSimple(const std::vector<int>& arr) {
    int count = 0;
    std::vector<int> seen;
    for (int val : arr)  {
        // if this value occurs more than once, and we haven't counted it yet
        if (std::count(arr.begin(), arr.end(), val) > 1 &&
            std::find(seen.begin(), seen.end(), val) == seen.end()) {
            seen.push_back(val);
            ++count;
        }
    }
    return count;
}

// O(n) average (hash table lookups & inserts)
int countDuplicatesSet(const std::vector<int>& arr) {
    std::unordered_set<int> seen;
    std::unordered_set<int> duplicates;

    for (int val : arr) {
        if (seen.count(val)) {
            duplicates.insert(val); // insert only if we've seen it before
        } else {
            seen.insert(val);
        }
    }

    return duplicates.size();
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

// --- Utility to print vectors ---
template <typename T>
std::string vecToStr(const std::vector<T>& v) {
    std::string s = "{";
    for (size_t i = 0; i < v.size(); ++i) {
        s += std::to_string(v[i]);
        if (i + 1 < v.size()) s += ",";
    }
    s += "}";
    return s;
}

// --- Generic test runner ---
template <typename TestCase, typename Func, typename Extract, typename ToStr>
void runTests(
    const std::string& title,
    const std::vector<TestCase>& cases,
    Func func,
    Extract expectedExtractor,
    ToStr toString
) {
    std::cout << "=== " << title << " ===\n";
    for (auto& tc : cases) {
        auto got = func(tc.arr);
        auto expected = expectedExtractor(tc);

        // normalize for comparison if vector
        if constexpr (std::is_same_v<decltype(got), std::vector<int>>) {
            auto sortedGot = got;
            auto sortedExpected = expected;
            std::sort(sortedGot.begin(), sortedGot.end());
            std::sort(sortedExpected.begin(), sortedExpected.end());
            bool pass = (sortedGot == sortedExpected);
            std::cout << tc.name
                      << ": expected=" << toString(expected)
                      << ", got=" << toString(got)
                      << " -> " << (pass ? "PASS" : "FAIL")
                      << "\n";
            assert(pass);
        } else {
            bool pass = (got == expected);
            std::cout << tc.name
                      << ": expected=" << toString(expected)
                      << ", got=" << toString(got)
                      << " -> " << (pass ? "PASS" : "FAIL")
                      << "\n";
            assert(pass);
        }
    }
    std::cout << "\n";
}

// --- Example usage ---

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

    runTests(
        "Testing countDuplicatesSimple",
        countCases,
        countDuplicatesSimple,
        [](auto& tc){ return tc.expectedCount; },
        [](auto v){ return std::to_string(v); }
    );

    runTests(
        "Testing countDuplicatesSet",
        countCases,
        countDuplicatesSet,
        [](auto& tc){ return tc.expectedCount; },
        [](auto v){ return std::to_string(v); }
    );
    
    runTests(
        "Testing countDuplicatesOptimal",
        countCases,
        countDuplicatesOptimal,
        [](auto& tc){ return tc.expectedCount; },
        [](auto v){ return std::to_string(v); }
    );

    runTests(
        "Testing findDuplicatesOptimal",
        listCases,
        findDuplicatesOptimal,
        [](auto& tc){ return tc.expectedList; },
        [](auto v){ return vecToStr(v); }
    );

    std::cout << "All tests passed successfully!\n";
    return 0;
}
