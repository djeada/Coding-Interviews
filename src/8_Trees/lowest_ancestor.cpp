/*
 * Task: Find the lowest common ancestor of two nodes in a BST.
 *
 * LOWEST COMMON ANCESTOR OF A BST
 *
 * Problem:
 * Given the root of a binary search tree and two node values p and q, return
 * the value of their lowest common ancestor.
 *
 * Constraints:
 * - 2 <= number of nodes <= 10^5
 * - All node values are unique.
 * - p and q both exist in the BST.
 *
 * Example:
 * Input: root = [20,8,22,4,12,10,14], p = 10, q = 14
 * Output: 12
 */

#include "binary_tree.h"
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>

class TreeWithLowestCommonAncestor : public BinaryTree {
public:
  TreeWithLowestCommonAncestor() : BinaryTree() {}

  // Finds the lowest common ancestor (LCA) of two nodes with the given values.
  int findLowestCommonAncestor(int value1, int value2) const {
    if (!root || !contains(value1) || !contains(value2)) {
      throw std::invalid_argument("Values are not present in the tree.");
    }
    return findLCA(root.get(), value1, value2);
  }

private:
  // Recursive helper function that finds the LCA by leveraging BST properties.
  int findLCA(const Node *node, int value1, int value2) const {
    if (node->left && node->value > value1 && node->value > value2) {
      return findLCA(node->left.get(), value1, value2);
    }
    if (node->right && node->value < value1 && node->value < value2) {
      return findLCA(node->right.get(), value1, value2);
    }
    return node->value;
  }
};

int main() {
  int total = 0;
  int failed = 0;

  auto expectEqual = [&](int got, int expected, const std::string &label) {
    ++total;
    if (got == expected) {
      std::cout << "[PASS] " << label << "\n";
      return;
    }
    ++failed;
    std::cout << "[FAIL] " << label << " expected=" << expected
              << " got=" << got << "\n";
  };

  auto expectThrows = [&](const std::function<void()> &fn,
                          const std::string &label) {
    ++total;
    try {
      fn();
      ++failed;
      std::cout << "[FAIL] " << label << " expected=throw got=no throw\n";
    } catch (const std::exception &ex) {
      std::cout << "[PASS] " << label << " threw=\"" << ex.what() << "\"\n";
    } catch (...) {
      std::cout << "[PASS] " << label << " threw=non-std exception\n";
    }
  };

  auto summary = [&]() {
    std::cout << "Tests: " << total - failed << " passed, " << failed
              << " failed, " << total << " total\n";
  };

  {
    TreeWithLowestCommonAncestor tree;
    for (const auto &value : {20, 8, 22, 4, 12, 10, 14}) {
      tree.add(value);
    }
    expectEqual(tree.findLowestCommonAncestor(10, 14), 12, "LCA 10,14");
  }

  {
    TreeWithLowestCommonAncestor tree;
    for (const auto &value : {20, 8, 22, 4, 12, 10, 14}) {
      tree.add(value);
    }
    expectEqual(tree.findLowestCommonAncestor(8, 14), 8, "LCA 8,14");
  }

  {
    TreeWithLowestCommonAncestor tree;
    for (const auto &value : {20, 8, 22, 4, 12, 10, 14}) {
      tree.add(value);
    }
    expectEqual(tree.findLowestCommonAncestor(10, 22), 20, "LCA 10,22");
  }

  {
    TreeWithLowestCommonAncestor tree;
    for (const auto &value : {5, 4, 3, 2, 1}) {
      tree.add(value);
    }
    // For this degenerate tree (all nodes to the left), the LCA of 1 and 3
    // is 3.
    expectEqual(tree.findLowestCommonAncestor(1, 3), 3, "LCA 1,3");
  }
  {
    TreeWithLowestCommonAncestor tree;
    for (const auto &value : {20, 8, 22}) {
      tree.add(value);
    }
    expectThrows([&]() { tree.findLowestCommonAncestor(8, 99); },
                 "LCA missing value");
  }
  summary();
  return 0;
}
