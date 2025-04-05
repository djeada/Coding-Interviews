#include "list.h"
#include <cassert>
#include <iostream>
#include <stdexcept>

// Derived class that exposes a loop-detection method.
class ListWithLoops : public List {
public:
  ListWithLoops() : List() {}

  // Expose the append method.
  void append(int value) { List::append(value); }
  // Connect the node at index 'from' to the node at index 'to'
  // (0-indexed). Throws std::out_of_range if indices are invalid.
  void connectNodes(int from, int to) {
    if (from < 0 || from >= size_ || to < 0 || to >= size_) {
      throw std::out_of_range("Index out of range!");
    }
    Node* fromNode = getNode(from);
    Node* toNode = getNode(to);
    if (!fromNode || !toNode) {
      throw std::runtime_error("Unexpected null node encountered.");
    }
    // Connect 'from' node to 'to' node, forming a loop.
    fromNode->next = toNode;
  }
  // Check for a loop using Floyd's algorithm.
  bool hasLoop() {
    if (empty())
      return false;
    
    Node* slow = head;
    Node* fast = head;
    
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
      if (slow == fast)
        return true;
    }
    
    return false;
  }
};

// Test cases.
void test1() {
  ListWithLoops list;
  list.append(1);
  // Single node should not have a loop.
  assert(!list.hasLoop());
}

void test2() {
  ListWithLoops list;
  list.append(1);
  // Connect the only node to itself to form a loop.
  list.connectNodes(0, 0);
  assert(list.hasLoop());
}

void test3() {
  ListWithLoops list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);
  // Connect the last node (index 4) to the node at index 2.
  list.connectNodes(4, 2);
  assert(list.hasLoop());
}

void test4() {
  ListWithLoops list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);
  // Connect the last node (index 4) to the first node (index 0).
  list.connectNodes(4, 0);
  assert(list.hasLoop());
}

int main() {
  test1();
  test2();
  test3();
  test4();
  std::cout << "All tests passed!\n";
  return 0;
}
