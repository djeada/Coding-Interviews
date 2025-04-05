#include "list.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <unordered_set>


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
