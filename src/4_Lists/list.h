#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

class List {
public:
  List();
  List(const List &other);
  ~List();
  bool empty() const;
  unsigned int size() const;
  void connectNodes(unsigned int index1, unsigned int index2);
  void print() const;
  void append(int value);
  int get(unsigned int index) const;
  bool operator==(const List &other) const;

protected:
  struct Node {
    int data;
    std::unique_ptr<Node> next;
  };
  std::unique_ptr<Node> head;
  unsigned int count;
};
