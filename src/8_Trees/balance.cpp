/*
 * Task: Check whether a binary tree is height-balanced.
 *
 * BALANCED BINARY TREE
 *
 * Problem:
 * Given the root of a binary tree, determine whether the tree is height
 * balanced. A tree is balanced if for every node, the heights of the left and
 * right subtrees differ by at most 1.
 *
 * Constraints:
 * - 0 <= number of nodes <= 10^5
 * - Node values are 32-bit signed integers.
 *
 * Example:
 * Input: root = [4,2,6,1,3,5,7]
 * Output: true
 */

#include "binary_tree.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

// TreeWithBalanceCheck extends the assumed BinaryTree from "binary_tree.h" with
// balance-checking methods.
class TreeWithBalanceCheck : public BinaryTree {
public:
  // Simple (Brute-force) Solution: O(n^2) worst-case.
  bool isBalancedSimple() const { return isBalancedSimple(root); }

  // Optimal (Efficient) Solution: O(n) time complexity.
  bool isBalancedOptimal() const {
    int depth = 0;
    return isBalancedOptimal(root, depth);
  }

private:
  // Computes the depth of a subtree.
  int depth(const std::unique_ptr<Node> &node) const {
    if (!node)
      return 0;
    return std::max(depth(node->left), depth(node->right)) + 1;
  }

  // Recursive function for the simple balance check.
  bool isBalancedSimple(const std::unique_ptr<Node> &node) const {
    if (!node)
      return true;
    int leftDepth = depth(node->left);
    int rightDepth = depth(node->right);
    if (std::abs(leftDepth - rightDepth) > 1)
      return false;
    return isBalancedSimple(node->left) && isBalancedSimple(node->right);
  }

  // Recursive function for the optimal balance check that calculates depth on
  // the fly.
  bool isBalancedOptimal(const std::unique_ptr<Node> &node,
                         int &currentDepth) const {
    if (!node) {
      currentDepth = 0;
      return true;
    }
    int leftDepth = 0, rightDepth = 0;
    if (!isBalancedOptimal(node->left, leftDepth) ||
        !isBalancedOptimal(node->right, rightDepth))
      return false;
    if (std::abs(leftDepth - rightDepth) > 1)
      return false;
    currentDepth = std::max(leftDepth, rightDepth) + 1;
    return true;
  }
};

int main() {
  int total = 0;
  int failed = 0;

  auto expectEqual = [&](bool got, bool expected, const std::string &label) {
    ++total;
    if (got == expected) {
      std::cout << "[PASS] " << label << "\n";
      return;
    }
    ++failed;
    std::cout << "[FAIL] " << label << " expected=" << std::boolalpha
              << expected << " got=" << got << "\n";
  };

  auto summary = [&]() {
    std::cout << "Tests: " << total - failed << " passed, " << failed
              << " failed, " << total << " total\n";
  };

  // Test Case 1: Balanced tree with nodes [4, 6, 2, 3, 1, 5, 7]
  {
    TreeWithBalanceCheck tree;
    int values[] = {4, 6, 2, 3, 1, 5, 7};
    for (int v : values)
      tree.add(v);
    expectEqual(tree.isBalancedSimple(), true, "simple balanced #1");
    expectEqual(tree.isBalancedOptimal(), true, "optimal balanced #1");
  }

  // Test Case 2: Minimal balanced tree [2, 1, 3]
  {
    TreeWithBalanceCheck tree;
    int values[] = {2, 1, 3};
    for (int v : values)
      tree.add(v);
    expectEqual(tree.isBalancedSimple(), true, "simple balanced #2");
    expectEqual(tree.isBalancedOptimal(), true, "optimal balanced #2");
  }

  // Test Case 3: Unbalanced tree (ascending order) [1, 2, 3, 4, 5]
  {
    TreeWithBalanceCheck tree;
    int values[] = {1, 2, 3, 4, 5};
    for (int v : values)
      tree.add(v);
    expectEqual(tree.isBalancedSimple(), false, "simple unbalanced #1");
    expectEqual(tree.isBalancedOptimal(), false, "optimal unbalanced #1");
  }

  // Test Case 4: Unbalanced tree (descending order) [5, 4, 3, 2, 1]
  {
    TreeWithBalanceCheck tree;
    int values[] = {5, 4, 3, 2, 1};
    for (int v : values)
      tree.add(v);
    expectEqual(tree.isBalancedSimple(), false, "simple unbalanced #2");
    expectEqual(tree.isBalancedOptimal(), false, "optimal unbalanced #2");
  }
  summary();
  return 0;
}
