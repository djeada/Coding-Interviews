/*
 * Task: Determine whether a pop sequence is valid for a given push sequence.
 *
 * VALID STACK POPPING ORDER VERIFICATION
 *
 * Given two sequences, check if the pop sequence can be produced by a stack
 * when elements are pushed in the given order.
 *
 * ASCII Illustration:
 *
 *     Push Order:              1  2  3  4  5
 *                              |  |  |  |  |
 *                             [Stack Simulation]
 *                              |   |  |  |  |
 *     Example Valid Pop Order: 4   5  3  2  1
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
#include <iostream>
#include <stack>
#include <string>
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
    if (s.empty() || s.top() != pop_value) {
      return false;
    }
    s.pop();
  }
  return s.empty();
}

// Alternative Recursive (Educational) Solution:
// Recursively generate all valid pop orders from push_order and check if target
// exists.
// Time Complexity:
// - Generating all valid stack pop permutations takes O(Cn) where Cn is the
//   nth Catalan number (approximately O(4^n / n^(3/2))).
// - Comparing each generated sequence with pop_order costs O(n).
// - Overall time complexity: O(Cn * n), which is exponential.
//
// Space Complexity:
// - O(Cn * n) to store all valid pop orders.
// - O(n) additional space for recursion stack and auxiliary stack.
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

namespace {
struct TestRunner {
  int total = 0;
  int failed = 0;

  void expectEqual(bool got, bool expected, const std::string &label) {
    ++total;
    if (got == expected) {
      std::cout << "[PASS] " << label << "\n";
      return;
    }
    ++failed;
    std::cout << "[FAIL] " << label << " expected=" << std::boolalpha
              << expected << " got=" << got << "\n";
  }

  void summary() const {
    std::cout << "Tests: " << total - failed << " passed, " << failed
              << " failed, " << total << " total\n";
  }
};
} // namespace

// Test cases to verify both solutions.
void test() {
  std::vector<int> push_order = {1, 2, 3, 4, 5};
  std::vector<int> pop_order1 = {4, 5, 3, 2, 1};
  std::vector<int> pop_order2 = {3, 5, 4, 2, 1};
  std::vector<int> pop_order3 = {4, 3, 5, 1, 2};
  std::vector<int> pop_order4 = {3, 5, 4, 1, 2};
  TestRunner runner;

  // Testing Simulation Solution.
  runner.expectEqual(isValidPopOrderSimulation(push_order, pop_order1), true,
                     "simulation valid #1");
  runner.expectEqual(isValidPopOrderSimulation(push_order, pop_order2), true,
                     "simulation valid #2");
  runner.expectEqual(isValidPopOrderSimulation(push_order, pop_order3), false,
                     "simulation invalid #1");
  runner.expectEqual(isValidPopOrderSimulation(push_order, pop_order4), false,
                     "simulation invalid #2");

  // Testing Recursive (Educational) Solution on small input.
  // Note: The recursive solution is computationally expensive for large n.
  runner.expectEqual(isValidPopOrderRecursive(push_order, pop_order1), true,
                     "recursive valid #1");
  runner.expectEqual(isValidPopOrderRecursive(push_order, pop_order2), true,
                     "recursive valid #2");
  runner.expectEqual(isValidPopOrderRecursive(push_order, pop_order3), false,
                     "recursive invalid #1");
  runner.expectEqual(isValidPopOrderRecursive(push_order, pop_order4), false,
                     "recursive invalid #2");

  runner.summary();
}

int main() {
  test();
  return 0;
}
