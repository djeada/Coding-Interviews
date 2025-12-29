/*
 * MAXIMUM ELEMENT IN A QUEUE (MAX QUEUE)
 *
 * This task involves implementing a data structure called MaxQueue that
 * supports the following operations:
 *   - push(x): Insert an integer x into the queue.
 *   - pop(): Remove the front element from the queue.
 *   - max(): Retrieve the maximum element currently in the queue.
 *
 * ASCII Illustration:
 *
 *   Operations:
 *      push(3) -> Queue: [3]       | max: 3
 *      push(1) -> Queue: [3,1]     | max: 3
 *      push(5) -> Queue: [3,1,5]   | max: 5
 *      pop()   -> Queue: [1,5]     | max: 5
 *
 * Example:
 *   Given the following sequence of operations:
 *     push 3, push 1, push 5, max, pop, max
 *   The expected output from the max() operations is:
 *     5, 5
 *
 *   Explanation:
 *     - After inserting 3, 1, and 5, the maximum element is 5.
 *     - After a pop operation (removing 3), the maximum remains 5.
 */

#include <cassert>
#include <deque>
#include <iostream>
#include <limits>
#include <optional>
#include <queue>
#include <set>
#include <vector>

// Simple (Brute-force) Solution
// Uses a deque for queue operations and scans the entire queue on each max()
// call. Complexity: O(n) for max() operation.
class SimpleMaxQueue {
public:
  void push(int x) { q.push_back(x); }

  void pop() {
    if (!q.empty()) {
      q.pop_front();
    }
  }

  int max() const {
    assert(!q.empty());
    int m = std::numeric_limits<int>::min();
    for (int x : q) {
      m = std::max(m, x);
    }
    return m;
  }

  bool empty() const { return q.empty(); }

private:
  std::deque<int> q;
};

// Optimal (Efficient) Solution
// Uses a normal queue (deque) along with an auxiliary deque to keep track of
// potential maximum values. Each operation is O(1) amortized.
class OptimalMaxQueue {
public:
  void push(int x) {
    q.push_back(x);
    // Remove elements smaller than x from the back of maxDeque.
    while (!maxDeque.empty() && maxDeque.back() < x) {
      maxDeque.pop_back();
    }
    maxDeque.push_back(x);
  }

  void pop() {
    if (q.empty())
      return;
    int frontVal = q.front();
    q.pop_front();
    if (frontVal == maxDeque.front()) {
      maxDeque.pop_front();
    }
  }

  int max() const {
    assert(!q.empty());
    return maxDeque.front();
  }

  bool empty() const { return q.empty(); }

private:
  std::deque<int> q;
  std::deque<int> maxDeque;
};

// Alternative (Educational) Solution
// Uses a deque for the queue and a multiset to keep elements in sorted order.
// Each push and pop operation requires updating the multiset, achieving O(log
// n) per operation.
class AlternativeMaxQueue {
public:
  void push(int x) {
    q.push_back(x);
    mset.insert(x);
  }

  void pop() {
    if (q.empty())
      return;
    int frontVal = q.front();
    q.pop_front();
    auto it = mset.find(frontVal);
    if (it != mset.end()) {
      mset.erase(it);
    }
  }

  int max() const {
    assert(!q.empty());
    return *mset.rbegin();
  }

  bool empty() const { return q.empty(); }

private:
  std::deque<int> q;
  std::multiset<int> mset;
};

// Test cases for correctness
void test() {
  // Simulate a series of operations:
  // push 3, push 1, push 5, max, pop, max
  std::vector<int> expected_max_values = {5, 5};

  // Test SimpleMaxQueue
  {
    SimpleMaxQueue mq;
    mq.push(3);
    mq.push(1);
    mq.push(5);
    int m1 = mq.max();
    mq.pop();
    int m2 = mq.max();
    assert(m1 == expected_max_values[0]);
    assert(m2 == expected_max_values[1]);
  }

  // Test OptimalMaxQueue
  {
    OptimalMaxQueue mq;
    mq.push(3);
    mq.push(1);
    mq.push(5);
    int m1 = mq.max();
    mq.pop();
    int m2 = mq.max();
    assert(m1 == expected_max_values[0]);
    assert(m2 == expected_max_values[1]);
  }

  // Test AlternativeMaxQueue
  {
    AlternativeMaxQueue mq;
    mq.push(3);
    mq.push(1);
    mq.push(5);
    int m1 = mq.max();
    mq.pop();
    int m2 = mq.max();
    assert(m1 == expected_max_values[0]);
    assert(m2 == expected_max_values[1]);
  }

  std::cout << "All tests passed!\n";
}

int main() {
  test();
  return 0;
}
