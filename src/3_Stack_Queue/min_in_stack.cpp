#include <cassert>
#include <stack>

template <typename T> class StackWithMin {
public:
  StackWithMin(void) {}
  virtual ~StackWithMin(void) {}

  T &top(void);
  const T &top(void) const;

  void push(const T &value);
  void pop(void);

  const T &min(void) const;

  bool empty() const;
  size_t size() const;

private:
  std::stack<T> data;
  T min_value;
};

template <typename T> void StackWithMin<T>::push(const T &value) {
  if (data.size() == 0) {
    data.push(value);
    min_value = value;
  } else if (value >= min_value) {
    data.push(value);
  } else {
    data.push(2 * value - min_value);
    min_value = value;
  }
}

template <typename T> void StackWithMin<T>::pop() {
  assert(data.size() > 0);

  if (data.top() < min_value)
    min_value = 2 * min_value - data.top();

  data.pop();
}

template <typename T> const T &StackWithMin<T>::min() const {
  assert(data.size() > 0);

  return min_value;
}

template <typename T> T &StackWithMin<T>::top() {
  T top = data.top();
  if (top < min_value)
    top = min_value;

  return top;
}

template <typename T> const T &StackWithMin<T>::top() const {
  T top = data.top();
  if (top < min_value)
    top = min_value;

  return top;
}

template <typename T> bool StackWithMin<T>::empty() const {
  return data.empty();
}

template <typename T> size_t StackWithMin<T>::size() const {
  return data.size();
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
  return 0;
}
