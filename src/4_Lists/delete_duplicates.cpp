#include "list.h"
#include <cassert>
#include <unordered_set>

class ListWithDeletion : public List {

public:
  ListWithDeletion() : List() {}

  void deleteDuplication() {
    if (!head)
      return;
    std::unordered_set<int> visited;

    curr = head;
    Node *prev = nullptr;
    while (curr) {
      if (visited.find(curr->data) != visited.end()) {
        prev->next = curr->next;
        delete curr;
      } else {
        visited.insert(curr->data);
        prev = curr;
      }
      curr = prev->next;
    }
  }
};

void test1() {
  ListWithDeletion duplicateList;

  duplicateList.append(1);
  duplicateList.append(2);
  duplicateList.append(3);
  duplicateList.append(4);
  duplicateList.append(4);
  duplicateList.append(5);

  ListWithDeletion uniqueList;

  uniqueList.append(1);
  uniqueList.append(2);
  uniqueList.append(3);
  uniqueList.append(4);
  uniqueList.append(5);

  duplicateList.deleteDuplication();

  assert(duplicateList == uniqueList);
}

void test2() {
  ListWithDeletion duplicateList;

  duplicateList.append(1);
  duplicateList.append(2);
  duplicateList.append(3);
  duplicateList.append(4);
  duplicateList.append(5);

  ListWithDeletion uniqueList;

  uniqueList.append(1);
  uniqueList.append(2);
  uniqueList.append(3);
  uniqueList.append(4);
  uniqueList.append(5);

  duplicateList.deleteDuplication();

  assert(duplicateList == uniqueList);
}

void test3() {
  ListWithDeletion duplicateList;

  duplicateList.append(1);
  duplicateList.append(1);
  duplicateList.append(1);
  duplicateList.append(1);
  duplicateList.append(2);

  ListWithDeletion uniqueList;

  uniqueList.append(1);
  uniqueList.append(2);

  duplicateList.deleteDuplication();

  assert(duplicateList == uniqueList);
}

void test4() {
  ListWithDeletion duplicateList;

  duplicateList.append(1);
  duplicateList.append(1);
  duplicateList.append(1);
  duplicateList.append(1);
  duplicateList.append(1);

  ListWithDeletion uniqueList;

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
