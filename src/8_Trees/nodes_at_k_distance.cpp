#include "binary_tree.h"
#include <cassert>
#include <functional>
#include <iostream>
#include <stdexcept>
class TreeWithDepth : public BinaryTree {

public:
  TreeWithDepth() : BinaryTree() {}

  std::vector<int> kDistanceNodes(unsigned int k) {

    std::vector<int> result;

    if (!root)
      return result;

    std::function<void(Node *, int, std::vector<int> &)> nodesDown;
    nodesDown = [&](Node *node, int k, std::vector<int> &result) -> void {
      if (!node || k < 0)
        return;

      if (k == 0) {
        result.push_back(node->value);
        return;
      }

      nodesDown(node->left, k - 1, result);
      nodesDown(node->right, k - 1, result);
    };

    nodesDown(root, k, result);

    return result;
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

  unsigned int k = 3;
  std::vector<int> result{7, 15};
  assert(tree.kDistanceNodes(k) == result);
}

void test2() {

  TreeWithDepth tree;
  tree.add(5);
  tree.add(4);
  tree.add(3);
  tree.add(2);
  tree.add(1);

  unsigned int k = 4;
  std::vector<int> result{1};
  assert(tree.kDistanceNodes(k) == result);
}

void test3() {

  TreeWithDepth tree;
  tree.add(1);
  tree.add(2);
  tree.add(3);
  tree.add(4);
  tree.add(5);

  unsigned int k = 4;
  std::vector<int> result{5};
  assert(tree.kDistanceNodes(k) == result);
}

void test4() {

  TreeWithDepth tree;
  tree.add(1);

  unsigned int k = 1;
  std::vector<int> result;
  assert(tree.kDistanceNodes(k) == result);
}

int main() {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
