#include "binary_tree.h"
#include <cassert>
#include <stack>
#include <vector>

class TreeWithVector : public BinaryTree {

public:
  TreeWithVector() : BinaryTree() {}

  std::vector<int> inorder() {
    std::vector<int> result;
    std::stack<Node *> s;
    auto curr = root;

    while (curr || !s.empty()) {
      while (curr) {
        s.push(curr);
        curr = curr->left;
      }

      curr = s.top();
      s.pop();
      result.push_back(curr->value);
      curr = curr->right;
    }

    return result;
  }

  std::vector<int> preorder() {
    std::vector<int> result;
    std::stack<Node *> s;

    s.push(root);

    while (!s.empty()) {
      auto temp = s.top();
      result.push_back(temp->value);
      s.pop();

      if (temp->right)
        s.push(temp->right);

      if (temp->left)
        s.push(temp->left);
    }

    return result;
  }
};

void test1() {
  std::vector<int> preorder{9, 8, 4, 7, 13, 10, 16, 15};
  std::vector<int> inorder{4, 7, 8, 9, 10, 13, 15, 16};

  TreeWithVector tree;
  tree.add(9);
  tree.add(8);
  tree.add(13);
  tree.add(4);
  tree.add(10);
  tree.add(16);
  tree.add(7);
  tree.add(15);

  assert(tree.inorder() == inorder);
  assert(tree.preorder() == preorder);
}

void test2() {
  std::vector<int> inorder{1, 2, 3, 4, 5};
  std::vector<int> preorder{5, 4, 3, 2, 1};

  TreeWithVector tree;
  tree.add(5);
  tree.add(4);
  tree.add(3);
  tree.add(2);
  tree.add(1);

  assert(tree.inorder() == inorder);
  assert(tree.preorder() == preorder);
}

void test3() {
  std::vector<int> preorder{1, 2, 3, 4, 5};
  std::vector<int> inorder{1, 2, 3, 4, 5};

  TreeWithVector tree;
  tree.add(1);
  tree.add(2);
  tree.add(3);
  tree.add(4);
  tree.add(5);

  assert(tree.inorder() == inorder);
  assert(tree.preorder() == preorder);
}

void test4() {
  std::vector<int> preorder{1};
  std::vector<int> inorder{1};

  TreeWithVector tree;
  tree.add(1);

  assert(tree.inorder() == inorder);
  assert(tree.preorder() == preorder);
}

int main() {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
