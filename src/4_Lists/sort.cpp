#include <cassert>
#include <memory>
#include <iostream>

// Minimal list implementation that uses unique_ptr for automatic memory management.
class List {
public:
  struct Node {
    int data;
    std::unique_ptr<Node> next;
    Node(int d) : data(d), next(nullptr) {}
  };

  std::unique_ptr<Node> head;

  List() : head(nullptr) {}

  // Append a new node with the given data.
  void append(int data) {
    auto newNode = std::make_unique<Node>(data);
    if (!head) {
      head = std::move(newNode);
    } else {
      Node* curr = head.get();
      while (curr->next)
        curr = curr->next.get();
      curr->next = std::move(newNode);
    }
  }

  // Equality operator to compare two lists based on node values.
  friend bool operator==(const List &l1, const List &l2) {
    const Node* n1 = l1.head.get();
    const Node* n2 = l2.head.get();
    while (n1 && n2) {
      if (n1->data != n2->data)
        return false;
      n1 = n1->next.get();
      n2 = n2->next.get();
    }
    return n1 == n2;
  }
};

class ListWithSorting : public List {
public:
  ListWithSorting() : List() {}

  // Insertion sort for the list. Rearranges nodes by moving unique_ptr ownership.
  void sort() {
    if (!head || !head->next)
      return;
    
    // Dummy node simplifies insertion at the beginning.
    auto dummy = std::make_unique<Node>(0);
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
