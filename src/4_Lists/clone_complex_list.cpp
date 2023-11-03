/**
 * This program defines a class named ComplexList that represents a singly
 * linked list, with an additional "sibling" pointer in each node that can point
 * to any other node in the list. The class supports basic operations such as
 * appending nodes, setting sibling pointers, and copying a ComplexList while
 * preserving the sibling relationships.
 *
 * The ComplexList class is designed as follows:
 * - Each node in the list has an integer value, a 'next' pointer to the next
 * node, and a 'sibling' pointer.
 * - The class uses smart pointers (std::unique_ptr) for automatic memory
 * management of nodes.
 * - The copy constructor creates a deep copy of the list while correctly
 * duplicating sibling relationships.
 *
 */
#include <cassert>
#include <iostream>
#include <memory>

class ComplexList {
public:
  ComplexList() = default;

  ComplexList(const ComplexList &other) {
    cloneNodes(other.head.get());
    connectSiblingNodes(other.head.get());
    reconnectNodes(other.head.get());
  }

  // No need for a custom destructor as we use smart pointers.

  ComplexList &append(int value) {
    auto newNode = std::make_unique<Node>(value);

    if (!head) {
      head = std::move(newNode);
    } else {
      auto curr = head.get();
      while (curr->next)
        curr = curr->next.get();
      curr->next = std::move(newNode);
    }

    return *this;
  }

  void setSibling(Node *node, Node *sibling) {
    if (node)
      node->sibling = sibling;
  }

  friend bool operator==(const ComplexList &l1, const ComplexList &l2) {
    auto node1 = l1.head.get();
    auto node2 = l2.head.get();

    while (node1 && node2) {
      if (node1->value != node2->value)
        return false;

      if ((node1->sibling == nullptr) != (node2->sibling == nullptr))
        return false;

      if (node1->sibling && node2->sibling) {
        if (node1->sibling->value != node2->sibling->value)
          return false;
      }

      node1 = node1->next.get();
      node2 = node2->next.get();
    }

    return node1 == node2;
  }

private:
  struct Node {
    int value;
    std::unique_ptr<Node> next;
    Node *sibling = nullptr;

    explicit Node(int val) : value(val) {}
  };

  std::unique_ptr<Node> head;

  void cloneNodes(const Node *otherHead) {
    auto node = otherHead;
    while (node) {
      auto clonedNode = std::make_unique<Node>(node->value);
      clonedNode->next = std::move(node->next);
      node->next = std::move(clonedNode);
      node = node->next->next.get();
    }
  }

  void connectSiblingNodes(const Node *otherHead) {
    auto node = otherHead;
    while (node && node->next) {
      node->next->sibling = node->sibling ? node->sibling->next.get() : nullptr;
      node = node->next->next.get();
    }
  }

  void reconnectNodes(const Node *otherHead) {
    auto node = otherHead;
    if (node) {
      head = std::move(node->next);
      node->next = std::move(head->next);
      node = node->next.get();
    }

    auto clonedNode = head.get();
    while (node && clonedNode) {
      clonedNode->next = std::move(node->next);
      node->next = std::move(clonedNode->next);

      clonedNode = clonedNode->next.get();
      node = node->next.get();
    }
  }
};

void test1() {
  ComplexList list;
  auto node1 = &list.append(1);
  auto node2 = &list.append(2);
  auto node3 = &list.append(3);
  auto node4 = &list.append(4);
  auto node5 = &list.append(5);

  list.setSibling(node1, node3);
  list.setSibling(node2, node5);
  list.setSibling(node5, node2);

  ComplexList copy(list);
  assert(list == copy);
}

void test2() {
  ComplexList list;
  auto node1 = &list.append(1);
  auto node2 = &list.append(2);
  auto node3 = &list.append(3);
  auto node4 = &list.append(4);
  auto node5 = &list.append(5);

  list.setSibling(node1, node2);
  list.setSibling(node2, node3);
  list.setSibling(node5, node4);
  list.setSibling(node4, node1);

  ComplexList copy(list);
  assert(list == copy);
}

void test3() {
  ComplexList list;
  auto node1 = &list.append(1);
  ComplexList copy(list);
  assert(list == copy);
}

void test4() {
  ComplexList list;
  ComplexList copy(list);
  assert(list == copy);
}

int main() {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
