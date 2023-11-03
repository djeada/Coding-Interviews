#include "binary_tree.h"
#include <iostream>
#include <stack>
#include <vector>

class TreeWithZigZagPrint : public BinaryTree {
public:
  TreeWithZigZagPrint() : BinaryTree() {}

  void print() const {
    if (!root) {
      std::cout << "Tree is empty." << std::endl;
      return;
    }

    std::vector<std::stack<const Node *>> levels(2);
    int current = 0;
    int next = 1;

    levels[current].push(root.get());

    while (!levels[0].empty() || !levels[1].empty()) {
      const auto *currentNode = levels[current].top();
      levels[current].pop();

      std::cout << currentNode->value << ' ';

      if (current == 0) {
        if (currentNode->left)
          levels[next].push(currentNode->left.get());
        if (currentNode->right)
          levels[next].push(currentNode->right.get());
      } else {
        if (currentNode->right)
          levels[next].push(currentNode->right.get());
        if (currentNode->left)
          levels[next].push(currentNode->left.get());
      }

      if (levels[current].empty()) {
        std::cout << std::endl;
        std::swap(current, next);
      }
    }
  }
};

int main() {
  TreeWithZigZagPrint tree;
  for (const auto &value : {10, 5, 12, 11, 16}) {
    tree.add(value);
  }

  tree.print();

  return 0;
}
