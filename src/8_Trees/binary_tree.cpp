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

void BinaryTree::add(int value) {

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

bool BinaryTree::contains(int value) {

  if (!root)
    return false;

  std::function<bool(Node *, int)> _contains;
  _contains = [&](Node *node, int value) -> bool {
    if (!node)
      return false;

    if (node->value == value)
      return true;

    else if (node->value > value)
      return _contains(node->left, value);

    return _contains(node->right, value);
  };

  return _contains(root, value);
}

bool operator==(const BinaryTree &t1, const BinaryTree &t2) {

  auto root1 = t1.root;
  auto root2 = t2.root;

  std::function<bool(BinaryTree::Node *, BinaryTree::Node *)> isIdentical;
  isIdentical = [&](BinaryTree::Node *root1, BinaryTree::Node *root2) -> bool {
    if (root1 == nullptr && root2 == nullptr)
      return true;
    else if ((root1 && !root2) || (!root1 && root2))
      return false;
    else if (root1->value == root2->value &&
             isIdentical(root1->left, root2->left) &&
             isIdentical(root1->right, root2->right))
      return true;
    return false;
  };

  return isIdentical(root1, root2);
}
