/*
 * LOWEST COMMON ANCESTOR IN A BINARY SEARCH TREE
 *
 * This program extends an assumed BinaryTree implementation (from
 * "binary_tree.h") by adding functionality to find the lowest common ancestor
 * (LCA) of two nodes in a binary search tree (BST).
 *
 * The lowest common ancestor of two nodes in a BST is defined as the lowest
 * node in the tree that has both nodes as descendants (where we allow a node to
 * be a descendant of itself).
 *
 * Approach:
 * 1. The function first checks if the tree is empty or if either of the values
 * is not present in the tree, in which case an exception is thrown.
 * 2. The recursive helper function 'findLCA' takes advantage of the BST
 * property:
 *    - If both values are less than the current node's value, the LCA must be
 * in the left subtree.
 *    - If both values are greater than the current node's value, the LCA must
 * be in the right subtree.
 *    - Otherwise, the current node is the LCA.
 *
 * ASCII Illustration:
 *              20
 *             /  \
 *            8    22
 *           / \
 *          4  12
 *             / \
 *            10 14
 *
 * Example Input/Output:
 * Input: Insert values {20, 8, 22, 4, 12, 10, 14} into the BST.
 * Query: Find LCA of 10 and 14.
 * Output: 12
 *
 * Explanation:
 * For values 10 and 14, the LCA is 12 because 12 is the lowest node that is an
 * ancestor to both.
 */

#include "binary_tree.h"
#include <cassert>
#include <stdexcept>

class TreeWithLowestCommonAncestor : public BinaryTree {
public:
  TreeWithLowestCommonAncestor() : BinaryTree() {}

  // Finds the lowest common ancestor (LCA) of two nodes with the given values.
  int findLowestCommonAncestor(int value1, int value2) const {
    if (!root || !contains(value1) || !contains(value2)) {
      throw std::invalid_argument("Values are not present in the tree.");
    }
    return findLCA(root.get(), value1, value2);
  }

private:
  // Recursive helper function that finds the LCA by leveraging BST properties.
  int findLCA(const Node *node, int value1, int value2) const {
    if (node->left && node->value > value1 && node->value > value2) {
      return findLCA(node->left.get(), value1, value2);
    }
    if (node->right && node->value < value1 && node->value < value2) {
      return findLCA(node->right.get(), value1, value2);
    }
    return node->value;
  }
};

// Test function to verify the correctness of the LCA implementation.
void runTests() {
  {
    TreeWithLowestCommonAncestor tree;
    for (const auto &value : {20, 8, 22, 4, 12, 10, 14}) {
      tree.add(value);
    }
    assert(tree.findLowestCommonAncestor(10, 14) == 12);
  }

  {
    TreeWithLowestCommonAncestor tree;
    for (const auto &value : {20, 8, 22, 4, 12, 10, 14}) {
      tree.add(value);
    }
    assert(tree.findLowestCommonAncestor(8, 14) == 8);
  }

  {
    TreeWithLowestCommonAncestor tree;
    for (const auto &value : {20, 8, 22, 4, 12, 10, 14}) {
      tree.add(value);
    }
    assert(tree.findLowestCommonAncestor(10, 22) == 20);
  }

  {
    TreeWithLowestCommonAncestor tree;
    for (const auto &value : {5, 4, 3, 2, 1}) {
      tree.add(value);
    }
    // For this degenerate tree (all nodes to the left), the LCA of 1 and 3
    // is 3.
    assert(tree.findLowestCommonAncestor(1, 3) == 3);
  }
}

int main() {
  runTests();
  return 0;
}
