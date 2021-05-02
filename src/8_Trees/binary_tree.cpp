#include "binary_tree.h"
#include <functional>

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::~BinaryTree() {

  std::function<void(Node *)> destroyRecursive;
  destroyRecursive = [&](Node *node) -> void {
    if (node) {
      destroyRecursive(node->left);
      destroyRecursive(node->right);
      delete node;
    }
  };

  destroyRecursive(root);
}

void BinaryTree ::add(int value) {

  if (!root) {
    root = new Node(value, nullptr, nullptr);
    return;
  }

  std::function<void(Node *)> _add;
  _add = [&](Node *node) -> void {
    if (value < node->value) {

      if (node->left)
        _add(node->left);

      else
        node->left = new Node(value, nullptr, nullptr);
    }

    else if (value > node->value) {

      if (node->right)
        _add(node->right);

      else
        node->right = new Node(value, nullptr, nullptr);
    } else {
      // throw exception
      // cout << "The key has already been added to the tree" << endl;
    }
  };

  _add(root);
}
