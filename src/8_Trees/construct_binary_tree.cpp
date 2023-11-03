#include "binary_tree.h"
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <vector>

class TreeWithConstruct : public BinaryTree {
private:
  std::unique_ptr<Node> construct(std::vector<int> &inorder,
                                  std::vector<int> &preorder, int start,
                                  int end, int &preInd) {
    if (start > end)
      return nullptr;

    auto val = preorder[preInd];
    auto root = std::make_unique<Node>(val);
    preInd++;

    if (start == end)
      return root;

    auto ind = std::find(inorder.begin() + start, inorder.begin() + end, val) -
               inorder.begin();

    root->left = construct(inorder, preorder, start, ind - 1, preInd);
    root->right = construct(inorder, preorder, ind + 1, end, preInd);

    return root;
  }

public:
  TreeWithConstruct() : BinaryTree() {}

  TreeWithConstruct(std::vector<int> &inorder, std::vector<int> &preorder) {
    if (inorder.empty() || preorder.empty())
      throw std::runtime_error("Invalid input.");

    int pre = 0;
    root = construct(inorder, preorder, 0, preorder.size() - 1, pre);
  }
};

void test1() {
  std::vector<int> preorder{9, 8, 4, 7, 13, 10, 16, 15};
  std::vector<int> inorder{4, 7, 8, 9, 10, 13, 15, 16};

  TreeWithConstruct tree(inorder, preorder);

  BinaryTree result;
  result.add(9);
  result.add(8);
  result.add(13);
  result.add(4);
  result.add(10);
  result.add(16);
  result.add(7);
  result.add(15);

  assert(tree == result);
}

void test2() {
  std::vector<int> inorder{1, 2, 3, 4, 5};
  std::vector<int> preorder{5, 4, 3, 2, 1};

  TreeWithConstruct tree(inorder, preorder);

  BinaryTree result;
  result.add(5);
  result.add(4);
  result.add(3);
  result.add(2);
  result.add(1);

  assert(tree == result);
}

void test3() {
  std::vector<int> preorder{1, 2, 3, 4, 5};
  std::vector<int> inorder{1, 2, 3, 4, 5};

  TreeWithConstruct tree(inorder, preorder);

  BinaryTree result;
  result.add(1);
  result.add(2);
  result.add(3);
  result.add(4);
  result.add(5);

  assert(tree == result);
}

void test4() {
  std::vector<int> preorder{1};
  std::vector<int> inorder{1};

  TreeWithConstruct tree(inorder, preorder);

  BinaryTree result;
  result.add(1);

  assert(tree == result);
}

int main() {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
