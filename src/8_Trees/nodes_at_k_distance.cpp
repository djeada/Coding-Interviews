/*
 * Task: Find all nodes at distance k from the root in a binary tree.
 *
 * FIND NODES AT K DISTANCE FROM ROOT IN A BINARY TREE
 *
 * Extend an assumed BinaryTree implementation (from "binary_tree.h") by
 * adding functionality to find all nodes that are exactly K edges away from
 * the root.
 *
 * The algorithm uses a recursive helper function that traverses the tree,
 * decrementing the distance until it reaches zero. When the distance is zero,
 * the node's value is added to the result.
 *
 * ASCII Illustration:
 *             9
 *            / \
 *           8   13
 *          /   /  \
 *         4   10  16
 *          \
 *           7        <- Node at distance 3
 *                \
 *                15     <- Node at distance 3
 *
 * Example Input/Output:
 * Input: Tree built by inserting values {9, 8, 13, 4, 10, 16, 7, 15} and k = 3.
 * Output: Nodes at distance 3 are [7, 15].
 *
 * Explanation:
 * Starting from the root (distance 0), the algorithm recursively explores the
 * tree, reducing the distance by one at each level. When the distance becomes
 * zero, the current node is part of the result.
 */

#include "binary_tree.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class TreeWithKDistanceNodes : public BinaryTree {
public:
  TreeWithKDistanceNodes() : BinaryTree() {}

  // Returns a vector containing the values of all nodes at distance k from the
  // root.
  std::vector<int> findNodesAtDistance(unsigned int k) const {
    std::vector<int> result;
    findNodesAtDistanceFromNode(root.get(), k, result);
    return result;
  }

private:
  // Recursive helper function to collect nodes at a given distance from the
  // current node.
  void findNodesAtDistanceFromNode(const Node *node, int distance,
                                   std::vector<int> &result) const {
    if (!node || distance < 0) {
      return;
    }

    if (distance == 0) {
      result.push_back(node->value);
      return;
    }

    findNodesAtDistanceFromNode(node->left.get(), distance - 1, result);
    findNodesAtDistanceFromNode(node->right.get(), distance - 1, result);
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

void runTests() {
  TestRunner runner;
  {
    TreeWithKDistanceNodes tree;
    for (const auto &value : {9, 8, 13, 4, 10, 16, 7, 15})
      tree.add(value);
    const auto result = tree.findNodesAtDistance(3);
    runner.expectEqual(result, std::vector<int>{7, 15}, "distance 3");
  }

  {
    TreeWithKDistanceNodes tree;
    for (const auto &value : {5, 4, 3, 2, 1})
      tree.add(value);
    const auto result = tree.findNodesAtDistance(4);
    runner.expectEqual(result, std::vector<int>{1}, "distance 4 left-skewed");
  }

  {
    TreeWithKDistanceNodes tree;
    for (const auto &value : {1, 2, 3, 4, 5})
      tree.add(value);
    const auto result = tree.findNodesAtDistance(4);
    runner.expectEqual(result, std::vector<int>{5}, "distance 4 right-skewed");
  }

  {
    TreeWithKDistanceNodes tree;
    tree.add(1);
    const auto result = tree.findNodesAtDistance(1);
    runner.expectEqual(result, std::vector<int>{}, "distance beyond depth");
  }
  runner.summary();
}

int main() {
  runTests();
  return 0;
}
