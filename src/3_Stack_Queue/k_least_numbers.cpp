/*
 * Task: Find the smallest k numbers from an unsorted list.
 *
 * SMALLEST K NUMBERS EXTRACTION
 *
 * Find the smallest 'k' numbers from a given list of numbers.
 *
 * Edge Cases:
 *  - If k is 0, an empty vector is returned.
 *  - If k is greater than or equal to the input size, the entire sorted list is
 * returned.
 *
 * Visual Illustration:
 *  Given the input:
 *      [4, 5, 1, 6, 2, 7, 3, 8]
 *  and k = 4,
 *
 *  The smallest 4 numbers are:
 *      [1, 2, 3, 4]
 *
 * Example Input/Output:
 *  Input:  {4, 5, 1, 6, 2, 7, 3, 8}, k = 4
 *  Output: {1, 2, 3, 4}
 *  Explanation: After processing using any of the three methods, the result is
 * the four smallest numbers in sorted order.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

namespace {
struct TestRunner {
  int total = 0;
  int failed = 0;

  void expectEqual(const std::vector<int> &got,
                   const std::vector<int> &expected, const std::string &label) {
    ++total;
    if (got == expected) {
      std::cout << "[PASS] " << label << "\n";
      return;
    }
    ++failed;
    std::cout << "[FAIL] " << label << " expected=" << toString(expected)
              << " got=" << toString(got) << "\n";
  }

  void summary() const {
    std::cout << "Tests: " << total - failed << " passed, " << failed
              << " failed, " << total << " total\n";
  }

private:
  static std::string toString(const std::vector<int> &values) {
    std::ostringstream oss;
    oss << "{";
    for (size_t i = 0; i < values.size(); ++i) {
      if (i > 0)
        oss << ", ";
      oss << values[i];
    }
    oss << "}";
    return oss.str();
  }
};
} // namespace

// Implementation 1: Simple Sort
std::vector<int> findSmallestKNumbersSort(const std::vector<int> &input,
                                          int k) {
  if (k >= static_cast<int>(input.size())) {
    std::vector<int> result = input;
    std::sort(result.begin(), result.end());
    return result;
  }
  std::vector<int> result = input;
  std::sort(result.begin(), result.end());
  result.resize(k);
  return result;
}

// Implementation 2: Max Heap (Priority Queue) Approach
std::vector<int> findSmallestKNumbersHeap(const std::vector<int> &input,
                                          int k) {
  if (k <= 0)
    return {};
  if (k >= static_cast<int>(input.size())) {
    std::vector<int> result = input;
    std::sort(result.begin(), result.end());
    return result;
  }
  std::priority_queue<int> maxHeap;
  for (const auto &num : input) {
    if (maxHeap.size() < static_cast<size_t>(k)) {
      maxHeap.push(num);
    } else if (num < maxHeap.top()) {
      maxHeap.pop();
      maxHeap.push(num);
    }
  }
  std::vector<int> result;
  while (!maxHeap.empty()) {
    result.push_back(maxHeap.top());
    maxHeap.pop();
  }
  std::sort(result.begin(), result.end());
  return result;
}

// Implementation 3: nth_element Approach
std::vector<int> findSmallestKNumbersNthElement(const std::vector<int> &input,
                                                int k) {
  if (k <= 0)
    return {};
  if (k >= static_cast<int>(input.size())) {
    std::vector<int> result = input;
    std::sort(result.begin(), result.end());
    return result;
  }
  std::vector<int> result = input;
  std::nth_element(result.begin(), result.begin() + k, result.end());
  result.resize(k);
  std::sort(result.begin(), result.end());
  return result;
}

void testFindSmallestKNumbers() {
  TestRunner runner;
  std::vector<int> testArray1{4, 5, 1, 6, 2, 7, 3, 8};
  std::vector<int> expected1{1, 2, 3, 4};

  // Test Simple Sort Method
  runner.expectEqual(findSmallestKNumbersSort(testArray1, 4), expected1,
                     "sort k=4");
  // Test Max Heap Method
  runner.expectEqual(findSmallestKNumbersHeap(testArray1, 4), expected1,
                     "heap k=4");
  // Test nth_element Method
  runner.expectEqual(findSmallestKNumbersNthElement(testArray1, 4), expected1,
                     "nth_element k=4");

  std::vector<int> testArray2{4, 5, 1, 6, 2, 7, 3, 8};
  std::vector<int> expected2{1, 2, 3, 4, 5, 6, 7, 8};
  runner.expectEqual(findSmallestKNumbersSort(testArray2, 8), expected2,
                     "sort k=8");
  runner.expectEqual(findSmallestKNumbersHeap(testArray2, 8), expected2,
                     "heap k=8");
  runner.expectEqual(findSmallestKNumbersNthElement(testArray2, 8), expected2,
                     "nth_element k=8");

  std::vector<int> testArray3{4, 5, 1, 6, 2, 7, 3, 8};
  std::vector<int> expected3{1};
  runner.expectEqual(findSmallestKNumbersSort(testArray3, 1), expected3,
                     "sort k=1");
  runner.expectEqual(findSmallestKNumbersHeap(testArray3, 1), expected3,
                     "heap k=1");
  runner.expectEqual(findSmallestKNumbersNthElement(testArray3, 1), expected3,
                     "nth_element k=1");

  std::vector<int> testArray4{4, 5, 1, 6, 2, 7, 2, 8};
  std::vector<int> expected4{1, 2};
  runner.expectEqual(findSmallestKNumbersSort(testArray4, 2), expected4,
                     "sort k=2 with dup");
  runner.expectEqual(findSmallestKNumbersHeap(testArray4, 2), expected4,
                     "heap k=2 with dup");
  runner.expectEqual(findSmallestKNumbersNthElement(testArray4, 2), expected4,
                     "nth_element k=2 with dup");
  runner.summary();
}

int main() {
  testFindSmallestKNumbers();
  return 0;
}
