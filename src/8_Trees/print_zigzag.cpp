/*
 * Task: Print a binary tree in zigzag (spiral) level order.
 *
 * BINARY TREE ZIGZAG LEVEL ORDER TRAVERSAL
 *
 * Problem:
 * Given the root of a binary tree, output node values level by level while
 * alternating direction each level (left-to-right, then right-to-left).
 *
 * Constraints:
 * - 0 <= number of nodes <= 10^5
 * - Node values are 32-bit signed integers.
 *
 * Example:
 * Input: root built from [10,5,12,11,16]
 * Output: [10,12,5,11,16]
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

int main() {
  int total = 0;
  int failed = 0;

  auto toString = [](const std::vector<int> &values) {
    std::ostringstream oss;
    oss << "{";
    for (size_t i = 0; i < values.size(); ++i) {
      if (i > 0)
        oss << ", ";
      oss << values[i];
    }
    oss << "}";
    return oss.str();
  };

  auto expectEqual = [&](const std::vector<int> &got,
                         const std::vector<int> &expected,
                         const std::string &label) {
    ++total;
    if (got == expected) {
      std::cout << "[PASS] " << label << "\n";
      return;
    }
    ++failed;
    std::cout << "[FAIL] " << label << " expected=" << toString(expected)
              << " got=" << toString(got) << "\n";
  };

  auto summary = [&]() {
    std::cout << "Tests: " << total - failed << " passed, " << failed
              << " failed, " << total << " total\n";
  };

  TreeWithZigZagPrint tree;
  for (const auto &value : {10, 5, 12, 11, 16}) {
    tree.add(value);
  }

  expectEqual(tree.collectZigZagOrder(),
              std::vector<int>{10, 12, 5, 11, 16}, "zigzag order");
  summary();
  tree.print();

  return 0;
}
