#include <cassert>
#include <iostream>
#include <memory>

class List {
public:
  struct Node {
    int data;
    std::unique_ptr<Node> next;
    Node(int d) : data(d), next(nullptr) {}
  };

  std::unique_ptr<Node> head;

  List() : head(nullptr) {}

  // Append a new node with the given data.
  void append(int data) {
    auto newNode = std::make_unique<Node>(data);
    if (!head) {
      head = std::move(newNode);
    } else {
      Node* curr = head.get();
      while (curr->next)
        curr = curr->next.get();
      curr->next = std::move(newNode);
    }
  }

  // Equality operator compares lists node by node.
  friend bool operator==(const List &l1, const List &l2) {
    const Node* n1 = l1.head.get();
    const Node* n2 = l2.head.get();
    while (n1 && n2) {
      if (n1->data != n2->data)
        return false;
      n1 = n1->next.get();
      n2 = n2->next.get();
    }
    return n1 == n2;
  }
};

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
