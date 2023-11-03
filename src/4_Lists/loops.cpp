#include "list.h"
#include <cassert>
#include <iostream>
#include <unordered_set>

class ListWithLoops : public List {
public:
  ListWithLoops() : List() {}

  void append(int value) { List::append(value); }

  bool hasLoop() {
    if (empty())
      return false;

    auto slow = head.get();
    auto fast = head.get();

    while (fast && fast->next) {
      slow = slow->next.get();
      fast = fast->next->next.get();

      if (fast == slow)
        return true;
    }

    return false;
  }
};

void test1() {
  ListWithLoops list;
  list.append(1);
  assert(!list.hasLoop());
}

void test2() {
  ListWithLoops list;
  list.append(1);
  list.connectNodes(0, 0); // Assuming List class has a method to connect nodes
  assert(list.hasLoop());
}

void test3() {
  ListWithLoops list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);
  list.connectNodes(4, 2); // Assuming List class has a method to connect nodes
  assert(list.hasLoop());
}

void test4() {
  ListWithLoops list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);
  list.connectNodes(4, 0); // Assuming List class has a method to connect nodes
  assert(list.hasLoop());
}

int main() {
  test1();
  test2();
  test3();
  test4();
  return 0;
}
