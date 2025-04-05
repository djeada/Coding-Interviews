#include "list.h"
#include <cassert>

class ListWithReversion : public List {
public:

  
void remove(int value) {
  Node *prev = nullptr;
  auto current = head.get();

  while (current && current->data != value) {
    prev = current;
    current = current->next.get();
  }

  if (current && current->data == value) {
    if (prev) {
      prev->next = std::move(current->next);
    } else {
      head = std::move(current->next);
    }
    --count;
  }
}
};

void test1() {
  ListWithReversion list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);

  list.remove(3);

  List expectedResult;
  expectedResult.append(1);
  expectedResult.append(2);
  expectedResult.append(4);
  expectedResult.append(5);

  assert(list == expectedResult);
}

void test2() {
  ListWithReversion list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);

  list.remove(5);

  List expectedResult;
  expectedResult.append(1);
  expectedResult.append(2);
  expectedResult.append(3);
  expectedResult.append(4);

  assert(list == expectedResult);
}

void test3() {
  ListWithReversion list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);

  list.remove(1);

  List expectedResult;
  expectedResult.append(2);
  expectedResult.append(3);
  expectedResult.append(4);
  expectedResult.append(5);

  assert(list == expectedResult);
}

void test4() {
  ListWithReversion list;
  list.append(1);

  list.remove(1);

  List expectedResult;

  assert(list == expectedResult);
}

int main() {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
