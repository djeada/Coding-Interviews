#include "binary_tree.h"
#include <cassert>
#include <stdexcept>

class TreeWithLowestCommonAncestor : public BinaryTree {
public:
  TreeWithLowestCommonAncestor() : BinaryTree() {}

  int findLowestCommonAncestor(int value1, int value2) const {
    if (!root || !contains(value1) || !contains(value2)) {
      throw std::invalid_argument("Values are not present in the tree.");
    }
    return findLCA(root.get(), value1, value2);
  }

private:
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
    assert(tree.findLowestCommonAncestor(1, 3) == 3);
  }
}

int main() {
  runTests();
  return 0;
}
