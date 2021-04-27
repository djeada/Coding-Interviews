#include "list.h"
#include <cassert>
#include <stdexcept>

class ListWithFind : public List {

public:
  ListWithFind() : List() {}

  int findKthToTail(unsigned int k) {
    if (!head)
      throw std::out_of_range("Index out of range!");

    curr = head;
    Node *prev = nullptr;

    for (unsigned int i = 0; i < k; ++i) {

      if (curr->next)
        curr = curr->next;

      else
        throw std::out_of_range("Index out of range!");
    }

    prev = head;
    while (curr->next) {
      curr = curr->next;
      prev = prev->next;
    }

    return prev->data;
  }
};

void test1() {
  ListWithFind list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);

  int k = 0;
  int result = 5;

  assert(list.findKthToTail(k) == result);
}

void test2() {
  ListWithFind list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);

  int k = 4;
  int result = 1;

  assert(list.findKthToTail(k) == result);
}

void test3() {
  ListWithFind list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);

  int k = 1;
  int result = 4;

  assert(list.findKthToTail(k) == result);
}

void test4() {
  ListWithFind list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);

  int k = 10;

  bool exceptionThrown = false;

  try {
    list.findKthToTail(k);
  } catch (...) {
    exceptionThrown = true;
  }

  assert(exceptionThrown);
}

int main() {

  test1();
  test2();
  test3();
  test4();

  return 0;
}
