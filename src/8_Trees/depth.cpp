#include "binary_tree.h"
#include <algorithm>
#include <cassert>

class TreeWithDepth : public BinaryTree {
public:
  TreeWithDepth() : BinaryTree() {}

  unsigned int depth() const { return _depth(root.get()); }

private:
  unsigned int _depth(const Node *node) const {
    if (!node)
      return 0;
    unsigned int left = _depth(node->left.get());
    unsigned int right = _depth(node->right.get());
    return std::max(left, right) + 1;
  }
};

void testTreeWithDepth(const TreeWithDepth &tree, unsigned int expectedDepth) {
  assert(tree.depth() == expectedDepth);
}

int main() {
  testTreeWithDepth(
      [] {
        TreeWithDepth tree;
        for (int val : {9, 8, 13, 4, 10, 16, 7, 15})
          tree.add(val);
        return tree;
      }(),
      4);

  testTreeWithDepth(
      [] {
        TreeWithDepth tree;
        for (int val : {5, 4, 3, 2, 1})
          tree.add(val);
        return tree;
      }(),
      5);

  testTreeWithDepth(
      [] {
        TreeWithDepth tree;
        for (int val : {1, 2, 3, 4, 5})
          tree.add(val);
        return tree;
      }(),
      5);

  testTreeWithDepth(
      [] {
        TreeWithDepth tree;
        tree.add(1);
        return tree;
      }(),
      1);

  return 0;
}
