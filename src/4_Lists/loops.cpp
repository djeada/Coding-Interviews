#include "list.h"
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <algorithm> // for std::max

class ListWithLoops : public List {
public:
  ListWithLoops() : List() {}

  // Expose the append method.
  void append(int value) { List::append(value); }

  // Connect the node at index 'from' to the node at index 'to'
  // (0-indexed). Throws std::out_of_range if indices are invalid.
  void connectNodes(int from, int to) {
    // Use size() (which returns count) instead of a non-existent size_
    if (from < 0 || static_cast<unsigned>(from) >= size() ||
        to   < 0 || static_cast<unsigned>(to) >= size()) {
      throw std::out_of_range("Index out of range!");
    }
    Node* fromNode = getNode(from);
    Node* toNode   = getNode(to);
    if (!fromNode || !toNode) {
      throw std::runtime_error("Unexpected null node encountered.");
    }
    // WARNING:
    // This hack “connects” the nodes by releasing the unique_ptr in fromNode->next
    // and then resetting it with a raw pointer that is already owned elsewhere.
    // This deliberately creates a loop for testing hasLoop(), but it will
    // confuse unique_ptr ownership and can cause double deletion.
    fromNode->next.release();
    fromNode->next.reset(toNode);
  }

  // Check for a loop using Floyd's algorithm.
  bool hasLoop() {
    if (empty())
      return false;
    
    // Initialize with raw pointers from the unique_ptrs.
    Node* slow = head.get();
    Node* fast = head.get();
    
    while (fast && fast->next) {
      slow = slow->next.get();
      fast = (fast->next->next ? fast->next->next.get() : nullptr);
      if (slow == fast)
        return true;
    }
    
    return false;
  }

private:
  // Helper method to traverse the list and return the node at the given index.
  Node* getNode(int index) {
    if (index < 0 || static_cast<unsigned>(index) >= size()) {
      return nullptr;
    }
    Node* current = head.get();
    for (int i = 0; i < index; ++i) {
      current = current->next.get();
    }
    return current;
  }
};
