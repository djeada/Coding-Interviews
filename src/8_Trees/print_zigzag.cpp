#include "binary_tree.h"
#include <iostream>
#include <stack>

class TreeWithPrint : public BinaryTree {

public:
  TreeWithPrint() : BinaryTree() {}
  void print() {

    if (!root)
      return;

    std::stack<Node *> levels[2];
    int current = 0;
    int next = 1;

    levels[current].push(root);
    while (!levels[0].empty() || !levels[1].empty()) {
      auto node = levels[current].top();
      levels[current].pop();

      std::cout << node->value << " ";

      if (current == 0) {
        if (node->left)
          levels[next].push(node->left);
        if (node->right)
          levels[next].push(node->right);
      } else {
        if (node->right)
          levels[next].push(node->right);
        if (node->left)
          levels[next].push(node->left);
      }

      if (levels[current].empty()) {
        std::cout << std::endl;
        current = 1 - current;
        next = 1 - next;
      }
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
