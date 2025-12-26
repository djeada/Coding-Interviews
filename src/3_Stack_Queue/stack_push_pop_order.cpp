/*
 * VALID STACK POPPING ORDER VERIFICATION
 *
 * This program checks if a given sequence of numbers can be a valid popping
 * order from a stack given a specific pushing order.
 *
 * Two solutions are provided:
 *
 * 1. Simulation Solution:
 *    This approach simulates the process of pushing and popping. It pushes
 * numbers from the given push order onto a stack until the top matches the
 * current number in the pop order. If the entire pop order can be reproduced
 * this way, the sequence is valid. Complexity: O(n) where n is the length of
 * the sequence.
 *
 * 2. Alternative Recursive (Educational) Solution:
 *    This method recursively explores both possible operations (push and pop)
 * to generate all possible pop orders from the given push order, then checks if
 * the target pop order is among them. Complexity: Exponential (O(2^n)) and
 * suitable only for small input sizes.
 *
 * ASCII Illustration:
 *
 *     Push Order:  1  2  3  4  5
 *                    |  |  |  |  |
 *                   [Stack Simulation]
 *                    |  |  |  |  |
 *     Example Valid Pop Order: 4 5 3 2 1
 *
 * Example:
 *   Push Order: [1, 2, 3, 4, 5]
 *   Pop Order:  [4, 5, 3, 2, 1]
 *   Output: Valid (true)
 *
 *   Explanation:
 *     The simulation pushes elements until the top of the stack matches the
 * next element in the pop order. If the entire pop order is processed and the
 * stack is empty, the sequence is valid.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stack>
#include <vector>

// Simulation Solution: Efficient O(n) approach.
bool isValidPopOrderSimulation(const std::vector<int> &push_order,
                               const std::vector<int> &pop_order) {
  if (push_order.empty() || pop_order.empty() ||
      push_order.size() != pop_order.size()) {
    return false;
  }

  std::stack<int> s;
  size_t push_index = 0;
  for (int pop_value : pop_order) {
    // Push elements until the stack's top equals pop_value.
    while (s.empty() || s.top() != pop_value) {
      if (push_index == push_order.size()) {
        break;
      }
      s.push(push_order[push_index++]);
    }
    if (s.top() != pop_value) {
      return false;
    }
    s.pop();
  }
  return s.empty();
}

// Alternative Recursive (Educational) Solution:
// Recursively generate all valid pop orders from push_order and check if target
// exists.
void generatePopOrders(const std::vector<int> &push_order, size_t push_index,
                       std::stack<int> &s, std::vector<int> &current,
                       std::vector<std::vector<int>> &all_orders) {
  if (push_index == push_order.size() && s.empty()) {
    all_orders.push_back(current);
    return;
  }

  // Option 1: Push the next element if available.
  if (push_index < push_order.size()) {
    s.push(push_order[push_index]);
    generatePopOrders(push_order, push_index + 1, s, current, all_orders);
    s.pop();
  }

  // Option 2: Pop from the stack if not empty.
  if (!s.empty()) {
    int top_val = s.top();
    s.pop();
    current.push_back(top_val);
    generatePopOrders(push_order, push_index, s, current, all_orders);
    current.pop_back();
    s.push(top_val);
  }
}

bool isValidPopOrderRecursive(const std::vector<int> &push_order,
                              const std::vector<int> &pop_order) {
  if (push_order.empty() || pop_order.empty() ||
      push_order.size() != pop_order.size()) {
    return false;
  }

  std::vector<std::vector<int>> all_orders;
  std::vector<int> current;
  std::stack<int> s;
  generatePopOrders(push_order, 0, s, current, all_orders);

  // Check if pop_order is among the generated orders.
  for (const auto &order : all_orders) {
    if (order == pop_order) {
      return true;
    }
  }
  return false;
}

// Test cases to verify both solutions.
void test() {
  std::vector<int> push_order = {1, 2, 3, 4, 5};
  std::vector<int> pop_order1 = {4, 5, 3, 2, 1};
  std::vector<int> pop_order2 = {3, 5, 4, 2, 1};
  std::vector<int> pop_order3 = {4, 3, 5, 1, 2};
  std::vector<int> pop_order4 = {3, 5, 4, 1, 2};

  // Testing Simulation Solution.
  assert(isValidPopOrderSimulation(push_order, pop_order1) == true);
  assert(isValidPopOrderSimulation(push_order, pop_order2) == true);
  assert(isValidPopOrderSimulation(push_order, pop_order3) == false);
  assert(isValidPopOrderSimulation(push_order, pop_order4) == false);

  // Testing Recursive (Educational) Solution on small input.
  // Note: The recursive solution is computationally expensive for large n.
  assert(isValidPopOrderRecursive(push_order, pop_order1) == true);
  assert(isValidPopOrderRecursive(push_order, pop_order2) == true);
  assert(isValidPopOrderRecursive(push_order, pop_order3) == false);
  assert(isValidPopOrderRecursive(push_order, pop_order4) == false);

  std::cout << "All tests passed!\n";
}

int main() {
  test();
  return 0;
}
