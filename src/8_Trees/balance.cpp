/*
 * BINARY TREE BALANCE CHECK
 *
 * This program demonstrates two modern C++ solutions to check whether a binary
 * search tree is balanced. A binary tree is considered balanced if, for every
 * node, the difference in height between its left and right subtrees is no more
 * than one.
 *
 * Two approaches are implemented:
 * 1. Simple (Brute-force) Approach:
 *    - For each node, recursively compute the depths of its left and right
 * subtrees and check the difference.
 *    - This solution is easy to implement but can be inefficient (O(n^2) in the
 * worst case) because depth is computed repeatedly for the same nodes.
 *
 * 2. Optimal (Efficient) Approach:
 *    - Combine the depth calculation and balance checking in a single recursive
 * function.
 *    - This approach improves performance to O(n) by avoiding redundant
 * computations.
 *
 * ASCII Illustration:
 *           4
 *          / \
 *         2   6
 *        / \ / \
 *       1  3 5  7
 *
 * Example Input/Output:
 * Input: Insert values [4, 6, 2, 3, 1, 5, 7] into the tree.
 * Output: The tree is balanced.
 *
 * Explanation: Each node's left and right subtree depths differ by no more
 * than 1.
 */

#include "binary_tree.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

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

// Test cases to ensure both implementations produce the same results.
void test() {
  // Test Case 1: Balanced tree with nodes [4, 6, 2, 3, 1, 5, 7]
  {
    TreeWithBalanceCheck tree;
    int values[] = {4, 6, 2, 3, 1, 5, 7};
    for (int v : values)
      tree.add(v);
    assert(tree.isBalancedSimple());
    assert(tree.isBalancedOptimal());
  }

  // Test Case 2: Minimal balanced tree [2, 1, 3]
  {
    TreeWithBalanceCheck tree;
    int values[] = {2, 1, 3};
    for (int v : values)
      tree.add(v);
    assert(tree.isBalancedSimple());
    assert(tree.isBalancedOptimal());
  }

  // Test Case 3: Unbalanced tree (ascending order) [1, 2, 3, 4, 5]
  {
    TreeWithBalanceCheck tree;
    int values[] = {1, 2, 3, 4, 5};
    for (int v : values)
      tree.add(v);
    assert(!tree.isBalancedSimple());
    assert(!tree.isBalancedOptimal());
  }

  // Test Case 4: Unbalanced tree (descending order) [5, 4, 3, 2, 1]
  {
    TreeWithBalanceCheck tree;
    int values[] = {5, 4, 3, 2, 1};
    for (int v : values)
      tree.add(v);
    assert(!tree.isBalancedSimple());
    assert(!tree.isBalancedOptimal());
  }

  std::cout << "All tests passed!\n";
}

int main() {
  test();
  return 0;
}
