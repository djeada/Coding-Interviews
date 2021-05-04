#include "binary_tree.h"
#include <cassert>
#include <functional>

class TreeWithDepth : public BinaryTree {

public:
  TreeWithDepth() : BinaryTree() {}

  unsigned int depth() {

    std::function<unsigned int(Node *)> _depth;
    _depth = [&](Node *node) -> unsigned int {
      if (!node)
        return 0;

      int left = _depth(node->left);
      int right = _depth(node->right);

      return (left > right) ? (left + 1) : (right + 1);
    };

    return _depth(root);
  }
};

void test1() {

  TreeWithDepth tree;
  tree.add(9);
  tree.add(8);
  tree.add(13);
  tree.add(4);
  tree.add(10);
  tree.add(16);
  tree.add(7);
  tree.add(15);

  unsigned int result = 4;
  assert(tree.depth() == result);
}

void test2() {

  TreeWithDepth tree;
  tree.add(5);
  tree.add(4);
  tree.add(3);
  tree.add(2);
  tree.add(1);

  unsigned int result = 5;
  assert(tree.depth() == result);
}

void test3() {

  TreeWithDepth tree;
  tree.add(1);
  tree.add(2);
  tree.add(3);
  tree.add(4);
  tree.add(5);

  unsigned int result = 5;
  assert(tree.depth() == result);
}

void test4() {

  TreeWithDepth tree;
  tree.add(1);

  unsigned int result = 1;
  assert(tree.depth() == result);
}

int main() {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
