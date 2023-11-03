/**
 * This program checks if a given sequence of numbers can be a valid popping
 * order from a stack given a specific pushing order.
 */

#include <cassert>
#include <iostream>
#include <stack>
#include <vector>

bool isValidPopOrder(const std::vector<int> &push_order,
                     const std::vector<int> &pop_order) {
  if (push_order.empty() || pop_order.empty() ||
      push_order.size() != pop_order.size()) {
    return false;
  }

  std::stack<int> stack;
  size_t push_idx = 0;
  size_t pop_idx = 0;

  while (pop_idx < pop_order.size()) {
    // Push elements to the stack until the top of the stack matches the current
    // element in pop_order
    while (stack.empty() || stack.top() != pop_order[pop_idx]) {
      if (push_idx == push_order.size()) {
        break;
      }
      stack.push(push_order[push_idx++]);
    }

    // If we couldn't find the element in pop_order
    if (stack.top() != pop_order[pop_idx]) {
      return false;
    }

    stack.pop();
    pop_idx++;
  }

  return stack.empty();
}

void test1() {
  std::vector<int> push_order{1, 2, 3, 4, 5};
  std::vector<int> pop_order{4, 5, 3, 2, 1};
  assert(isValidPopOrder(push_order, pop_order));
}

void test2() {
  std::vector<int> push_order{1, 2, 3, 4, 5};
  std::vector<int> pop_order{3, 5, 4, 2, 1};
  assert(isValidPopOrder(push_order, pop_order));
}

void test3() {
  std::vector<int> push_order{1, 2, 3, 4, 5};
  std::vector<int> pop_order{4, 3, 5, 1, 2};
  assert(!isValidPopOrder(push_order, pop_order));
}

void test4() {
  std::vector<int> push_order{1, 2, 3, 4, 5};
  std::vector<int> pop_order{3, 5, 4, 1, 2};
  assert(!isValidPopOrder(push_order, pop_order));
}

int main() {
  test1();
  test2();
  test3();
  test4();

  std::cout << "All tests passed!\n";
  return 0;
}
