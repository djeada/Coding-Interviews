/*
 * BREADTH-FIRST PRINT (LEVEL ORDER TRAVERSAL)
 *
 * This program extends an assumed BinaryTree implementation (from
 * "binary_tree.h") by adding functionality to print the tree in a breadth-first
 * (level order) manner.
 *
 * The algorithm uses a queue to traverse the tree level by level:
 *   - Start from the root node and push it into the queue.
 *   - While the queue is not empty, remove the front node, print its value, and
 * enqueue its children.
 *
 * ASCII Illustration:
 *           10
 *          /  \
 *         5    12
 *             /  \
 *           11    16
 *
 * Example Output:
 * For the tree built by inserting {10, 5, 12, 11, 16}, the printed output will
 * be: 10 5 12 11 16
 *
 * Explanation:
 * The nodes are printed level by level from left to right.
 */

#include "binary_tree.h"
#include <iostream>
#include <queue>

class TreeWithBreadthFirstPrint : public BinaryTree {
public:
  TreeWithBreadthFirstPrint() : BinaryTree() {}

  // Prints the tree in a breadth-first order.
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
