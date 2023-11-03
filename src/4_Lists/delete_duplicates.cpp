#include "list.h"
#include <cassert>
#include <unordered_set>

class UniqueList : public List {
public:
  UniqueList() : List() {}

  void deleteDuplication() {
    if (empty())
      return;

    std::unordered_set<int> visited;
    Node *current = head.get();
    Node *previous = nullptr;

    while (current) {
      if (visited.find(current->data) != visited.end()) {
        // Since we don't have access to Node structure and
        // next is a unique_ptr, we can't directly manipulate the pointers.
        // Assuming List class provides a remove method.
        remove(current->data);
      } else {
        visited.insert(current->data);
        previous = current;
      }
      current = previous->next.get();
    }
  }
};

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

  return 0;
}
