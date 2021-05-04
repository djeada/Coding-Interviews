#include "binary_tree.h"
#include <iostream>
#include <queue>

class TreeWithPrint : public BinaryTree {

public:
  TreeWithPrint() : BinaryTree() {}
  void print() {
    if (!root)
      return;

    std::queue<Node *> queue;
    queue.push(root);

    while (!queue.empty()) {
      auto node = queue.front();
      queue.pop();

      std::cout << node->value << std::endl;

      if (node->left)
        queue.push(node->left);

      if (node->right)
        queue.push(node->right);
    }
  }
};

int main() {
  TreeWithPrint tree;
  tree.add(10);
  tree.add(5);
  tree.add(12);
  tree.add(11);
  tree.add(16);

  tree.print();

  return 0;
}
