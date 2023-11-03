#include "binary_tree.h"

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::~BinaryTree() = default;

void BinaryTree::add(int value) { add(value, root); }

void BinaryTree::add(int value, std::unique_ptr<Node> &node) {
  if (!node) {
    node = std::make_unique<Node>(value);
  } else if (value < node->value) {
    add(value, node->left);
  } else if (value > node->value) {
    add(value, node->right);
  } else {
    // Value already exists
  }
}

bool BinaryTree::contains(int value) const { return contains(value, root); }

bool BinaryTree::contains(int value, const std::unique_ptr<Node> &node) const {
  if (!node) {
    return false;
  }
  if (node->value == value) {
    return true;
  }
  if (value < node->value) {
    return contains(value, node->left);
  }
  return contains(value, node->right);
}

bool operator==(const BinaryTree &t1, const BinaryTree &t2) {
  return BinaryTree::isIdentical(t1.root, t2.root);
}

bool BinaryTree::isIdentical(const std::unique_ptr<Node> &a,
                             const std::unique_ptr<Node> &b) {
  if (!a && !b) {
    return true;
  }
  if (a && b && a->value == b->value) {
    return isIdentical(a->left, b->left) && isIdentical(a->right, b->right);
  }
  return false;
}
