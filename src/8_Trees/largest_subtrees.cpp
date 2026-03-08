/*
 * Task: Find the size of the largest BST subtree in a binary tree.
 *
 * LARGEST BST SUBTREE
 *
 * Problem:
 * Given a binary tree, return the size of the largest subtree that is a valid
 * binary search tree (BST).
 *
 * Constraints:
 * - 0 <= number of nodes <= 10^5
 * - Node values are 32-bit signed integers.
 *
 * Example:
 * Input: root built from [8,6,10,5,7,9,11]
 * Output: 7
 */

#include "binary_tree.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <string>

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

int main() {
  int total = 0;
  int failed = 0;

  auto expectEqual = [&](int got, int expected, const std::string &label) {
    ++total;
    if (got == expected) {
      std::cout << "[PASS] " << label << "\n";
      return;
    }
    ++failed;
    std::cout << "[FAIL] " << label << " expected=" << expected
              << " got=" << got << "\n";
  };

  auto summary = [&]() {
    std::cout << "Tests: " << total - failed << " passed, " << failed
              << " failed, " << total << " total\n";
  };

  auto testTreeWithSubtree = [&](const TreeWithSubtree &tree,
                                 int expectedSize,
                                 const std::string &label) {
    expectEqual(tree.largestBST(), expectedSize, label);
  };

  {
    TreeWithSubtree empty;
    testTreeWithSubtree(empty, 0, "largest BST empty");
  }
  testTreeWithSubtree(
      [] {
        TreeWithSubtree tree;
        for (int val : {8, 6, 10, 5, 7, 9, 11})
          tree.add(val);
        return tree;
      }(),
      7, "largest BST full");

  testTreeWithSubtree(
      [] {
        TreeWithSubtree tree;
        for (int val : {11, 6, 16, 5, 7, 19})
          tree.add(val);
        return tree;
      }(),
      6, "largest BST case 2");

  testTreeWithSubtree(
      [] {
        TreeWithSubtree tree;
        for (int val : {12, 6, 9, 5, 8, 10})
          tree.add(val);
        return tree;
      }(),
      6, "largest BST case 3");

  testTreeWithSubtree(
      [] {
        TreeWithSubtree tree;
        for (int val : {5, 3, 4, 2, 1})
          tree.add(val);
        return tree;
      }(),
      5, "largest BST skewed");
  summary();

  return 0;
}
