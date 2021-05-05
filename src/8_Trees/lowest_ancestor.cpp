#include "binary_tree.h"
#include <cassert>
#include <functional>
#include <vector>

class TreeWithLCA : public BinaryTree {

public:
  TreeWithLCA() : BinaryTree() {}

  int lowestCommonAncestor(int val1, int val2) {

    if (!root || !contains(val1) || !contains(val2))
      throw std::runtime_error("Invalid input.");

    std::function<int(Node *, int, int)> _lca;
    _lca = [&](Node *node, int val1, int val2) -> int {
      if (node->left && node->value > val1 && node->value > val2)
        return _lca(node->left, val1, val2);

      if (node->right && node->value < val1 && node->value < val2)
        return _lca(node->right, val1, val2);

      return node->value;
    };

    return _lca(root, val1, val2);
  }
};

void test1() {
  TreeWithLCA tree;
  tree.add(20);
  tree.add(8);
  tree.add(22);
  tree.add(4);
  tree.add(12);
  tree.add(10);
  tree.add(14);

  int val1 = 10;
  int val2 = 14;
  int result = 12;

  assert(tree.lowestCommonAncestor(val1, val2) == result);
}

void test2() {
  TreeWithLCA tree;
  tree.add(20);
  tree.add(8);
  tree.add(22);
  tree.add(4);
  tree.add(12);
  tree.add(10);
  tree.add(14);

  int val1 = 8;
  int val2 = 14;
  int result = 8;

  assert(tree.lowestCommonAncestor(val1, val2) == result);
}

void test3() {
  TreeWithLCA tree;
  tree.add(20);
  tree.add(8);
  tree.add(22);
  tree.add(4);
  tree.add(12);
  tree.add(10);
  tree.add(14);

  int val1 = 10;
  int val2 = 22;
  int result = 20;

  assert(tree.lowestCommonAncestor(val1, val2) == result);
}

void test4() {
  TreeWithLCA tree;
  tree.add(5);
  tree.add(4);
  tree.add(3);
  tree.add(2);
  tree.add(1);

  int val1 = 1;
  int val2 = 3;
  int result = 3;

  assert(tree.lowestCommonAncestor(val1, val2) == result);
}

int main() {
  test1();
  test2();
  test3();
  test4();
  return 0;
}
