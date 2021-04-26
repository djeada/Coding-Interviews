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
  Node *temp;

public:
  List();
  ~List();
  void connectNode(Node *next);
  void setCurrent(Node *node);
  // overload stream
  void print();
  void append(int value);
  void remove(int value);
  friend bool operator==(const List &l1, const List &l2);

};

#endif
