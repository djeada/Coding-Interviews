#ifndef _BINARYTREE_H
#define _BINARYTREE_H

class BinaryTree {

protected:
  typedef struct Node {
    int value;
    Node *left;
    Node *right;

  public:
    Node(int _value, Node *_left, Node *_right)
        : value(_value), left(_left), right(_right) {}
  } Node;

  Node *root;

public:
  BinaryTree();
  ~BinaryTree();

  void add(int value);
  friend bool operator==(const BinaryTree &t1, const BinaryTree &t2);
};

#endif
