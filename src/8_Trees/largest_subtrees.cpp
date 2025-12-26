/*
 * LARGEST BINARY SEARCH TREE (BST) SUBTREE SIZE
 *
 * This program extends an assumed BinaryTree implementation (from
 * "binary_tree.h") by adding a method to determine the size of the largest
 * subtree that is a valid Binary Search Tree (BST).
 *
 * The algorithm uses a recursive helper function to traverse the tree and
 * calculate:
 *   - The minimum and maximum values in the subtree.
 *   - The size of the largest BST subtree found.
 *   - Whether the current subtree itself is a BST.
 *
 * The base case treats an empty subtree as a valid BST with size 0, setting min
 * and max to extreme values. For non-empty nodes, it checks if both left and
 * right subtrees are BSTs, and if the current node's value is at least as large
 * as the maximum value in the left subtree and at most as small as the minimum
 * value in the right subtree.
 *
 * ASCII Illustration:
 *          8
 *         / \
 *        6   10
 *       / \  / \
 *      5   7 9  11
 *
 * Example Input/Output:
 * Input: Insert values {8, 6, 10, 5, 7, 9, 11} into the tree.
 * Output: The largest BST subtree size is 7.
 *
 * Explanation:
 * The entire tree is a BST, so the size of the largest BST subtree is the
 * number of nodes in the tree.
 */

#include "binary_tree.h"
#include <algorithm>
#include <cassert>
#include <limits>

class TreeWithSubtree : public BinaryTree {
public:
  TreeWithSubtree() : BinaryTree() {}

  // Returns the size of the largest BST subtree within the binary tree.
  int largestBST() const {
    int min, max, largestSize;
    _largestBST(root.get(), min, max, largestSize);
    return largestSize;
  }

private:
  // Recursive helper function that returns whether the subtree is a BST,
  // and updates min, max, and the size of the largest BST subtree.
  bool _largestBST(const Node *node, int &min, int &max,
                   int &largestSize) const {
    if (!node) {
      max = std::numeric_limits<int>::min();
      min = std::numeric_limits<int>::max();
      largestSize = 0;
      return true;
    }

    int minLeft, maxLeft, leftSize;
    bool left = _largestBST(node->left.get(), minLeft, maxLeft, leftSize);

    int minRight, maxRight, rightSize;
    bool right = _largestBST(node->right.get(), minRight, maxRight, rightSize);

    if (left && right && node->value >= maxLeft && node->value <= minRight) {
      largestSize = leftSize + rightSize + 1;
      min = std::min(node->value, minLeft);
      max = std::max(node->value, maxRight);
      return true;
    }

    largestSize = std::max(leftSize, rightSize);
    return false;
  }
};

// Test function to ensure that the computed largest BST subtree size matches
// the expected size.
void testTreeWithSubtree(const TreeWithSubtree &tree, int expectedSize) {
  assert(tree.largestBST() == expectedSize);
}

int main() {
  testTreeWithSubtree(
      [] {
        TreeWithSubtree tree;
        for (int val : {8, 6, 10, 5, 7, 9, 11})
          tree.add(val);
        return tree;
      }(),
      7);

  testTreeWithSubtree(
      [] {
        TreeWithSubtree tree;
        for (int val : {11, 6, 16, 5, 7, 19})
          tree.add(val);
        return tree;
      }(),
      6);

  testTreeWithSubtree(
      [] {
        TreeWithSubtree tree;
        for (int val : {12, 6, 9, 5, 8, 10})
          tree.add(val);
        return tree;
      }(),
      6);

  testTreeWithSubtree(
      [] {
        TreeWithSubtree tree;
        for (int val : {5, 3, 4, 2, 1})
          tree.add(val);
        return tree;
      }(),
      5);

  return 0;
}
