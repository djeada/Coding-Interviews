#include <cassert>
#include <iostream>
#include <memory>
#include <unordered_set>

// A minimal singly linked list class using unique_ptr for node management.
class List {
public:
  // Node structure used by List.
  struct Node {
    int data;
    std::unique_ptr<Node> next;
    Node(int d) : data(d), next(nullptr) {}
  };

  std::unique_ptr<Node> head;

  List() : head(nullptr) {}

  // Returns true if the list is empty.
  bool empty() const { return head == nullptr; }

  // Append a new node with the given data to the end of the list.
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

  // Remove the first occurrence of the given value.
  void remove(int value) {
    Node* curr = head.get();
    Node* prev = nullptr;
    while (curr) {
      if (curr->data == value) {
        if (!prev) {  // Remove head.
          head = std::move(head->next);
        } else {
          prev->next = std::move(curr->next);
        }
        return;
      }
      prev = curr;
      curr = curr->next.get();
    }
  }

  // Equality operator compares lists node by node.
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

// UniqueList is derived from List and provides deletion of duplicate nodes.
class UniqueList : public List {
public:
  UniqueList() : List() {}

  // Delete duplicate nodes in the list.
  void deleteDuplication() {
    if (empty())
      return;

    std::unordered_set<int> visited;
    Node* current = head.get();
    Node* previous = nullptr;

    while (current) {
      if (visited.find(current->data) != visited.end()) {
        // Duplicate found: remove the node.
        if (!previous) {
          // If current is at head (shouldn't happen after first unique value),
          // update head.
          head = std::move(current->next);
          current = head.get();
        } else {
          previous->next = std::move(current->next);
          current = previous->next.get();
        }
      } else {
        // First occurrence: mark as visited and move forward.
        visited.insert(current->data);
        previous = current;
        current = current->next.get();
      }
    }
  }
};

// ------------------- Test Cases -------------------

void test1() {
  UniqueList duplicateList;
  duplicateList.append(1);
  duplicateList.append(2);
  duplicateList.append(3);
  duplicateList.append(4);
  duplicateList.append(4);
  duplicateList.append(5);

  UniqueList uniqueList;
  uniqueList.append(1);
  uniqueList.append(2);
  uniqueList.append(3);
  uniqueList.append(4);
  uniqueList.append(5);

  duplicateList.deleteDuplication();
  assert(duplicateList == uniqueList);
}

void test2() {
  UniqueList duplicateList;
  duplicateList.append(1);
  duplicateList.append(2);
  duplicateList.append(3);
  duplicateList.append(4);
  duplicateList.append(5);

  UniqueList uniqueList;
  uniqueList.append(1);
  uniqueList.append(2);
  uniqueList.append(3);
  uniqueList.append(4);
  uniqueList.append(5);

  duplicateList.deleteDuplication();
  assert(duplicateList == uniqueList);
}

void test3() {
  UniqueList duplicateList;
  duplicateList.append(1);
  duplicateList.append(1);
  duplicateList.append(1);
  duplicateList.append(1);
  duplicateList.append(2);

  UniqueList uniqueList;
  uniqueList.append(1);
  uniqueList.append(2);

  duplicateList.deleteDuplication();
  assert(duplicateList == uniqueList);
}

void test4() {
  UniqueList duplicateList;
  duplicateList.append(1);
  duplicateList.append(1);
  duplicateList.append(1);
  duplicateList.append(1);
  duplicateList.append(1);

  UniqueList uniqueList;
  uniqueList.append(1);

  duplicateList.deleteDuplication();
  assert(duplicateList == uniqueList);
}

int main() {
  test1();
  test2();
  test3();
  test4();
  std::cout << "All tests passed!\n";
  return 0;
}
