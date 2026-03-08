/*
 * Task: Deep copy a linked list with sibling pointers.
 *
 * COPY LIST WITH RANDOM (SIBLING) POINTER
 *
 * Problem:
 * Given a linked list where each node has `next` and `sibling` pointers,
 * create a deep copy of the list. The copied nodes must be new objects, and
 * every copied sibling pointer must reference the corresponding copied node.
 *
 * Constraints:
 * - 0 <= n <= 10^5
 * - Node values are 32-bit signed integers.
 * - `sibling` is either null or points to any node in the same list.
 *
 * Example 1:
 * Input: values = [1,2,3,4,5], sibling = {1->3, 2->5, 5->2}
 * Output: deep-copied list with identical `next` and `sibling` structure
 *
 * Example 2:
 * Input: values = [1], sibling = {}
 * Output: [1] (copied node, not the same address)
 */

#include "list.h"
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

// ComplexList inherits from List (defined in list.h) and adds a sibling pointer
// to each node.
class ComplexList : public List {
public:
  // Our node type extends the base List::Node.
  struct Node : public List::Node {
    Node() : List::Node(), sibling(nullptr) {}
    explicit Node(int val) : List::Node(), sibling(nullptr) {
      this->data = val;
    }
    // Pointer to any other node in the list.
    Node *sibling;
  };

  ComplexList() : List() {}

  // Copy constructor: deep-copies the list, preserving sibling relationships.
  ComplexList(const ComplexList &other) : List() {
    if (!other.head)
      return;

    // Map from original nodes to their corresponding cloned nodes.
    std::unordered_map<const Node *, Node *> nodeMap;

    // Create the new head.
    head = std::unique_ptr<List::Node>(static_cast<List::Node *>(
        new Node(static_cast<const Node *>(other.head.get())->data)));
    count = 1;
    nodeMap[static_cast<const Node *>(other.head.get())] =
        static_cast<Node *>(head.get());

    Node *currentNew = static_cast<Node *>(head.get());
    const Node *currentOld = static_cast<const Node *>(other.head.get());
    // Copy the "next" chain.
    while (currentOld->next) {
      currentNew->next = std::unique_ptr<List::Node>(static_cast<List::Node *>(
          new Node(static_cast<const Node *>(currentOld->next.get())->data)));
      currentNew = static_cast<Node *>(currentNew->next.get());
      currentOld = static_cast<const Node *>(currentOld->next.get());
      nodeMap[currentOld] = currentNew;
      ++count;
    }

    // Set sibling pointers.
    currentOld = static_cast<const Node *>(other.head.get());
    currentNew = static_cast<Node *>(head.get());
    while (currentOld) {
      if (currentOld->sibling)
        currentNew->sibling =
            nodeMap[static_cast<const Node *>(currentOld->sibling)];
      currentOld = static_cast<const Node *>(currentOld->next.get());
      currentNew = static_cast<Node *>(currentNew->next.get());
    }
  }

  ComplexList &operator=(const ComplexList &other) {
    if (this == &other)
      return *this;
    ComplexList temp(other);
    swap(temp);
    return *this;
  }

  ComplexList(ComplexList &&other) noexcept = default;
  ComplexList &operator=(ComplexList &&other) noexcept = default;

  // Append a new node with the given value.
  // Returns a pointer to the new node (of our Node type).
  Node *append(int value) {
    auto newNode =
        std::unique_ptr<List::Node>(static_cast<List::Node *>(new Node(value)));
    Node *newNodePtr = static_cast<Node *>(newNode.get());
    if (!head) {
      head = std::move(newNode);
    } else {
      Node *curr = static_cast<Node *>(head.get());
      while (curr->next)
        curr = static_cast<Node *>(curr->next.get());
      curr->next = std::move(newNode);
    }
    ++count;
    return newNodePtr;
  }

  // Set the sibling pointer for the given node.
  void setSibling(Node *node, Node *sibling) {
    if (node)
      node->sibling = sibling;
  }

  // Equality operator for testing purposes.
  friend bool operator==(const ComplexList &l1, const ComplexList &l2) {
    const Node *node1 = static_cast<const Node *>(l1.head.get());
    const Node *node2 = static_cast<const Node *>(l2.head.get());

    while (node1 && node2) {
      if (node1->data != node2->data)
        return false;

      // Check presence/absence of sibling pointers.
      if ((node1->sibling == nullptr) != (node2->sibling == nullptr))
        return false;

      // If both nodes have siblings, compare their values.
      if (node1->sibling && node2->sibling) {
        if (node1->sibling->data != node2->sibling->data)
          return false;
      }

      node1 = static_cast<const Node *>(node1->next.get());
      node2 = static_cast<const Node *>(node2->next.get());
    }

    return node1 == node2;
  }
};

int main() {
  int total = 0;
  int failed = 0;

  auto expectTrue = [&](bool condition, const std::string &label) {
    ++total;
    if (condition) {
      std::cout << "[PASS] " << label << "\n";
      return;
    }
    ++failed;
    std::cout << "[FAIL] " << label << " expected=true got=false\n";
  };

  auto summary = [&]() {
    std::cout << "Tests: " << total - failed << " passed, " << failed
              << " failed, " << total << " total\n";
  };

  {
    ComplexList list;
    auto node1 = list.append(1);
    auto node2 = list.append(2);
    auto node3 = list.append(3);
    list.append(4);
    auto node5 = list.append(5);

    list.setSibling(node1, node3);
    list.setSibling(node2, node5);
    list.setSibling(node5, node2);

    ComplexList copy(list);
    expectTrue(list == copy, "clone test1");
  }

  {
    ComplexList list;
    auto node1 = list.append(1);
    auto node2 = list.append(2);
    auto node3 = list.append(3);
    auto node4 = list.append(4);
    auto node5 = list.append(5);

    list.setSibling(node1, node2);
    list.setSibling(node2, node3);
    list.setSibling(node5, node4);
    list.setSibling(node4, node1);

    ComplexList copy(list);
    expectTrue(list == copy, "clone test2");
  }

  {
    ComplexList list;
    list.append(1);
    ComplexList copy(list);
    expectTrue(list == copy, "clone test3");
  }

  {
    ComplexList list;
    ComplexList copy(list);
    expectTrue(list == copy, "clone test4");
  }

  summary();
  return 0;
}
