#include "binary_tree.h"

#include <utility>

BinaryTree::BinaryTree() : root(nullptr), count(0) {}

BinaryTree::~BinaryTree() = default;

BinaryTree::BinaryTree(const BinaryTree &other) : root(nullptr), count(0) {
  root = clone(other.root);
  count = countNodes(root);
}

BinaryTree::BinaryTree(BinaryTree &&other) noexcept
    : root(std::move(other.root)), count(other.count) {
  other.count = 0;
}

BinaryTree &BinaryTree::operator=(const BinaryTree &other) {
  if (this == &other) {
    return *this;
  }
  BinaryTree temp(other);
  swap(temp);
  return *this;
}

BinaryTree &BinaryTree::operator=(BinaryTree &&other) noexcept {
  if (this == &other) {
    return *this;
  }
  root = std::move(other.root);
  count = other.count;
  other.count = 0;
  return *this;
}

void BinaryTree::add(int value) { add(value, root); }

bool BinaryTree::empty() const { return !root; }

std::size_t BinaryTree::size() const { return count; }

void BinaryTree::clear() {
  root.reset();
  count = 0;
}

void BinaryTree::add(int value, std::unique_ptr<Node> &node) {
  if (!node) {
    node = std::make_unique<Node>(value);
    ++count;
  } else if (value < node->value) {
    add(value, node->left);
  } else if (value > node->value) {
    add(value, node->right);
  } else {
    // Value already exists; do nothing.
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

std::unique_ptr<BinaryTree::Node>
BinaryTree::clone(const std::unique_ptr<Node> &node) {
  if (!node) {
    return nullptr;
  }
  auto cloned = std::make_unique<Node>(node->value);
  cloned->left = clone(node->left);
  cloned->right = clone(node->right);
  return cloned;
}

std::size_t BinaryTree::countNodes(const std::unique_ptr<Node> &node) {
  if (!node) {
    return 0;
  }
  return 1 + countNodes(node->left) + countNodes(node->right);
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

void BinaryTree::swap(BinaryTree &other) noexcept {
  std::swap(root, other.root);
  std::swap(count, other.count);
}
