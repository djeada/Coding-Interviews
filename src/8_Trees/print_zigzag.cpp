/*
 * Task: Print a binary tree in zigzag (spiral) level order.
 *
 * ZIGZAG (SPIRAL) LEVEL ORDER TRAVERSAL
 *
 * Extend an assumed BinaryTree implementation (from "binary_tree.h") by
 * adding functionality to print the tree in a zigzag (spiral) level order.
 * This means that the nodes at each level are printed alternately from
 * left-to-right and right-to-left.
 *
 * Approach:
 *   - Use two stacks to alternate between levels.
 *   - For the current level, push the child nodes into the alternate stack in
 * an order that ensures the next level is printed in the opposite direction.
 *
 * ASCII Illustration:
 *           10
 *          /  \
 *         5    12
 *             /  \
 *           11    16
 *
 * Example Output:
 * For the tree built by inserting {10, 5, 12, 11, 16}, the printed output might
 * be: 10 12 5 11 16
 *
 * Explanation:
 * The first level is printed left-to-right (just the root), the second level is
 * printed right-to-left, and the process alternates for subsequent levels.
 */

#include "binary_tree.h"
#include <algorithm> // For std::swap
#include <iostream>
#include <stack>
#include <vector>

class TreeWithZigZagPrint : public BinaryTree {
public:
  TreeWithZigZagPrint() : BinaryTree() {}

  // Prints the tree in zigzag (spiral) level order.
  void print() const {
    if (!root) {
      std::cout << "Tree is empty." << std::endl;
      return;
    }

    // Use two stacks to store nodes of current level and next level.
    std::vector<std::stack<const Node *>> levels(2);
    int current = 0;
    int next = 1;

    levels[current].push(root.get());

    while (!levels[0].empty() || !levels[1].empty()) {
      const Node *currentNode = levels[current].top();
      levels[current].pop();

      std::cout << currentNode->value << ' ';

      if (current == 0) {
        // For left-to-right, push left child first then right child.
        if (currentNode->left)
          levels[next].push(currentNode->left.get());
        if (currentNode->right)
          levels[next].push(currentNode->right.get());
      } else {
        // For right-to-left, push right child first then left child.
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
