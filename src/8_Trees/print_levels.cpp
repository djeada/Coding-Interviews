/*
 * Task: Print a binary tree in level-order (breadth-first) traversal.
 *
 * BREADTH-FIRST PRINT (LEVEL ORDER TRAVERSAL)
 *
 * Extend an assumed BinaryTree implementation (from "binary_tree.h") by
 * adding functionality to print the tree in a breadth-first (level order)
 * manner.
 *
 * The algorithm uses a queue to traverse the tree level by level:
 *   - Start from the root node and push it into the queue.
 *   - While the queue is not empty, remove the front node, print its value, and
 * enqueue its children.
 *
 * ASCII Illustration:
 *           10
 *          /  \
 *         5    12
 *             /  \
 *           11    16
 *
 * Example Output:
 * For the tree built by inserting {10, 5, 12, 11, 16}, the printed output will
 * be: 10 5 12 11 16
 *
 * Explanation:
 * The nodes are printed level by level from left to right.
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
  TreeWithBreadthFirstPrint tree;
  for (const auto &value : {10, 5, 12, 11, 16}) {
    tree.add(value);
  }

  runner.expectEqual(tree.collectLevelOrder(),
                     std::vector<int>{10, 5, 12, 11, 16}, "level order");
  runner.summary();
  tree.print();

  return 0;
}
