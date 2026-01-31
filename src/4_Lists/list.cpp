#include "list.h"

#include <utility>

List::List() : head(nullptr), count(0) {}

List::List(const List &other) : head(nullptr), count(0) {
  for (auto node = other.head.get(); node; node = node->next.get()) {
    append(node->data);
  }
}

List::List(List &&other) noexcept
    : head(std::move(other.head)), count(other.count) {
  other.count = 0;
}

List::~List() = default;

List &List::operator=(const List &other) {
  if (this == &other) {
    return *this;
  }
  List temp(other);
  swap(temp);
  return *this;
}

List &List::operator=(List &&other) noexcept {
  if (this == &other) {
    return *this;
  }
  head = std::move(other.head);
  count = other.count;
  other.count = 0;
  return *this;
}

bool List::empty() const { return !head; }

unsigned int List::size() const { return count; }

void List::clear() {
  head.reset();
  count = 0;
}

List::Node *List::nodeAt(unsigned int index) {
  if (index >= count) {
    return nullptr;
  }
  auto node = head.get();
  for (unsigned int i = 0; i < index && node; ++i) {
    node = node->next.get();
  }
  return node;
}

const List::Node *List::nodeAt(unsigned int index) const {
  if (index >= count) {
    return nullptr;
  }
  auto node = head.get();
  for (unsigned int i = 0; i < index && node; ++i) {
    node = node->next.get();
  }
  return node;
}

std::unique_ptr<List::Node> *List::ownerAt(unsigned int index) {
  if (index >= count) {
    return nullptr;
  }
  auto *owner = &head;
  for (unsigned int i = 0; i < index; ++i) {
    if (!owner->get()) {
      return nullptr;
    }
    owner = &((*owner)->next);
  }
  return owner;
}

void List::connectNodes(unsigned int index1, unsigned int index2) {
  if (index1 == index2 || index1 >= count || index2 >= count) {
    throw std::out_of_range{"Index out of range!"};
  }

  if (index1 < index2) {
    auto *owner1 = ownerAt(index1);
    auto *owner2 = ownerAt(index2);
    if (!owner1 || !owner2) {
      throw std::out_of_range{"Index out of range!"};
    }
    Node *node1 = owner1->get();
    Node *node2 = owner2->get();
    if (!node1 || !node2) {
      throw std::out_of_range{"Index out of range!"};
    }
    if (node1->next.get() == node2) {
      return;
    }
    auto moving = std::move(*owner2);
    *owner2 = std::move(moving->next);
    moving->next = std::move(node1->next);
    node1->next = std::move(moving);
    return;
  }

  auto *owner2 = ownerAt(index2);
  if (!owner2) {
    throw std::out_of_range{"Index out of range!"};
  }
  auto moving = std::move(*owner2);
  *owner2 = std::move(moving->next);

  auto *owner1 = ownerAt(index1 - 1);
  if (!owner1) {
    throw std::out_of_range{"Index out of range!"};
  }
  Node *node1 = owner1->get();
  if (!node1) {
    throw std::out_of_range{"Index out of range!"};
  }
  moving->next = std::move(node1->next);
  node1->next = std::move(moving);
}

void List::print() const {
  std::cout << "PrintList starts.\n";
  for (auto node = head.get(); node; node = node->next.get()) {
    std::cout << node->data << " ";
  }
  std::cout << std::endl;
}

void List::append(int value) {
  auto newNode = std::make_unique<Node>(value);

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
  auto node = nodeAt(index);
  if (!node) {
    throw std::out_of_range{"Index out of range!"};
  }

  return node->data;
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

void List::swap(List &other) noexcept {
  std::swap(head, other.head);
  std::swap(count, other.count);
}
