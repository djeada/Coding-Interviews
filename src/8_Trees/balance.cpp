#include "binary_tree.h"
#include <cassert>
#include <functional>

class TreeWithBalanceCheck : public BinaryTree {

private:
  int _depth(Node *node) {
    if (!node)
      return 0;

    int left = _depth(node->left);
    int right = _depth(node->right);

    return (left > right) ? (left + 1) : (right + 1);
  }

public:
  TreeWithBalanceCheck() : BinaryTree() {}

  int depth() { return _depth(root); }

  bool isBalanced1() {

    std::function<bool(Node *)> _isBalanced;
    _isBalanced = [&](Node *node) -> bool {
      if (!node)
        return true;

      int left = _depth(node->left);
      int right = _depth(node->right);
      int diff = left - right;

      if (diff > 1 || diff < -1)
        return false;

      return _isBalanced(node->left) && _isBalanced(node->right);
    };

    return _isBalanced(root);
  }

  bool isBalanced2() {

    std::function<bool(Node *, int *)> _isBalanced;
    _isBalanced = [&](Node *node, int *depth) -> bool {
      if (!node) {
        *depth = 0;
        return true;
      }

      int left, right;
      if (_isBalanced(node->left, &left) && _isBalanced(node->right, &right)) {

        int diff = left - right;

        if (diff <= 1 && diff >= -1) {
          *depth = 1 + (left > right ? left : right);
          return true;
        }
      }

      return false;
    };

    int depth = 0;
    return _isBalanced(root, &depth);
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
  //  test2();
  //  test3();
  //  test4();

  return 0;
}
