/*
 * Task: Implement a stack that can return the minimum element in O(1) time.
 *
 * STACK WITH MINIMUM TRACKING
 *
 * Implement a template class `StackWithMin` which represents a stack data
 * structure capable of tracking the minimum element in constant time (O(1))
 * for all operations including push, pop, top, and retrieving the minimum
 * value.
 *
 * ASCII Illustration:
 *
 *      Stack: [ ... | encoded_value ]
 *                   ^
 *              min_value (current minimum)
 *
 * encoded value = 2 * value - min
 * some data on the underlying stack will be "fake" / encoded
 * when reading we need decode
 *
 * Example Input/Output:
 *
 *   Sequence of operations:
 *     push(10) -> min: 10, stack: [10]
 *     push(5)  -> min: 5,  stack: [10, (2*5 - 10)=0]
 *     push(2)  -> min: 2,  stack: [10, 0, (2*2 - 5)=-1]
 *     top()    -> returns: 2 (decoded from -1)
 *     pop()    -> removes 2, restores min to 5
 *
 *   Explanation:
 *     The algorithm encodes new minimum values to allow constant time retrieval
 * of both the top element and the minimum element after a pop operation.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <optional>
#include <stack>
#include <string>

// Template class for a stack that tracks the minimum element in O(1) time.
template <typename T> class StackWithMin {
public:
  void push(T value) {
    if (empty()) {
      data.push(value);
      _min = value;
    } else if (value < *_min) {
      data.push(2 * value - *_min);
      _min = value;
    } else {
      data.push(value);
    }
  }

  void pop() {
    if (empty()) {
      return;
    }
    T front = data.top();
    if (front < *_min) {
      _min = 2 * *_min - front;
    }
    data.pop();
    if (empty()) {
      _min.reset();
    }
  }

  std::optional<T> top() {
    if (empty()) {
      return std::nullopt;
    }
    T front = data.top();
    return (front < *_min) ? _min : front;
  }

  std::optional<T> min() { return _min; }

  bool empty() { return data.empty(); }

  size_t size() { return data.size(); }

private:
  std::stack<T> data;
  std::optional<T> _min;
};

namespace {
struct TestRunner {
  int total = 0;
  int failed = 0;

  template <typename T>
  void expectEqual(const std::optional<T> &got,
                   const std::optional<T> &expected, const std::string &label) {
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
  template <typename T>
  static std::string toString(const std::optional<T> &value) {
    if (!value.has_value())
      return "nullopt";
    return std::to_string(*value);
  }
};
} // namespace

// Test cases to ensure correctness of StackWithMin operations.
void test() {
  TestRunner runner;

  // 1) Empty stack behavior
  {
    StackWithMin<int> stack;
    runner.expectEqual(stack.min(), std::optional<int>{}, "min on empty");
    runner.expectEqual(stack.top(), std::optional<int>{}, "top on empty");

    // If pop() is supposed to be safe on empty, this should not crash.
    stack.pop();
    runner.expectEqual(stack.min(), std::optional<int>{},
                       "min still empty after pop on empty");
    runner.expectEqual(stack.top(), std::optional<int>{},
                       "top still empty after pop on empty");
  }

  // 2) Basic push/pop + popping all the way to empty
  {
    StackWithMin<int> stack;
    stack.push(10);
    stack.push(5);
    stack.push(2);
    runner.expectEqual(stack.min(), std::optional<int>(2), "min after push");
    runner.expectEqual(stack.top(), std::optional<int>(2), "top after push");

    stack.pop();
    runner.expectEqual(stack.min(), std::optional<int>(5), "min after pop");
    runner.expectEqual(stack.top(), std::optional<int>(5), "top after pop");

    stack.pop(); // removes 5
    runner.expectEqual(stack.min(), std::optional<int>(10),
                       "min after pop to single");
    runner.expectEqual(stack.top(), std::optional<int>(10),
                       "top after pop to single");

    stack.pop(); // removes 10 -> empty
    runner.expectEqual(stack.min(), std::optional<int>{},
                       "min after popping to empty");
    runner.expectEqual(stack.top(), std::optional<int>{},
                       "top after popping to empty");
  }

  // 3) Negative values + restore
  {
    StackWithMin<int> stack;
    stack.push(-1);
    stack.push(7);
    stack.push(-2);
    runner.expectEqual(stack.min(), std::optional<int>(-2),
                       "min with negative");

    stack.pop();
    runner.expectEqual(stack.min(), std::optional<int>(-1), "min restored");
    runner.expectEqual(stack.top(), std::optional<int>(7), "top restored");
  }

  // 4) Duplicate minimums (min should persist until ALL mins are popped)
  {
    StackWithMin<int> stack;
    stack.push(3);
    stack.push(1);
    stack.push(1);
    stack.push(2);

    runner.expectEqual(stack.min(), std::optional<int>(1),
                       "min with duplicates");
    runner.expectEqual(stack.top(), std::optional<int>(2),
                       "top with duplicates");

    stack.pop(); // pop 2
    runner.expectEqual(stack.min(), std::optional<int>(1),
                       "min after popping non-min");
    runner.expectEqual(stack.top(), std::optional<int>(1),
                       "top after popping non-min");

    stack.pop(); // pop 1 (still another 1 remains)
    runner.expectEqual(stack.min(), std::optional<int>(1),
                       "min remains after popping one duplicate min");
    runner.expectEqual(stack.top(), std::optional<int>(1),
                       "top now duplicate min");

    stack.pop(); // pop last 1, min should restore to 3
    runner.expectEqual(stack.min(), std::optional<int>(3),
                       "min restores after all duplicate mins removed");
    runner.expectEqual(stack.top(), std::optional<int>(3),
                       "top restores after all duplicate mins removed");
  }

  // 5) All equal values
  {
    StackWithMin<int> stack;
    stack.push(4);
    stack.push(4);
    stack.push(4);

    runner.expectEqual(stack.min(), std::optional<int>(4),
                       "min with all equal");
    runner.expectEqual(stack.top(), std::optional<int>(4),
                       "top with all equal");

    stack.pop();
    runner.expectEqual(stack.min(), std::optional<int>(4),
                       "min after pop with all equal");
    stack.pop();
    runner.expectEqual(stack.min(), std::optional<int>(4),
                       "min after second pop with all equal");
    stack.pop();
    runner.expectEqual(stack.min(), std::optional<int>{},
                       "min after popping all equal to empty");
  }

  // 6) Monotonic increasing: min should stay first element until empty
  {
    StackWithMin<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);

    runner.expectEqual(stack.min(), std::optional<int>(1),
                       "min in increasing sequence");
    stack.pop(); // 4
    runner.expectEqual(stack.min(), std::optional<int>(1),
                       "min after pop in increasing sequence");
    stack.pop(); // 3
    runner.expectEqual(stack.min(), std::optional<int>(1),
                       "min after second pop in increasing sequence");
  }

  // 7) Monotonic decreasing: min updates each push, restores each pop
  {
    StackWithMin<int> stack;
    stack.push(4);
    runner.expectEqual(stack.min(), std::optional<int>(4),
                       "min after push 4 (decreasing)");

    stack.push(3);
    runner.expectEqual(stack.min(), std::optional<int>(3),
                       "min after push 3 (decreasing)");

    stack.push(2);
    runner.expectEqual(stack.min(), std::optional<int>(2),
                       "min after push 2 (decreasing)");

    stack.push(1);
    runner.expectEqual(stack.min(), std::optional<int>(1),
                       "min after push 1 (decreasing)");

    stack.pop(); // 1
    runner.expectEqual(stack.min(), std::optional<int>(2),
                       "min restores to 2 after popping 1");
    stack.pop(); // 2
    runner.expectEqual(stack.min(), std::optional<int>(3),
                       "min restores to 3 after popping 2");
    stack.pop(); // 3
    runner.expectEqual(stack.min(), std::optional<int>(4),
                       "min restores to 4 after popping 3");
  }

  // 8) Longer deterministic sequence: validate min after every push and pop
  {
    StackWithMin<int> stack;

    // Push a sequence where the min changes a few times.
    // Values: 50, 49, ..., 26, 0, 25, 24, ..., 1
    int expectedMin = 1e9;
    for (int i = 50; i >= 26; --i) {
      stack.push(i);
      expectedMin = std::min(expectedMin, i);
      runner.expectEqual(stack.min(), std::optional<int>(expectedMin),
                         "min after push in long sequence (part 1)");
    }

    stack.push(0);
    expectedMin = 0;
    runner.expectEqual(stack.min(), std::optional<int>(0),
                       "min after pushing 0 in long sequence");

    for (int i = 25; i >= 1; --i) {
      stack.push(i);
      runner.expectEqual(stack.min(), std::optional<int>(0),
                         "min stays 0 in long sequence (part 2)");
    }

    // Now pop everything above 0; min should stay 0 until 0 is popped.
    for (int i = 1; i <= 25; ++i) {
      stack.pop();
      runner.expectEqual(stack.min(), std::optional<int>(0),
                         "min stays 0 while popping down to 0");
    }

    // Pop 0; min should restore to 26 (the smallest remaining from 26..50)
    stack.pop();
    runner.expectEqual(stack.min(), std::optional<int>(26),
                       "min restores after popping 0");

    // Pop remaining; min should climb upward as we remove 26,27,...
    for (int expected = 27; expected <= 50; ++expected) {
      stack.pop();
      runner.expectEqual(stack.min(),
                         (expected <= 50 ? std::optional<int>(expected)
                                         : std::optional<int>{}),
                         "min after popping in long sequence tail");
    }
    stack.pop();

    // After all popped, empty
    runner.expectEqual(stack.min(), std::optional<int>{},
                       "min empty at end of long sequence");
    runner.expectEqual(stack.top(), std::optional<int>{},
                       "top empty at end of long sequence");
  }

  runner.summary();
}

int main() {
  test();
  return 0;
}
