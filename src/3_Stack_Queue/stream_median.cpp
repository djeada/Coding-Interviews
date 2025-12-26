/*
 * DYNAMIC MEDIAN CALCULATION OF A NUMBER STREAM
 *
 * This program demonstrates three approaches for dynamically computing the
 * median of a stream of numbers as new elements are inserted:
 *
 * 1. Simple Solution:
 *    Uses a sorted vector to store numbers. Every insertion sorts the vector
 *    so that retrieving the median is straightforward. This approach is easy to
 *    implement but becomes inefficient with a large number of insertions.
 *    Complexity: O(n log n) per insertion.
 *
 * 2. Optimal Solution:
 *    Uses two heaps (a max-heap for the lower half and a min-heap for the upper
 * half) to maintain balance and enable efficient median retrieval. Complexity:
 * O(log n) per insertion and O(1) median retrieval.
 *
 * 3. Alternative (Educational) Solution:
 *    Utilizes a balanced multiset with an iterator tracking the median. This
 * approach allows logarithmic insertion and direct access to the median,
 * showcasing another way to maintain order dynamically.
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
#include <cassert>
#include <cmath>
#include <exception>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

// Simple (Brute-force) Solution
// Stores numbers in a vector and sorts on each insertion.
// Complexity: O(n log n) per insertion.
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
// Uses two heaps: a max-heap for the lower half and a min-heap for the upper
// half. Complexity: O(log n) per insertion, O(1) median retrieval.
class OptimalMedianCalculator {
public:
  void insert(double num) {
    if (minHeap.empty() || num >= minHeap.top()) {
      minHeap.push(num);
    } else {
      maxHeap.push(num);
    }

    // Balance the heaps to ensure the size difference is not more than 1.
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
  std::priority_queue<double> maxHeap; // Default is max-heap.
};

// Alternative (Educational) Solution
// Uses a multiset to maintain sorted order with logarithmic insertions
// and an iterator to track the median position.
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
        if (data.size() % 2 == 0) { // even -> odd: move iterator left.
          --medianIt;
        }
      } else {
        if (data.size() % 2 == 1) { // odd -> even: move iterator right.
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

  for (size_t i = 0; i < inputs.size(); ++i) {
    simpleCalc.insert(inputs[i]);
    optimalCalc.insert(inputs[i]);
    alternativeCalc.insert(inputs[i]);
    double m1 = simpleCalc.getMedian();
    double m2 = optimalCalc.getMedian();
    double m3 = alternativeCalc.getMedian();
    assert(std::fabs(m1 - expectedMedians[i]) < 1e-7);
    assert(std::fabs(m2 - expectedMedians[i]) < 1e-7);
    assert(std::fabs(m3 - expectedMedians[i]) < 1e-7);
  }

  std::cout << "All tests passed!\n";
}

int main() {
  test();
  return 0;
}
