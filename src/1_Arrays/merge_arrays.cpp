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
#include <iterator>
#include <random>
#include <string>
#include <tuple>
#include <vector>

// Simple Implementation (O((n+m) log(n+m)))
void mergeSortedSimple(std::vector<int> &arr1, const std::vector<int> &arr2) {
  arr1.insert(arr1.end(), arr2.begin(), arr2.end());
  std::sort(arr1.begin(), arr1.end());
}

// Optimal Merge Implementation (O(n+m))
void mergeSortedOptimal(std::vector<int> &arr1, const std::vector<int> &arr2) {
  std::size_t n = arr1.size();
  std::size_t m = arr2.size();

  arr1.resize(n + m);

  std::size_t k = n + m; // write position (one past the last index)

  // Only need to drain arr2; any leftover arr1 elements are already in place
  while (m > 0) {
    if (n > 0 && arr1[n - 1] >= arr2[m - 1]) {
      arr1[--k] = arr1[--n];
    } else {
      arr1[--k] = arr2[--m];
    }
  }
}

// Copy-merge using std::merge (also O(n+m)), replaces contents of 'a'
void merge_sorted_copy(std::vector<int> &a, const std::vector<int> &b) {
  std::vector<int> out;
  out.reserve(a.size() + b.size());
  std::merge(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(out));
  a = std::move(out);
}

// --- Test case struct ---
struct TestCaseMerge {
  std::string name;
  std::vector<int> a;
  std::vector<int> b;
  std::vector<int> expected;
};

// --- Test runners ---
void printVec(const std::vector<int> &v) {
  std::cout << "{";
  for (size_t i = 0; i < v.size(); ++i) {
    std::cout << v[i] << (i + 1 < v.size() ? "," : "");
  }
  std::cout << "}";
}

void testMergeSimple(const std::vector<TestCaseMerge> &cases) {
  std::cout << "=== Testing mergeSortedSimple ===\n";
  for (const auto &tc : cases) {
    auto got = tc.a;
    mergeSortedSimple(got, tc.b);
    bool pass = (got == tc.expected);
    std::cout << tc.name << ": expected=";
    printVec(tc.expected);
    std::cout << ", got=";
    printVec(got);
    std::cout << " -> " << (pass ? "PASS" : "FAIL") << "\n";
    assert(pass);
  }
  std::cout << "\n";
}

void testMergeOptimal(const std::vector<TestCaseMerge> &cases) {
  std::cout << "=== Testing mergeSortedOptimal ===\n";
  for (const auto &tc : cases) {
    auto got = tc.a;
    mergeSortedOptimal(got, tc.b);
    bool pass = (got == tc.expected);
    std::cout << tc.name << ": expected=";
    printVec(tc.expected);
    std::cout << ", got=";
    printVec(got);
    std::cout << " -> " << (pass ? "PASS" : "FAIL") << "\n";
    assert(pass);
  }
  std::cout << "\n";
}

void testMergeCopy(const std::vector<TestCaseMerge> &cases) {
  std::cout << "=== Testing merge_sorted_copy ===\n";
  for (const auto &tc : cases) {
    auto got = tc.a;
    merge_sorted_copy(got, tc.b);
    bool pass = (got == tc.expected);
    std::cout << tc.name << ": expected=";
    printVec(tc.expected);
    std::cout << ", got=";
    printVec(got);
    std::cout << " -> " << (pass ? "PASS" : "FAIL") << "\n";
    assert(pass);
  }
  std::cout << "\n";
}

// Property-style randomized test to ensure all implementations agree
void testEquivalenceRandom(int trials = 200) {
  std::cout << "=== Randomized equivalence (all three agree) ===\n";
  std::mt19937 rng(1234567);
  std::uniform_int_distribution<int> lenDist(0, 20);
  std::uniform_int_distribution<int> valDist(-10, 10);

  for (int t = 0; t < trials; ++t) {
    int n = lenDist(rng);
    int m = lenDist(rng);

    std::vector<int> a(n), b(m);
    for (int &x : a)
      x = valDist(rng);
    for (int &x : b)
      x = valDist(rng);

    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    auto a1 = a, a2 = a, a3 = a;
    mergeSortedSimple(a1, b);
    mergeSortedOptimal(a2, b);
    merge_sorted_copy(a3, b);

    bool agree = (a1 == a2) && (a2 == a3);
    if (!agree) {
      std::cout << "Disagreement on trial " << t << "\n";
      std::cout << "a=";
      printVec(a);
      std::cout << ", b=";
      printVec(b);
      std::cout << "\n";
      std::cout << "simple=";
      printVec(a1);
      std::cout << "\n";
      std::cout << "optimal=";
      printVec(a2);
      std::cout << "\n";
      std::cout << "copy  =";
      printVec(a3);
      std::cout << "\n";
    }
    assert(agree);
  }
  std::cout << "Randomized checks passed.\n\n";
}

int main() {
  std::vector<TestCaseMerge> cases = {
      {"Interleaved", {1, 3, 5}, {2, 4, 6}, {1, 2, 3, 4, 5, 6}},
      {"All before", {1, 2, 3}, {4, 5, 6}, {1, 2, 3, 4, 5, 6}},
      {"All after", {4, 5, 6}, {1, 2, 3}, {1, 2, 3, 4, 5, 6}},
      {"All equal", {1, 1, 1}, {1, 1, 1}, {1, 1, 1, 1, 1, 1}},
      {"Empty first", {}, {1, 2, 3}, {1, 2, 3}},
      {"Empty second", {4, 5, 6}, {}, {4, 5, 6}},
      {"Single elements", {2}, {1}, {1, 2}},
      {"Negatives", {-5, -3, 0}, {-4, -2, 2}, {-5, -4, -3, -2, 0, 2}},
      {"Duplicates", {1, 2, 2, 3}, {2, 2, 4}, {1, 2, 2, 2, 2, 3, 4}}};

  testMergeSimple(cases);
  testMergeOptimal(cases);
  testMergeCopy(cases);
  testEquivalenceRandom();

  std::cout << "All tests passed successfully!\n";
  return 0;
}
