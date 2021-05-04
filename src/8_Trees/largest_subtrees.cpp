#include "binary_tree.h"
#include <cassert>
#include <functional>
#include <limits>

class TreeWithSubtree : public BinaryTree {

public:
  TreeWithSubtree() : BinaryTree() {}

  int largestBST() {
    int min, max, largestSize;

    std::function<bool(Node *, int &, int &, int &)> _largestBST;
    _largestBST = [&](Node *node, int &min, int &max,
                      int &largestSize) -> bool {
      if (!node) {
        max = 0x80000000;
        min = 0x7FFFFFFF;
        largestSize = 0;
        return true;
      }

      int minLeft, maxLeft, leftSize;
      bool left = _largestBST(node->left, minLeft, maxLeft, leftSize);

      int minRight, maxRight, rightSize;
      bool right = _largestBST(node->right, minRight, maxRight, rightSize);

      bool overall = false;
      if (left && right && node->value >= maxLeft && node->value <= minRight) {
        largestSize = leftSize + rightSize + 1;
        overall = true;

        min = (node->value < minLeft) ? node->value : minLeft;
        max = (node->value > maxRight) ? node->value : maxRight;
      } else
        largestSize = (leftSize > rightSize) ? leftSize : rightSize;

      return overall;
    };

    _largestBST(root, min, max, largestSize);
    return largestSize;
  }
};

void test1() {
  TreeWithSubtree tree;
  tree.add(8);
  tree.add(6);
  tree.add(10);
  tree.add(5);
  tree.add(7);
  tree.add(9);
  tree.add(11);

  int result = 7;
  assert(tree.largestBST() == result);
}

void test2() {
  TreeWithSubtree tree;
  tree.add(11);
  tree.add(6);
  tree.add(16);
  tree.add(5);
  tree.add(7);
  tree.add(19);

  int result = 6;
  assert(tree.largestBST() == result);
}

void test3() {

  TreeWithSubtree tree;
  tree.add(12);
  tree.add(6);
  tree.add(9);
  tree.add(5);
  tree.add(8);
  tree.add(10);

  int result = 6;
  assert(tree.largestBST() == result);
}

void test4() {
  TreeWithSubtree tree;
  tree.add(5);
  tree.add(3);
  tree.add(4);
  tree.add(2);
  tree.add(1);

  int result = 5;
  assert(tree.largestBST() == result);
}

int main() {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
