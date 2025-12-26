/*
 * Task: Identify the majority element in an array.
 *
 * A majority element is a value that appears more than ⌊n/2⌋ times
 * in an array of length n. If such an element exists, return it;
 * otherwise, indicate that no majority exists.
 *
 * Visual intuition:
 * For an array of length n, a majority must occupy more than half
 * of the positions. That means at most one majority element can exist.
 *
 * Examples:
 * [2, 2, 2, 1, 3]           -> Majority: 2   (appears 3/5 > 2.5)
 * [7, 7, 7, 7]              -> Majority: 7   (appears 4/4 > 2)
 * [1, 1, 2, 2]              -> No majority   (2/4 is not > 2)
 * [42]                      -> Majority: 42  (1/1 > 0.5)
 *
 * Example Input/Output:
 * Input:  [3, 3, 4, 2, 3, 3, 3]
 * Output: 3
 *
 * Input:  [1, 2, 3, 4, 5]
 * Output: No majority
 *
 * Input:  [1, 1, 1, 2, 2]
 * Output: 1
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

// ---- Utility ----
bool isMajority(const std::vector<int> &arr, int candidate) {
  return std::count(arr.begin(), arr.end(), candidate) * 2 >
         static_cast<int>(arr.size());
}

// ---- Implementations ----

// Boyer–Moore Majority Vote (O(n), no modifications)
int majorityCounting(const std::vector<int> &arr) {
  if (arr.empty())
    throw std::invalid_argument("Array is empty.");
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

// Finds and returns the majority element using the frequency dictionary
// approach (O(n) time, O(n) space).
int majorityFrequency(const std::vector<int> &arr) {
  if (arr.empty())
    throw std::invalid_argument("Array is empty.");
  std::unordered_map<int, int> freq;
  const int n = static_cast<int>(arr.size());
  for (int v : arr) {
    int c = ++freq[v]; // increment the count for v
    if (c * 2 > n)
      return v; // early exit if v is majority
  }
  throw std::invalid_argument("No majority exists.");
}

// ---- Testing infrastructure ----
struct TestCase {
  std::string name;
  std::vector<int> arr;
  bool expectException;
  int expected; // only meaningful if expectException == false
};

// Generic runner
template <typename Func>
void runTests(const std::string &title, const std::vector<TestCase> &cases,
              Func func) {
  std::cout << "=== " << title << " ===\n";
  for (auto &tc : cases) {
    bool passed = false;
    try {
      int result = func(tc.arr);
      if (!tc.expectException && result == tc.expected) {
        passed = true;
      }
    } catch (const std::invalid_argument &) {
      if (tc.expectException)
        passed = true;
    }
    std::cout << tc.name << " -> " << (passed ? "PASS" : "FAIL") << "\n";
    assert(passed);
  }
  std::cout << "\n";
}

int main() {
  std::vector<TestCase> cases = {{"No majority", {1, 2, 3, 4, 5}, true, 0},
                                 {"Simple majority", {2, 2, 2, 1, 3}, false, 2},
                                 {"Even split", {1, 1, 2, 2}, true, 0},
                                 {"All same", {7, 7, 7, 7}, false, 7},
                                 {"Single element", {42}, false, 42},
                                 {"Large random no",
                                  [] {
                                    std::vector<int> v(100);
                                    for (int i = 0; i < 100; ++i)
                                      v[i] = i % 2; // 50 zeros, 50 ones
                                    return v;
                                  }(),
                                  true, 0},
                                 {"Large random yes",
                                  [] {
                                    std::vector<int> v(101, 1);
                                    for (int i = 0; i < 50; ++i)
                                      v[i] = 0;
                                    return v;
                                  }(),
                                  false, 1}};

  runTests("Testing majorityCounting (Boyer–Moore)", cases, majorityCounting);
  runTests("Testing majorityFrequency (Hash Map)", cases, majorityFrequency);

  std::cout << "All tests passed successfully!\n";
  return 0;
}
