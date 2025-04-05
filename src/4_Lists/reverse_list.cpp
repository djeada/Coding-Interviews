#include "list.h"
#include <cassert>
#include <iostream>
#include <memory>

class ListWithReversion : public List {
public:
  ListWithReversion() : List() {}

  // Reverse the list by re-linking the unique_ptr nodes.
  void reverse() {
    std::unique_ptr<Node> new_head = nullptr;
    // While there are nodes in the original list:
    while (head) {
      // Detach the first node from the list.
      auto temp = std::move(head->next);
      // Insert it at the front of the new list.
      head->next = std::move(new_head);
      new_head = std::move(head);
      // Continue with the rest of the original list.
      head = std::move(temp);
    }
    head = std::move(new_head);
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

  std::cout << "All tests passed!\n";
  return 0;
}
