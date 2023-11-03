/**
 * This program defines a template class StackWithMin that represents a stack
 * data structure while keeping track of the minimum element. The implementation
 * ensures that all operations (push, pop, top, min) run in O(1) time.
 */

#include <cassert>
#include <iostream>
#include <optional>
#include <stack>

template <typename T> class StackWithMin {
public:
  StackWithMin() = default;
  ~StackWithMin() = default;

  void push(const T &value);
  void pop();
  std::optional<T> top() const;
  std::optional<T> min() const;
  bool empty() const;
  size_t size() const;

private:
  std::stack<T> data_;
  std::optional<T> min_value_;
};

template <typename T> void StackWithMin<T>::push(const T &value) {
  if (data_.empty()) {
    data_.push(value);
    min_value_ = value;
  } else if (value >= min_value_) {
    data_.push(value);
  } else {
    data_.push(2 * value - *min_value_);
    min_value_ = value;
  }
}

template <typename T> void StackWithMin<T>::pop() {
  assert(!data_.empty());
  if (data_.top() < *min_value_) {
    min_value_ = 2 * *min_value_ - data_.top();
  }
  data_.pop();
}

template <typename T> std::optional<T> StackWithMin<T>::min() const {
  return min_value_;
}

template <typename T> std::optional<T> StackWithMin<T>::top() const {
  if (data_.empty()) {
    return std::nullopt;
  }

  T top = data_.top();
  if (top < *min_value_) {
    return min_value_;
  }
  return top;
}

template <typename T> bool StackWithMin<T>::empty() const {
  return data_.empty();
}

template <typename T> size_t StackWithMin<T>::size() const {
  return data_.size();
}

void test1() {
  StackWithMin<int> stack;
  stack.push(10);
  stack.push(5);
  stack.push(2);

  assert(stack.min() == 2);
}

void test2() {
  StackWithMin<int> stack;
  stack.push(-1);
  stack.push(7);
  stack.push(-2);
  stack.pop();

  assert(stack.min() == -1);
}

int main() {
  test1();
  test2();
  std::cout << "All tests passed!\n";
  return 0;
}
