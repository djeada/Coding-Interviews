/*
 * Task: Dynamically compute the median of a number stream after each insert.
 *
 * DYNAMIC MEDIAN CALCULATION OF A NUMBER STREAM
 *
 * Demonstrate approaches for computing the median of a stream of numbers as
 * new elements are inserted:
 *
 * ASCII Illustration:
 *
 *         Dynamic Median Calculation:
 *
 *              Lower Half                Upper Half
 *           (max-heap: largest at top)  (min-heap: smallest at top)
 *                  [  ... ]                  [  ... ]
 *                        \                /
 *                         \              /
 *                          [  MEDIAN  ]
 *
 * Example:
 *    Inserting numbers: 5, 2, 3, 8, 1
 *
 *    Sorted order: 1, 2, 3, 5, 8
 *
 *    Median evolution:
 *       After inserting 5: Median = 5
 *       After inserting 2: Median = (2+5)/2 = 3.5
 *       After inserting 3: Median = 3
 *       After inserting 8: Median = (3+5)/2 = 4
 *       After inserting 1: Median = 3
 *
 * Input/Output:
 *    Input: A sequence of numbers
 *    Output: The median after each insertion
 *    Explanation: The median is defined as the middle number in a sorted list
 * or the average of the two middle numbers if the list has an even length.
 */

#include <algorithm>
#include <cmath>
#include <exception>
#include <iomanip>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

// Simple (Brute-force) Solution
//
// Stores all numbers in a vector and sorts it after each insertion.
//
// Time Complexity:
// - insert(): O(n log n) due to sorting after every insertion.
// - getMedian(): O(1).
//
// Space Complexity:
// - O(n) to store all elements.
//
// This approach is simple but inefficient for large data streams.
class SimpleMedianCalculator {
public:
  void insert(double num) {
    data.push_back(num);
    std::sort(data.begin(), data.end());
  }

  double getMedian() const {
    size_t size = data.size();
    if (size == 0)
      throw std::runtime_error("No numbers available");

    if (size % 2 == 1)
      return data[size / 2];
    else
      return (data[size / 2 - 1] + data[size / 2]) / 2.0;
  }

private:
  std::vector<double> data;
};

// Optimal (Efficient) Solution
//
// Uses two heaps:
// - Max-heap for the lower half of numbers
// - Min-heap for the upper half
//
// Time Complexity:
// - insert(): O(log n) due to heap insertion and rebalancing.
// - getMedian(): O(1).
//
// Space Complexity:
// - O(n) to store all elements across both heaps.
//
// This is the optimal solution for maintaining the median of a data stream.
class OptimalMedianCalculator {
public:
  void insert(double num) {
    if (minHeap.empty() || num >= minHeap.top()) {
      minHeap.push(num);
    } else {
      maxHeap.push(num);
    }

    // Balance the heaps so their sizes differ by at most 1.
    if (minHeap.size() > maxHeap.size() + 1) {
      maxHeap.push(minHeap.top());
      minHeap.pop();
    } else if (maxHeap.size() > minHeap.size()) {
      minHeap.push(maxHeap.top());
      maxHeap.pop();
    }
  }

  double getMedian() const {
    if (minHeap.empty() && maxHeap.empty())
      throw std::runtime_error("No numbers available");

    if (minHeap.size() > maxHeap.size())
      return minHeap.top();
    else
      return (minHeap.top() + maxHeap.top()) / 2.0;
  }

private:
  std::priority_queue<double, std::vector<double>, std::greater<double>>
      minHeap;
  std::priority_queue<double> maxHeap;
};

// Alternative (Educational) Solution
//
// Uses a multiset to maintain sorted order and an iterator pointing
// to the current median.
//
// Time Complexity:
// - insert(): O(log n) due to multiset insertion.
// - getMedian(): O(1).
//
// Space Complexity:
// - O(n) to store all elements.
//
// This solution is elegant and easy to reason about, but typically
// slower in practice than the heap-based approach due to tree overhead.
class AlternativeMedianCalculator {
public:
  void insert(double num) {
    if (data.empty()) {
      data.insert(num);
      medianIt = data.begin();
    } else {
      data.insert(num);
      // Adjust the median iterator based on the inserted value.
      if (num < *medianIt) {
        if (data.size() % 2 == 0) { // even -> odd
          --medianIt;
        }
      } else {
        if (data.size() % 2 == 1) { // odd -> even
          ++medianIt;
        }
      }
    }
  }

  double getMedian() const {
    if (data.empty())
      throw std::runtime_error("No numbers available");

    if (data.size() % 2 == 1)
      return *medianIt;
    else {
      auto nextIt = std::next(medianIt);
      return (*medianIt + *nextIt) / 2.0;
    }
  }

private:
  std::multiset<double> data;
  std::multiset<double>::iterator medianIt = data.end();
};

namespace {
struct TestRunner {
  int total = 0;
  int failed = 0;

  void expectNear(double got, double expected, double tol,
                  const std::string &label) {
    ++total;
    if (std::fabs(got - expected) <= tol) {
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
  static std::string toString(double value) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << value;
    return oss.str();
  }
};
} // namespace

// Test cases for correctness
void test() {
  std::vector<double> inputs = {5, 2, 3, 8, 1};
  // Expected medians after each insertion:
  // After 5 -> 5
  // After 2 -> (2,5) median = 3.5
  // After 3 -> Sorted: 2,3,5 -> median = 3
  // After 8 -> Sorted: 2,3,5,8 -> median = 4
  // After 1 -> Sorted: 1,2,3,5,8 -> median = 3
  std::vector<double> expectedMedians = {5, 3.5, 3, 4, 3};

  SimpleMedianCalculator simpleCalc;
  OptimalMedianCalculator optimalCalc;
  AlternativeMedianCalculator alternativeCalc;
  TestRunner runner;

  for (size_t i = 0; i < inputs.size(); ++i) {
    simpleCalc.insert(inputs[i]);
    optimalCalc.insert(inputs[i]);
    alternativeCalc.insert(inputs[i]);
    double m1 = simpleCalc.getMedian();
    double m2 = optimalCalc.getMedian();
    double m3 = alternativeCalc.getMedian();
    runner.expectNear(m1, expectedMedians[i], 1e-7,
                      "simple median step " + std::to_string(i + 1));
    runner.expectNear(m2, expectedMedians[i], 1e-7,
                      "optimal median step " + std::to_string(i + 1));
    runner.expectNear(m3, expectedMedians[i], 1e-7,
                      "alternative median step " + std::to_string(i + 1));
  }

  runner.summary();
}

int main() {
  test();
  return 0;
}
