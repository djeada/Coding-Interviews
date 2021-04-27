#include <cassert>

class ComplexList {

  typedef struct ComplexNode {
    int value;
    ComplexNode *next;
    ComplexNode *sibling;
  } ComplexNode;

  ComplexNode *head;

public:
  ComplexList() { head = nullptr; }

  ComplexList(const ComplexList &other) {
    cloneNodes(other.head);
    connectSiblingNodes(other.head);
    reconnectNodes(other.head);
  }

  ~ComplexList() {
    auto node = head;
    while (node) {
      head = head->next;
      delete node;
      node = head;
    }
  }

  void cloneNodes(ComplexNode *otherHead) {

    auto node = otherHead;

    while (node) {
      auto clonedNode = new ComplexNode();
      clonedNode->value = node->value;
      clonedNode->next = node->next;
      clonedNode->sibling = nullptr;

      node->next = clonedNode;
      node = clonedNode->next;
    }
  }

  void connectSiblingNodes(ComplexNode *otherHead) {

    auto node = otherHead;

    while (node) {
      auto clonedNode = node->next;

      if (node->sibling) {
        clonedNode->sibling = node->sibling->next;
      }

      node = clonedNode->next;
    }
  }

  void reconnectNodes(ComplexNode *otherHead) {

    head = nullptr;
    ComplexNode *clonedNode = nullptr;
    auto node = otherHead;

    if (node) {
      head = clonedNode = node->next;
      node->next = clonedNode->next;
      node = node->next;
    }

    while (node) {
      clonedNode->next = node->next;
      clonedNode = clonedNode->next;
      node->next = clonedNode->next;
      node = node->next;
    }
  }

  ComplexNode *append(int value) {
    auto newNode = new ComplexNode();
    newNode->next = nullptr;
    newNode->sibling = nullptr;
    newNode->value = value;

    if (head) {
      auto curr = head;
      while (curr->next)
        curr = curr->next;

      curr->next = newNode;
    }

    else
      head = newNode;

    return newNode;
  }

  void setSibling(ComplexNode *node, ComplexNode *sibling) {
    if (node)
      node->sibling = sibling;
  }

  friend bool operator==(const ComplexList &l1, const ComplexList &l2) {

    auto node1 = l1.head;
    auto node2 = l2.head;

    while (node1 && node2) {

      if (node1->value != node2->value)
        return false;

      if ((node1->sibling == nullptr) != (node2->sibling == nullptr))
        return false;

      if (node1->sibling && node2->sibling) {
        if (node1->sibling->value != node2->sibling->value)
          return false;
      }

      node1 = node1->next;
      node2 = node2->next;
    }

    return node1 == node2;
  }
};

void test1() {
  ComplexList list;
  auto node1 = list.append(1);
  auto node2 = list.append(2);
  auto node3 = list.append(3);
  auto node4 = list.append(4);
  auto node5 = list.append(5);

  list.setSibling(node1, node3);
  list.setSibling(node2, node5);
  list.setSibling(node5, node2);

  ComplexList copy(list);
  if (list == copy)
    assert(list == copy);
}

void test2() {
  ComplexList list;
  auto node1 = list.append(1);
  auto node2 = list.append(2);
  auto node3 = list.append(3);
  auto node4 = list.append(4);
  auto node5 = list.append(5);

  list.setSibling(node1, node2);
  list.setSibling(node2, node3);
  list.setSibling(node5, node4);
  list.setSibling(node4, node1);

  ComplexList copy(list);
  assert(list == copy);
}

void test3() {
  ComplexList list;
  auto node1 = list.append(1);
  ComplexList copy(list);
  assert(list == copy);
}

void test4() {
  ComplexList list;
  ComplexList copy(list);
  assert(list == copy);
}

int main() {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
