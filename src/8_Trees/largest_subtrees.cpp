#include "binary_tree.h"
#include <algorithm>
#include <cassert>
#include <limits>

class TreeWithSubtree : public BinaryTree {
public:
  TreeWithSubtree() : BinaryTree() {}

  int largestBST() const {
    int min, max, largestSize;
    _largestBST(root.get(), min, max, largestSize);
    return largestSize;
  }

private:
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
