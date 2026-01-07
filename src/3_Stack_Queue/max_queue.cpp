/*
 * Task: Implement a queue that can return the current maximum in O(1) time.
 *
 * MAXIMUM ELEMENT IN A QUEUE (MAX QUEUE)
 *
 * Implement a data structure called MaxQueue that supports the following
 * operations:
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
#include <string>
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

namespace {
struct TestRunner {
  int total = 0;
  int failed = 0;

  void expectEqual(int got, int expected, const std::string &label) {
    ++total;
    if (got == expected) {
      std::cout << "[PASS] " << label << "\n";
      return;
    }
    ++failed;
    std::cout << "[FAIL] " << label << " expected=" << expected
              << " got=" << got << "\n";
  }

  void summary() const {
    std::cout << "Tests: " << total - failed << " passed, " << failed
              << " failed, " << total << " total\n";
  }
};
} // namespace

// Test cases for correctness
void test() {
  // Simulate a series of operations:
  // push 3, push 1, push 5, max, pop, max
  std::vector<int> expected_max_values = {5, 5};
  TestRunner runner;

  // Test SimpleMaxQueue
  {
    SimpleMaxQueue mq;
    mq.push(3);
    mq.push(1);
    mq.push(5);
    int m1 = mq.max();
    mq.pop();
    int m2 = mq.max();
    runner.expectEqual(m1, expected_max_values[0], "SimpleMaxQueue max #1");
    runner.expectEqual(m2, expected_max_values[1], "SimpleMaxQueue max #2");
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
    runner.expectEqual(m1, expected_max_values[0], "OptimalMaxQueue max #1");
    runner.expectEqual(m2, expected_max_values[1], "OptimalMaxQueue max #2");
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
    runner.expectEqual(m1, expected_max_values[0],
                       "AlternativeMaxQueue max #1");
    runner.expectEqual(m2, expected_max_values[1],
                       "AlternativeMaxQueue max #2");
  }

  runner.summary();
}

int main() {
  test();
  return 0;
}
