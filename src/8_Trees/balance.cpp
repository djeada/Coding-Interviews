#include "binary_tree.h"
#include <cassert>
#include <cmath>

class TreeWithBalanceCheck : public BinaryTree {
public:
  TreeWithBalanceCheck() : BinaryTree() {}
  int depth() const { return depth(root); }
  bool isBalanced1() const { return isBalanced1(root); }
  bool isBalanced2() const {
    int depth = 0;
    return isBalanced2(root, depth);
  }

private:
  int depth(const std::unique_ptr<Node> &node) const {
    if (!node)
      return 0;
    int left = depth(node->left);
    int right = depth(node->right);
    return std::max(left, right) + 1;
  }

  bool isBalanced1(const std::unique_ptr<Node> &node) const {
    if (!node)
      return true;
    int left = depth(node->left);
    int right = depth(node->right);
    int diff = left - right;
    return std::abs(diff) <= 1 && isBalanced1(node->left) &&
           isBalanced1(node->right);
  }

  bool isBalanced2(const std::unique_ptr<Node> &node, int &depth) const {
    if (!node) {
      depth = 0;
      return true;
    }
    int left, right;
    if (isBalanced2(node->left, left) && isBalanced2(node->right, right)) {
      int diff = left - right;
      if (std::abs(diff) <= 1) {
        depth = std::max(left, right) + 1;
        return true;
      }
    }
    return false;
  }
};

void test1() {
  TreeWithBalanceCheck tree;
  tree.add(4);
  tree.add(6);
  tree.add(2);
  tree.add(3);
  tree.add(1);
  tree.add(5);
  tree.add(7);

  assert(tree.isBalanced1());
  assert(tree.isBalanced2());
}

void test2() {
  TreeWithBalanceCheck tree;
  tree.add(2);
  tree.add(1);
  tree.add(3);

  assert(tree.isBalanced1());
  assert(tree.isBalanced2());
}

void test3() {
  TreeWithBalanceCheck tree;
  tree.add(1);
  tree.add(2);
  tree.add(3);
  tree.add(4);
  tree.add(5);

  assert(!tree.isBalanced1());
  assert(!tree.isBalanced2());
}

void test4() {
  TreeWithBalanceCheck tree;
  tree.add(5);
  tree.add(4);
  tree.add(3);
  tree.add(2);
  tree.add(1);

  assert(!tree.isBalanced1());
  assert(!tree.isBalanced2());
}

int main() {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
