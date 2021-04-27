#include "list.h"
#include <exception>
#include <iostream>

List::List() : head(nullptr), curr(nullptr), count(0) {}

List::List(const List &other) : head(nullptr), curr(nullptr), count(0) {
  auto node = other.head;
  while (node) {
    append(node->data);
    node = node->next;
  }
}

List::~List() {
  auto node = head;
  while (node) {
    head = head->next;
    delete node;
    node = head;
  }
}

bool List::empty() { return head == nullptr; }

unsigned int List::size() { return count; }

void List::connectNodes(unsigned int index1, unsigned int index2) {

  Node *node1 = nullptr;
  Node *node2 = nullptr;

  unsigned int counter = 0;

  auto node = head;

  if (counter == index1)
    node1 = node;

  if (counter == index2)
    node2 = node;

  while (node && counter < std::max(index1, index2)) {
    node = node->next;
    counter++;
    if (counter == index1)
      node1 = node;

    if (counter == index2)
      node2 = node;
  }

  if (!node1 || !node2)
    throw std::out_of_range{"Index out of range!"};

  node1->next = node2;
}

void List::print() {
  std::cout << "PrintList starts." << std::endl;

  auto node = head;
  while (node) {
    std::cout << node->data << " ";
    node = node->next;
  }

  std::cout << std::endl;
}

void List::append(int value) {
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

  count++;
}

int List::get(unsigned int index) {

  unsigned int counter = 0;
  auto node = head;

  while (node && counter <= index) {

    if (counter == index)
      return node->data;

    node = node->next;
    counter++;
  }

  throw std::out_of_range{"Index out of range!"};
}

void List::remove(int value) {
  Node *prev = nullptr;
  curr = head;
  while (curr && curr->data != value) {
    prev = curr;
    curr = curr->next;
  }
  if (curr && curr->data == value) {

    if (curr == head) {
      if (head->next)
        head = head->next;
      else
        head = nullptr;
    } else if (prev) {
      if (curr->next)
        prev->next = curr->next;
      else
        prev->next = nullptr;
    }
    delete curr;
    curr = nullptr;
    count--;
  }
}

bool operator==(const List &l1, const List &l2) {

  auto node1 = l1.head;
  auto node2 = l2.head;

  while (node1 && node2) {
    if (node1->data != node2->data)
      return false;

    node1 = node1->next;
    node2 = node2->next;
  }

  return node1 == node2;
}
