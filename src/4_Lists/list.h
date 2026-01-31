#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>

class List {
protected:
  struct Node {
    int data{};
    std::unique_ptr<Node> next{};
    Node() = default;
    explicit Node(int value) : data(value), next(nullptr) {}
  };

public:
  class ConstIterator {
  public:
    explicit ConstIterator(const Node *node) : node(node) {}

    int operator*() const { return node->data; }

    ConstIterator &operator++() {
      node = node->next.get();
      return *this;
    }

    bool operator==(const ConstIterator &other) const {
      return node == other.node;
    }

    bool operator!=(const ConstIterator &other) const {
      return node != other.node;
    }

  private:
    const Node *node;
  };

  List();
  List(const List &other);
  List(List &&other) noexcept;
  ~List();
  List &operator=(const List &other);
  List &operator=(List &&other) noexcept;
  bool empty() const;
  unsigned int size() const;
  void clear();
  // Move the node at index2 to be immediately after the node at index1.
  void connectNodes(unsigned int index1, unsigned int index2);
  void print() const;
  void append(int value);
  int get(unsigned int index) const;
  bool operator==(const List &other) const;
  void swap(List &other) noexcept;

  ConstIterator begin() const { return ConstIterator(head.get()); }
  ConstIterator end() const { return ConstIterator(nullptr); }

protected:
  Node *nodeAt(unsigned int index);
  const Node *nodeAt(unsigned int index) const;
  std::unique_ptr<Node> *ownerAt(unsigned int index);
  std::unique_ptr<Node> head;
  unsigned int count;
};
