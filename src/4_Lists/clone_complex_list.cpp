/*
 * DEEP COPY OF A COMPLEX LINKED LIST WITH SIBLING POINTERS
 *
 * This program defines a class named ComplexList that represents a singly linked
 * list where each node has an integer value, a pointer to the next node, and an
 * additional "sibling" pointer that can reference any other node in the list.
 * The class supports operations for appending nodes, setting sibling pointers, and
 * performing a deep copy of the entire list while preserving the sibling relationships.
 *
 * The deep copy is implemented in the copy constructor, which:
 * - Traverses the original list to create new nodes and maps each original node to its copy.
 * - Iterates again to correctly set the sibling pointers in the copied list.
 *
 * ASCII Illustration:
 *
 *    Original List:      Copied List:
 *
 *      1  -->  2  -->  3       1  -->  2  -->  3
 *       \       \             \       \
 *        v       v             v       v
 *        3       5             3       5
 *
 * Example:
 * Input List:
 *    Node values: 1 -> 2 -> 3 -> 4 -> 5
 *    Sibling relationships: 
 *      - 1's sibling -> 3
 *      - 2's sibling -> 5
 *      - 5's sibling -> 2
 *
 * When copied, both lists will have the same structure and sibling connections.
 */

#include "list.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <unordered_map>

// ComplexList inherits from List (defined in list.h) and adds a sibling pointer to each node.
class ComplexList : public List {
public:
  // Our node type extends the base List::Node.
  struct Node : public List::Node {
    Node() : List::Node(), sibling(nullptr) {}
    explicit Node(int val) : List::Node(), sibling(nullptr) { this->data = val; }
    // Pointer to any other node in the list.
    Node* sibling;
  };

  ComplexList() : List() {}

  // Copy constructor: deep-copies the list, preserving sibling relationships.
  ComplexList(const ComplexList &other) : List() {
    if (!other.head)
      return;
    
    // Map from original nodes to their corresponding cloned nodes.
    std::unordered_map<const Node*, Node*> nodeMap;
    
    // Create the new head.
    head = std::unique_ptr<List::Node>(static_cast<List::Node*>(new Node(static_cast<const Node*>(other.head.get())->data)));
    nodeMap[static_cast<const Node*>(other.head.get())] = static_cast<Node*>(head.get());
    
    Node* currentNew = static_cast<Node*>(head.get());
    const Node* currentOld = static_cast<const Node*>(other.head.get());
    // Copy the "next" chain.
    while (currentOld->next) {
      currentNew->next = std::unique_ptr<List::Node>(static_cast<List::Node*>(new Node(static_cast<const Node*>(currentOld->next.get())->data)));
      currentNew = static_cast<Node*>(currentNew->next.get());
      currentOld = static_cast<const Node*>(currentOld->next.get());
      nodeMap[currentOld] = currentNew;
    }
    
    // Set sibling pointers.
    currentOld = static_cast<const Node*>(other.head.get());
    currentNew = static_cast<Node*>(head.get());
    while (currentOld) {
      if (currentOld->sibling)
        currentNew->sibling = nodeMap[static_cast<const Node*>(currentOld->sibling)];
      currentOld = static_cast<const Node*>(currentOld->next.get());
      currentNew = static_cast<Node*>(currentNew->next.get());
    }
  }

  // Append a new node with the given value.
  // Returns a pointer to the new node (of our Node type).
  Node* append(int value) {
    auto newNode = std::unique_ptr<List::Node>(static_cast<List::Node*>(new Node(value)));
    Node* newNodePtr = static_cast<Node*>(newNode.get());
    if (!head) {
      head = std::move(newNode);
    } else {
      Node* curr = static_cast<Node*>(head.get());
      while (curr->next)
        curr = static_cast<Node*>(curr->next.get());
      curr->next = std::move(newNode);
    }
    return newNodePtr;
  }

  // Set the sibling pointer for the given node.
  void setSibling(Node* node, Node* sibling) {
    if (node)
      node->sibling = sibling;
  }

  // Equality operator for testing purposes.
  friend bool operator==(const ComplexList &l1, const ComplexList &l2) {
    const Node* node1 = static_cast<const Node*>(l1.head.get());
    const Node* node2 = static_cast<const Node*>(l2.head.get());
    
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
      
      node1 = static_cast<const Node*>(node1->next.get());
      node2 = static_cast<const Node*>(node2->next.get());
    }
    
    return node1 == node2;
  }
};

// ----- Test Cases -----

void test1() {
  ComplexList list;
  auto node1 = list.append(1);
  auto node2 = list.append(2);
  auto node3 = list.append(3);
  auto node4 = list.append(4);
  auto node5 = list.append(5);

  list.setSibling(node1, node3);
  list.setSibling(node2, node5);
  list.setSibling(node5, node2);

  ComplexList copy(list);
  assert(list == copy);
}

void test2() {
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
  assert(list == copy);
}

void test3() {
  ComplexList list;
  auto node1 = list.append(1);
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
  std::cout << "All tests passed!\n";
  return 0;
}
