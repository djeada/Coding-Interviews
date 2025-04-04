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
#include <unordered_map>

class ComplexList {
public:
  // Make Node publicly accessible.
  struct Node {
    int value;
    std::unique_ptr<Node> next;
    Node* sibling = nullptr;
    explicit Node(int val) : value(val) {}
  };

  ComplexList() = default;

  // Copy constructor: deep-copies the list, preserving sibling relationships.
  ComplexList(const ComplexList &other) {
    if (!other.head)
      return;

    // Map from original nodes to their corresponding cloned nodes.
    std::unordered_map<const Node*, Node*> nodeMap;
    
    // Create the new head.
    head = std::make_unique<Node>(other.head->value);
    nodeMap[other.head.get()] = head.get();
    
    Node* currentNew = head.get();
    const Node* currentOld = other.head.get();
    // Copy the "next" chain.
    while (currentOld->next) {
      currentNew->next = std::make_unique<Node>(currentOld->next->value);
      currentNew = currentNew->next.get();
      currentOld = currentOld->next.get();
      nodeMap[currentOld] = currentNew;
    }
    
    // Set sibling pointers.
    currentOld = other.head.get();
    currentNew = head.get();
    while (currentOld) {
      if (currentOld->sibling)
        currentNew->sibling = nodeMap[currentOld->sibling];
      currentOld = currentOld->next.get();
      currentNew = currentNew->next.get();
    }
  }

  // Append a new node with the given value and return its pointer.
  Node* append(int value) {
    auto newNode = std::make_unique<Node>(value);
    Node* newNodePtr = newNode.get();
    if (!head) {
      head = std::move(newNode);
    } else {
      Node* curr = head.get();
      while (curr->next)
        curr = curr->next.get();
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
    const Node* node1 = l1.head.get();
    const Node* node2 = l2.head.get();
    
    while (node1 && node2) {
      if (node1->value != node2->value)
        return false;
      
      // Check presence/absence of sibling pointers.
      if ((node1->sibling == nullptr) != (node2->sibling == nullptr))
        return false;
      
      // If both nodes have siblings, compare their values.
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
  std::unique_ptr<Node> head;
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
