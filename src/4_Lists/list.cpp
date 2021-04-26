#include "list.h"
#include <exception>
#include <iostream>

List::List() {
  head = nullptr;
  curr = nullptr;
  temp = nullptr;
}

List::~List() {
  auto node = head;
  while (node) {
    head = head->next;
    delete node;
    node = head;
  }
}

void List::setCurrent(Node *node) { curr = node; }

void List::connectNode(Node *next) {
  if (!curr)
    throw std::out_of_range{"Current node wasn't set!"};

  curr->next = next;
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
}

void List::remove(int value) {
  Node *delPtr = nullptr;
  temp = head;
  curr = head;
  while (curr && curr->data != value) {
    temp = curr;
    curr = curr->next;
  }
  if (curr) {
    delete delPtr;
  } else {
    delPtr = curr;
    curr = curr->next;
    temp->next = curr;
    if (delPtr == head) {
      head = head->next;
      temp = nullptr;
    }
    delete delPtr;
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
