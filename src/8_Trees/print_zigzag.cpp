/*
 * Task: Print a binary tree in zigzag (spiral) level order.
 *
 * ZIGZAG (SPIRAL) LEVEL ORDER TRAVERSAL
 *
 * Extend an assumed BinaryTree implementation (from "binary_tree.h") by
 * adding functionality to print the tree in a zigzag (spiral) level order.
 * This means that the nodes at each level are printed alternately from
 * left-to-right and right-to-left.
 *
 * Approach:
 *   - Use two stacks to alternate between levels.
 *   - For the current level, push the child nodes into the alternate stack in
 * an order that ensures the next level is printed in the opposite direction.
 *
 * ASCII Illustration:
 *           10
 *          /  \
 *         5    12
 *             /  \
 *           11    16
 *
 * Example Output:
 * For the tree built by inserting {10, 5, 12, 11, 16}, the printed output might
 * be: 10 12 5 11 16
 *
 * Explanation:
 * The first level is printed left-to-right (just the root), the second level is
 * printed right-to-left, and the process alternates for subsequent levels.
 */

#include "binary_tree.h"
#include <algorithm> // For std::swap
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

class TreeWithZigZagPrint : public BinaryTree {
public:
  TreeWithZigZagPrint() : BinaryTree() {}

  // Prints the tree in zigzag (spiral) level order.
  void print() const {
    const auto values = collectZigZagOrder();
    if (values.empty()) {
      std::cout << "Tree is empty." << std::endl;
      return;
    }
    for (int value : values)
      std::cout << value << ' ';
    std::cout << std::endl;
  }

  std::vector<int> collectZigZagOrder() const {
    std::vector<int> result;
    if (!root)
      return result;

    // Use two stacks to store nodes of current level and next level.
    std::vector<std::stack<const Node *>> levels(2);
    int current = 0;
    int next = 1;

    levels[current].push(root.get());

    while (!levels[0].empty() || !levels[1].empty()) {
      const Node *currentNode = levels[current].top();
      levels[current].pop();

      result.push_back(currentNode->value);

      if (current == 0) {
        // For left-to-right, push left child first then right child.
        if (currentNode->left)
          levels[next].push(currentNode->left.get());
        if (currentNode->right)
          levels[next].push(currentNode->right.get());
      } else {
        // For right-to-left, push right child first then left child.
        if (currentNode->right)
          levels[next].push(currentNode->right.get());
        if (currentNode->left)
          levels[next].push(currentNode->left.get());
      }

      if (levels[current].empty()) {
        std::swap(current, next);
      }
    }
    return result;
  }
};

namespace {
struct TestRunner {
  int total = 0;
  int failed = 0;

  void expectEqual(const std::vector<int> &got,
                   const std::vector<int> &expected, const std::string &label) {
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
  static std::string toString(const std::vector<int> &values) {
    std::ostringstream oss;
    oss << "{";
    for (size_t i = 0; i < values.size(); ++i) {
      if (i > 0)
        oss << ", ";
      oss << values[i];
    }
    oss << "}";
    return oss.str();
  }
};
} // namespace

int main() {
  TestRunner runner;
  TreeWithZigZagPrint tree;
  for (const auto &value : {10, 5, 12, 11, 16}) {
    tree.add(value);
  }

  runner.expectEqual(tree.collectZigZagOrder(),
                     std::vector<int>{10, 12, 5, 11, 16}, "zigzag order");
  runner.summary();
  tree.print();

  return 0;
}
