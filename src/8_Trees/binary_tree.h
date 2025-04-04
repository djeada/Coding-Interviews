#pragma once
#include <functional>
#include <memory>

class BinaryTree {
public:
  BinaryTree();           // declare
  virtual ~BinaryTree();  // declare

  BinaryTree(const BinaryTree&) = delete;
  BinaryTree& operator=(const BinaryTree&) = delete;

  BinaryTree(BinaryTree&&) = default;
  BinaryTree& operator=(BinaryTree&&) = default;

  void add(int value);
  bool contains(int value) const;
  friend bool operator==(const BinaryTree &t1, const BinaryTree &t2);

protected:
  struct Node {
    int value;
    std::unique_ptr<Node> left, right;
    Node(int val) : value(val), left(nullptr), right(nullptr) {}
  };

  std::unique_ptr<Node> root;

  void add(int value, std::unique_ptr<Node> &node);
  bool contains(int value, const std::unique_ptr<Node> &node) const;
  static bool isIdentical(const std::unique_ptr<Node> &a,
                          const std::unique_ptr<Node> &b);
};
