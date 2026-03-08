/*
 * Task: Print a binary tree in level-order (breadth-first) traversal.
 *
 * BINARY TREE LEVEL ORDER TRAVERSAL
 *
 * Problem:
 * Given the root of a binary tree, output the node values in level-order
 * (breadth-first) from left to right.
 *
 * Constraints:
 * - 0 <= number of nodes <= 10^5
 * - Node values are 32-bit signed integers.
 *
 * Example:
 * Input: root built from [10,5,12,11,16]
 * Output: [10,5,12,11,16]
 */

#include "binary_tree.h"
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

class TreeWithBreadthFirstPrint : public BinaryTree {
public:
  TreeWithBreadthFirstPrint() : BinaryTree() {}

  // Prints the tree in a breadth-first order.
  void print() const {
    const auto values = collectLevelOrder();
    if (values.empty()) {
      std::cout << "Tree is empty." << std::endl;
      return;
    }
    for (int value : values)
      std::cout << value << ' ';
    std::cout << std::endl;
  }

  std::vector<int> collectLevelOrder() const {
    std::vector<int> result;
    if (!root)
      return result;

    std::queue<const Node *> nodesToPrint;
    nodesToPrint.push(root.get());

    while (!nodesToPrint.empty()) {
      const auto *currentNode = nodesToPrint.front();
      nodesToPrint.pop();

      result.push_back(currentNode->value);

      if (currentNode->left) {
        nodesToPrint.push(currentNode->left.get());
      }
      if (currentNode->right) {
        nodesToPrint.push(currentNode->right.get());
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

  TreeWithBreadthFirstPrint tree;
  for (const auto &value : {10, 5, 12, 11, 16}) {
    tree.add(value);
  }

  expectEqual(tree.collectLevelOrder(),
              std::vector<int>{10, 5, 12, 11, 16}, "level order");
  summary();
  tree.print();

  return 0;
}
