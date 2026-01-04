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
 * The implementation uses a modified stack mechanism where the pushed value is
 * encoded if it is less than the current minimum. This ensures that when an
 * element is popped, the previous minimum can be restored in constant time.
 *
 * ASCII Illustration:
 *
 *      Stack: [ ... | encoded_value ]
 *                   ^
 *              min_value (current minimum)
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

#include <iostream>
#include <optional>
#include <stack>
#include <string>

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

// Template class for a stack that tracks the minimum element in O(1) time.
template <typename T> class StackWithMin {
public:
  StackWithMin() = default;
  ~StackWithMin() = default;

  void push(const T &value) {
    if (data_.empty()) {
      data_.push(value);
      min_value_ = value;
    } else if (value >= *min_value_) {
      data_.push(value);
    } else {
      // Encode the new minimum value.
      data_.push(2 * value - *min_value_);
      min_value_ = value;
    }
  }

  void pop() {
    assert(!data_.empty());
    T top_val = data_.top();
    if (top_val < *min_value_) {
      // Restore the previous minimum.
      min_value_ = 2 * *min_value_ - top_val;
    }
    data_.pop();
  }

  std::optional<T> top() const {
    if (data_.empty()) {
      return std::nullopt;
    }
    T top_val = data_.top();
    return (top_val < *min_value_) ? *min_value_ : top_val;
  }

  std::optional<T> min() const { return min_value_; }

  bool empty() const { return data_.empty(); }

  size_t size() const { return data_.size(); }

private:
  std::stack<T> data_;
  std::optional<T> min_value_;
};

// Test cases to ensure correctness of StackWithMin operations.
void test() {
  TestRunner runner;
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
  }
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
  runner.summary();
}

int main() {
  test();
  return 0;
}
