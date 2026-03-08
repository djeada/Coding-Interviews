/*
 * Task: Return inorder and preorder traversals of a binary tree as vectors.
 *
 * BINARY TREE TRAVERSALS TO VECTOR
 *
 * Problem:
 * Given the root of a binary tree, return its inorder traversal and preorder
 * traversal as arrays.
 *
 * Constraints:
 * - 0 <= number of nodes <= 10^5
 * - Node values are 32-bit signed integers.
 *
 * Example:
 * Input: root built from [9,8,13,4,10,16,7,15]
 * Output: inorder = [4,7,8,9,10,13,15,16], preorder = [9,8,4,7,13,10,16,15]
 */

#include "binary_tree.h"
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

class TreeWithVector : public BinaryTree {
public:
  // Default constructor calls the base default constructor
  TreeWithVector() : BinaryTree() {}

  // Delete copy semantics
  TreeWithVector(const TreeWithVector &) = delete;
  TreeWithVector &operator=(const TreeWithVector &) = delete;

  // Allow move semantics
  TreeWithVector(TreeWithVector &&) = default;
  TreeWithVector &operator=(TreeWithVector &&) = default;

  // Iterative inorder traversal: left -> root -> right
  std::vector<int> inorder() const {
    std::vector<int> result;
    std::stack<const Node *> s;
    const Node *curr = root.get();

    while (curr || !s.empty()) {
      while (curr) {
        s.push(curr);
        curr = curr->left.get();
      }
      curr = s.top();
      s.pop();
      result.push_back(curr->value);
      curr = curr->right.get();
    }
    return result;
  }

  // Iterative preorder traversal: root -> left -> right
  std::vector<int> preorder() const {
    std::vector<int> result;
    std::stack<const Node *> s;

    if (root)
      s.push(root.get());

    while (!s.empty()) {
      const auto temp = s.top();
      s.pop();
      result.push_back(temp->value);

      if (temp->right)
        s.push(temp->right.get());
      if (temp->left)
        s.push(temp->left.get());
    }
    return result;
  }
};

int main() {
  int total = 0;
  int failed = 0;

  auto toString = [](const std::vector<int> &values) {
    std::ostringstream oss;
    oss << "{";
    for (size_t i = 0; i < values.size(); ++i) {
      if (i > 0)
        oss << ", ";
      oss << values[i];
    }
    oss << "}";
    return oss.str();
  };

  auto expectEqual = [&](const std::vector<int> &got,
                         const std::vector<int> &expected,
                         const std::string &label) {
    ++total;
    if (got == expected) {
      std::cout << "[PASS] " << label << "\n";
      return;
    }
    ++failed;
    std::cout << "[FAIL] " << label << " expected=" << toString(expected)
              << " got=" << toString(got) << "\n";
  };

  auto summary = [&]() {
    std::cout << "Tests: " << total - failed << " passed, " << failed
              << " failed, " << total << " total\n";
  };

  auto testTreeWithVector = [&](const TreeWithVector &tree,
                                const std::vector<int> &inorderExpected,
                                const std::vector<int> &preorderExpected) {
    expectEqual(tree.inorder(), inorderExpected, "inorder traversal");
    expectEqual(tree.preorder(), preorderExpected, "preorder traversal");
  };

  testTreeWithVector([] {
                       TreeWithVector tree;
                       for (int val : {9, 8, 13, 4, 10, 16, 7, 15})
                         tree.add(val);
                       return tree; // Moved (since copy is deleted)
                     }(),
                     {4, 7, 8, 9, 10, 13, 15, 16},
                     {9, 8, 4, 7, 13, 10, 16, 15});

  testTreeWithVector([] {
                       TreeWithVector tree;
                       for (int val : {5, 4, 3, 2, 1})
                         tree.add(val);
                       return tree;
                     }(),
                     {1, 2, 3, 4, 5}, {5, 4, 3, 2, 1});

  testTreeWithVector([] {
                       TreeWithVector tree;
                       for (int val : {1, 2, 3, 4, 5})
                         tree.add(val);
                       return tree;
                     }(),
                     {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5});

  testTreeWithVector([] {
                       TreeWithVector tree;
                       tree.add(1);
                       return tree;
                     }(),
                     {1}, {1});
  summary();

  return 0;
}
