#pragma once

#include <cstddef>
#include <functional>
#include <memory>

class BinaryTree {
public:
  BinaryTree();
  virtual ~BinaryTree();

  BinaryTree(const BinaryTree &other);
  BinaryTree &operator=(const BinaryTree &other);

  BinaryTree(BinaryTree &&other) noexcept;
  BinaryTree &operator=(BinaryTree &&other) noexcept;

  void add(int value);
  bool empty() const;
  std::size_t size() const;
  void clear();
  bool contains(int value) const;
  friend bool operator==(const BinaryTree &t1, const BinaryTree &t2);
  void swap(BinaryTree &other) noexcept;

protected:
  struct Node {
    int value{};
    std::unique_ptr<Node> left{};
    std::unique_ptr<Node> right{};
    Node() = default;
    Node(int val) : value(val), left(nullptr), right(nullptr) {}
  };

  std::unique_ptr<Node> root;
  std::size_t count;

  void add(int value, std::unique_ptr<Node> &node);
  bool contains(int value, const std::unique_ptr<Node> &node) const;
  static std::unique_ptr<Node> clone(const std::unique_ptr<Node> &node);
  static std::size_t countNodes(const std::unique_ptr<Node> &node);
  static bool isIdentical(const std::unique_ptr<Node> &a,
                          const std::unique_ptr<Node> &b);
};
