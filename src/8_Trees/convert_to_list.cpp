#include "binary_tree.h"
#include <cassert>
#include <stack>
#include <vector>

class TreeWithVector : public BinaryTree {
public:
  // Default constructor calls the base default constructor
  TreeWithVector() : BinaryTree() {}

  // Delete copy semantics
  TreeWithVector(const TreeWithVector &) = delete;
  TreeWithVector &operator=(const TreeWithVector &) = delete;

  // Allow move semantics
  TreeWithVector(TreeWithVector &&) = default;
  TreeWithVector &operator=(TreeWithVector &&) = default;

  std::vector<int> inorder() const {
    std::vector<int> result;
    std::stack<const Node *> s;
    const Node *curr = root.get();

    while (curr || !s.empty()) {
      while (curr) {
        s.push(curr);
        curr = curr->left.get();
      }
      curr = s.top();
      s.pop();
      result.push_back(curr->value);
      curr = curr->right.get();
    }
    return result;
  }

  std::vector<int> preorder() const {
    std::vector<int> result;
    std::stack<const Node *> s;

    if (root)
      s.push(root.get());

    while (!s.empty()) {
      const auto temp = s.top();
      s.pop();
      result.push_back(temp->value);

      if (temp->right)
        s.push(temp->right.get());
      if (temp->left)
        s.push(temp->left.get());
    }
    return result;
  }
};

// Simple test function using assertions
void testTreeWithVector(const TreeWithVector &tree,
                        const std::vector<int> &inorderExpected,
                        const std::vector<int> &preorderExpected) {
  assert(tree.inorder() == inorderExpected);
  assert(tree.preorder() == preorderExpected);
}

int main() {
  testTreeWithVector(
      [] {
        TreeWithVector tree;
        for (int val : {9, 8, 13, 4, 10, 16, 7, 15})
          tree.add(val);
        return tree;  // Moved (since copy is deleted)
      }(),
      {4, 7, 8, 9, 10, 13, 15, 16},
      {9, 8, 4, 7, 13, 10, 16, 15});

  testTreeWithVector(
      [] {
        TreeWithVector tree;
        for (int val : {5, 4, 3, 2, 1})
          tree.add(val);
        return tree;
      }(),
      {1, 2, 3, 4, 5},
      {5, 4, 3, 2, 1});

  testTreeWithVector(
      [] {
        TreeWithVector tree;
        for (int val : {1, 2, 3, 4, 5})
          tree.add(val);
        return tree;
      }(),
      {1, 2, 3, 4, 5},
      {1, 2, 3, 4, 5});

  testTreeWithVector(
      [] {
        TreeWithVector tree;
        tree.add(1);
        return tree;
      }(),
      {1},
      {1});

  return 0;
}
