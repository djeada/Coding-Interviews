#include "list.h"
#include <cassert>

class ListWithSorting : public List {

public:
  ListWithSorting() : List() {}

  void sort() {
    if (!head)
      return;

    auto lastSorted = head;
    auto toBeSorted = lastSorted->next;
    while (toBeSorted) {
      if (toBeSorted->data < head->data) {
        lastSorted->next = toBeSorted->next;
        toBeSorted->next = head;
        head = toBeSorted;
      } else {
        auto pNode = head;
        while (pNode != lastSorted && pNode->next->data < toBeSorted->data) {
          pNode = pNode->next;
        }

        if (pNode != lastSorted) {
          lastSorted->next = toBeSorted->next;
          toBeSorted->next = pNode->next;
          pNode->next = toBeSorted;
        } else
          lastSorted = lastSorted->next;
      }

      toBeSorted = lastSorted->next;
    }
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

  return 0;
}
