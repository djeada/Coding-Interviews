#ifndef _BINARYTREE_H
#define _BINARYTREE_H

class BinaryTree {

protected:
  struct Node {
    int value;
    Node *left;
    Node *right;

  public:
    Node(int _value, Node *_left, Node *_right)
        : value(_value), left(_left), right(_right) {}
  };

  Node *root;

public:
  BinaryTree();
  ~BinaryTree();

  void add(int value);
};

#endif
