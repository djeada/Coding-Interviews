#include "binary_tree.h"
#include <cassert>
#include <functional>
#include <vector>

class TreeWithPath : public BinaryTree {

public:
  TreeWithPath() : BinaryTree() {}

  std::vector<int> findPath(int expectedSum) {
    if (!root)
      return std::vector<int>();

    std::function<bool(Node *, int, std::vector<int> &, int)> _findPath;
    _findPath = [&](Node *node, int expectedSum, std::vector<int> &path,
                    int currentSum) -> bool {
      currentSum += node->value;
      path.push_back(node->value);

      bool isLeaf = !node->left && !node->right;

      if (isLeaf) {
        if (currentSum != expectedSum)
          path.pop_back();
        return currentSum == expectedSum;
      }

      auto leftResult = _findPath(node->left, expectedSum, path, currentSum);
      auto rightResult = _findPath(node->right, expectedSum, path, currentSum);

      if (node->left && node->right) {
        if (!(leftResult || rightResult))
          path.pop_back();
        return leftResult || rightResult;
      }

      if (node->left) {
        if (!leftResult)
          path.pop_back();

        return leftResult;
      }

      if (node->right) {
        if (!rightResult)
          path.pop_back();

        return rightResult;
      }

      return false;
    };

    std::vector<int> path;
    int currentSum = 0;

    if (_findPath(root, expectedSum, path, currentSum))
      return path;

    return std::vector<int>();
  }
};

void test1() {

  TreeWithPath tree;
  tree.add(10);
  tree.add(5);
  tree.add(12);
  tree.add(4);
  tree.add(7);

  int expectedSum = 22;
  std::vector<int> result{10, 5, 7, 12};
  assert(tree.findPath(expectedSum) == result);
}

void test2() {
  TreeWithPath tree;
  tree.add(10);
  tree.add(5);
  tree.add(12);
  tree.add(4);
  tree.add(7);

  int expectedSum = 15;
  std::vector<int> result;
  assert(tree.findPath(expectedSum) == result);
}

void test3() {
  TreeWithPath tree;
  tree.add(5);
  tree.add(4);
  tree.add(3);
  tree.add(2);
  tree.add(1);

  int expectedSum = 15;
  std::vector<int> result{5, 4, 3, 2, 1};
  assert(tree.findPath(expectedSum) == result);
}

void test4() {
  TreeWithPath tree;
  tree.add(1);
  tree.add(2);
  tree.add(3);
  tree.add(4);
  tree.add(5);

  int expectedSum = 16;
  std::vector<int> result;
  assert(tree.findPath(expectedSum) == result);
}

int main() {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
