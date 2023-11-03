#include "list.h"

List::List() : head(nullptr), count(0) {}

List::List(const List &other) : head(nullptr), count(0) {
  for (auto node = other.head.get(); node; node = node->next.get()) {
    append(node->data);
  }
}

List::~List() = default;

bool List::empty() const { return !head; }

unsigned int List::size() const { return count; }

void List::connectNodes(unsigned int index1, unsigned int index2) {
  if (index1 == index2 || index1 >= count || index2 >= count) {
    throw std::out_of_range{"Index out of range!"};
  }

  Node *node1 = nullptr;
  Node *node2 = nullptr;

  auto node = head.get();
  for (unsigned int i = 0; i <= std::max(index1, index2) && node; ++i) {
    if (i == index1)
      node1 = node;
    if (i == index2)
      node2 = node;
    node = node->next.get();
  }

  if (!node1 || !node2) {
    throw std::out_of_range{"Index out of range!"};
  }

  node1->next = std::move(node2->next);
}

void List::print() const {
  std::cout << "PrintList starts.\n";
  for (auto node = head.get(); node; node = node->next.get()) {
    std::cout << node->data << " ";
  }
  std::cout << std::endl;
}

void List::append(int value) {
  auto newNode = std::make_unique<Node>();
  newNode->data = value;

  Node *current = head.get();
  while (current && current->next) {
    current = current->next.get();
  }

  if (current) {
    current->next = std::move(newNode);
  } else {
    head = std::move(newNode);
  }

  ++count;
}

int List::get(unsigned int index) const {
  if (index >= count) {
    throw std::out_of_range{"Index out of range!"};
  }

  auto node = head.get();
  for (unsigned int i = 0; i < index; ++i) {
    node = node->next.get();
  }

  return node->data;
}

void List::remove(int value) {
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

bool List::operator==(const List &other) const {
  auto node1 = head.get();
  auto node2 = other.head.get();

  while (node1 && node2) {
    if (node1->data != node2->data)
      return false;
    node1 = node1->next.get();
    node2 = node2->next.get();
  }

  return !node1 && !node2;
}
