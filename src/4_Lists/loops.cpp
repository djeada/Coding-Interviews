#include "list.h"
#include <cassert>
#include <iostream>
#include <unordered_set>

class ListWithLoops : public List {

  std::unordered_set<Node *> nodes;

public:
  ListWithLoops() : List(){};

  ~ListWithLoops() {
    for (auto &node : nodes)
      delete node;

    head = nullptr;
  }

  void append(int value) {
    auto newNode = new Node;
    newNode->next = nullptr;
    newNode->data = value;

    if (head) {
      curr = head;
      while (curr->next)
        curr = curr->next;

      curr->next = newNode;
    }

    else
      head = newNode;

    nodes.insert(newNode);
  }

  bool hasLoop() {
    if (!head)
      return false;

    auto slow = head->next;
    if (!slow)
      return false;

    auto fast = slow->next;
    while (fast && slow) {
      if (fast == slow)
        return true;

      slow = slow->next;

      fast = fast->next;
      if (fast)
        fast = fast->next;
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
  list.connectNodes(0, 0);

  assert(list.hasLoop());
}

void test3() {
  ListWithLoops list;

  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);

  list.connectNodes(4, 2);

  assert(list.hasLoop());
}

void test4() {
  ListWithLoops list;

  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);

  list.connectNodes(4, 0);

  assert(list.hasLoop());
}

int main() {
  test1();
  test2();
  // test3();
  test4();

  return 0;
}
