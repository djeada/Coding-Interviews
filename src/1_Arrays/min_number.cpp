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
#include <iostream>
#include <string>
#include <vector>

// Simple Iterative Solution (O(n))
int findMinSimple(const std::vector<int> &arr) {
  int minNum = arr[0];
  for (int num : arr)
    if (num < minNum)
      minNum = num;
  return minNum;
}

// Optimal STL Solution (O(n))
int findMinOptimal(const std::vector<int> &arr) {
  return *std::min_element(arr.begin(), arr.end());
}

struct TestCase {
  std::string name;
  std::vector<int> arr;
  int expected;
};

void testFindMinSimple(const std::vector<TestCase> &cases) {
  std::cout << "=== Testing findMinSimple ===\n";
  for (const auto &tc : cases) {
    int got = findMinSimple(tc.arr);
    bool pass = (got == tc.expected);
    std::cout << tc.name << ": expected=" << tc.expected << ", got=" << got
              << " -> " << (pass ? "PASS" : "FAIL") << "\n";
    assert(pass);
  }
  std::cout << "\n";
}

void testFindMinOptimal(const std::vector<TestCase> &cases) {
  std::cout << "=== Testing findMinOptimal ===\n";
  for (const auto &tc : cases) {
    int got = findMinOptimal(tc.arr);
    bool pass = (got == tc.expected);
    std::cout << tc.name << ": expected=" << tc.expected << ", got=" << got
              << " -> " << (pass ? "PASS" : "FAIL") << "\n";
    assert(pass);
  }
  std::cout << "\n";
}

int main() {
  std::vector<TestCase> cases = {{"Random order", {3, 5, 1, 4, 2}, 1},
                                 {"All negatives", {-3, -5, -1, -4}, -5},
                                 {"Min at end", {10, 20, 30, 40, 5}, 5},
                                 {"All equal", {1, 1, 1, 1, 1}, 1},
                                 {"Single element", {42}, 42},
                                 {"Two elements", {7, 3}, 3}};

  testFindMinSimple(cases);
  testFindMinOptimal(cases);

  std::cout << "All tests passed successfully!\n";
  return 0;
}
