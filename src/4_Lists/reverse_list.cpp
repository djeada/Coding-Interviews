#include "list.h"
#include <cassert>

class ListWithReversion : public List {
public:
  ListWithReversion() : List() {}

  void reverse() {
    std::shared_ptr<Node> reversedHead = nullptr;
    std::shared_ptr<Node> prev = nullptr;
    auto node = head;
    while (node) {
      auto next = node->next;

      if (!next) {
        reversedHead = node;
      }

      node->next = prev;
      prev = node;
      node = next;
    }

    head = reversedHead;
  }
};

void test1() {

  ListWithReversion list;

  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);

  List expected;

  expected.append(5);
  expected.append(4);
  expected.append(3);
  expected.append(2);
  expected.append(1);

  list.reverse();

  assert(list == expected);
}

void test2() {
  ListWithReversion list;
  list.append(1);

  List expected;
  expected.append(1);

  list.reverse();

  assert(list == expected);
}

void test3() {
  ListWithReversion list;

  List expected;

  list.reverse();

  assert(list == expected);
}

int main() {
  test1();
  test2();
  test3();

  return 0;
}
