#include "list.h"
#include <cassert>
#include <memory>
#include <iostream>

class ListWithSorting : public List {
public:
  ListWithSorting() : List() {}

  // Insertion sort for the list. Rearranges nodes by moving unique_ptr ownership.
  void sort() {
    if (!head || !head->next)
      return;
    
    // Create a dummy node using the default constructor and manually set its data.
    auto dummy = std::make_unique<Node>();
    dummy->data = 0;
    dummy->next = std::move(head);

    // lastSorted points to the last node in the sorted portion.
    Node* lastSorted = dummy->next.get();
    
    // While there is an unsorted node available.
    while (lastSorted && lastSorted->next) {
      // If the next node should be inserted at the beginning.
      if (lastSorted->next->data < dummy->next->data) {
        // Remove the node to be inserted.
        auto toInsert = std::move(lastSorted->next);
        lastSorted->next = std::move(toInsert->next);
        // Insert at the beginning.
        toInsert->next = std::move(dummy->next);
        dummy->next = std::move(toInsert);
      } else {
        // Find the correct insertion point within the sorted portion.
        Node* prev = dummy->next.get();
        // Traverse until we find a node with a greater value.
        while (prev != lastSorted && prev->next && prev->next->data < lastSorted->next->data) {
          prev = prev->next.get();
        }
        // If insertion is not at the end, extract and reinsert the node.
        if (prev != lastSorted) {
          auto toInsert = std::move(lastSorted->next);
          lastSorted->next = std::move(toInsert->next);
          toInsert->next = std::move(prev->next);
          prev->next = std::move(toInsert);
        } else {
          // Otherwise, the node is already in the right place.
          lastSorted = lastSorted->next.get();
        }
      }
    }
    head = std::move(dummy->next);
  }
};

void test1() {
  ListWithSorting list;
  list.append(2);
  list.append(4);
  list.append(5);
  list.append(1);
  list.append(3);

  List expected;
  expected.append(1);
  expected.append(2);
  expected.append(3);
  expected.append(4);
  expected.append(5);

  list.sort();
  assert(list == expected);
}

void test2() {
  ListWithSorting list;
  list.append(5);
  list.append(4);
  list.append(3);
  list.append(2);
  list.append(1);

  List expected;
  expected.append(1);
  expected.append(2);
  expected.append(3);
  expected.append(4);
  expected.append(5);

  list.sort();
  assert(list == expected);
}

void test3() {
  ListWithSorting list;
  list.append(1);

  List expected;
  expected.append(1);

  list.sort();
  assert(list == expected);
}

void test4() {
  ListWithSorting list;
  List expected;
  list.sort();
  assert(list == expected);
}

int main() {
  test1();
  test2();
  test3();
  test4();

  std::cout << "All tests passed!\n";
  return 0;
}
