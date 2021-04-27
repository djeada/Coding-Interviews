#ifndef _LIST_H
#define _LIST_H

class List {
protected:
  typedef struct Node {
    int data;
    Node *next;
  } Node;

  Node *head;
  Node *curr;
  unsigned int count;

public:
  List();
  List(const List &other);
  ~List();
  void connectNodes(unsigned int index1, unsigned int index2);
  // overload stream
  unsigned int size();
  int get(unsigned int index);
  bool empty();
  void print();
  void append(int value);
  void remove(int value);
  friend bool operator==(const List &l1, const List &l2);
};

#endif
