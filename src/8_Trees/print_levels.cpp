#include "binary_tree.h"
#include <iostream>
#include <queue>

class TreeWithBreadthFirstPrint : public BinaryTree {
public:
  TreeWithBreadthFirstPrint() : BinaryTree() {}

  void print() const {
    if (!root) {
      std::cout << "Tree is empty." << std::endl;
      return;
    }

    std::queue<const Node *> nodesToPrint;
    nodesToPrint.push(root.get());

    while (!nodesToPrint.empty()) {
      const auto *currentNode = nodesToPrint.front();
      nodesToPrint.pop();

      std::cout << currentNode->value << ' ';

      if (currentNode->left) {
        nodesToPrint.push(currentNode->left.get());
      }
      if (currentNode->right) {
        nodesToPrint.push(currentNode->right.get());
      }
    }
    std::cout << std::endl;
  }
};

int main() {
  TreeWithBreadthFirstPrint tree;
  for (const auto &value : {10, 5, 12, 11, 16}) {
    tree.add(value);
  }

  tree.print();

  return 0;
}
