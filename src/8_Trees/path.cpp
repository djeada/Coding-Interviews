/*
 * Task: Find a root-to-leaf path with a given sum in a binary tree.
 *
 * FIND PATH WITH GIVEN SUM IN A BINARY TREE
 *
 * Extend an assumed BinaryTree implementation (from "binary_tree.h") by
 * adding functionality to find a path from the root to a leaf whose node
 * values sum up to a given target.
 *
 * The algorithm uses a recursive helper function that traverses the tree while
 * maintaining the current sum and the path taken. If a leaf is reached and the
 * current sum equals the target sum, the path is returned. Otherwise, the
 * algorithm backtracks.
 *
 * ASCII Illustration:
 *         10
 *        /  \
 *       5   12
 *      / \
 *     4   7
 *
 * Example Input/Output:
 * Input: Tree built by inserting values {10, 5, 12, 4, 7} and targetSum = 22.
 * Output: Path [10, 5, 7] since 10 + 5 + 7 = 22.
 *
 * Explanation:
 * The algorithm explores each root-to-leaf path. When it reaches the leaf node,
 * it checks if the sum of the values along the path matches the target sum. If
 * so, it returns that path; if not, it backtracks.
 */

#include "binary_tree.h"
#include <cassert>
#include <vector>

class TreeWithSumPath : public BinaryTree {
public:
  TreeWithSumPath() : BinaryTree() {}

  // Returns a vector representing a path from root to leaf whose sum equals
  // targetSum. If no such path exists, returns an empty vector.
  std::vector<int> findPathWithSum(int targetSum) const {
    std::vector<int> path;
    findPath(root.get(), targetSum, 0, path);
    return path;
  }

private:
  // Recursive helper function to find a valid path.
  // It adds the current node's value to the current sum and path.
  // If a leaf is reached and current sum equals targetSum, returns true.
  // Otherwise, backtracks by removing the current node's value from the path.
  bool findPath(const Node *node, int targetSum, int currentSum,
                std::vector<int> &path) const {
    if (!node) {
      return false;
    }

    currentSum += node->value;
    path.push_back(node->value);

    // Check if we reached a leaf node and the current sum equals targetSum.
    if (!node->left && !node->right && currentSum == targetSum) {
      return true;
    }

    // Continue searching in the left or right subtree.
    if (findPath(node->left.get(), targetSum, currentSum, path) ||
        findPath(node->right.get(), targetSum, currentSum, path)) {
      return true;
    }

    // Backtrack if no valid path is found in either subtree.
    path.pop_back();
    return false;
  }
};

// Test function to verify that the found path meets the expected result.
void runTests() {
  {
    TreeWithSumPath tree;
    for (const auto &value : {10, 5, 12, 4, 7})
      tree.add(value);
    const auto result = tree.findPathWithSum(22);
    assert((result == std::vector<int>{10, 5, 7}));
  }

  {
    TreeWithSumPath tree;
    for (const auto &value : {10, 5, 12, 4, 7})
      tree.add(value);
    const auto result = tree.findPathWithSum(15);
    assert(result.empty());
  }

  {
    TreeWithSumPath tree;
    for (const auto &value : {5, 4, 3, 2, 1})
      tree.add(value);
    const auto result = tree.findPathWithSum(15);
    assert((result == std::vector<int>{5, 4, 3, 2, 1}));
  }

  {
    TreeWithSumPath tree;
    for (const auto &value : {1, 2, 3, 4, 5})
      tree.add(value);
    const auto result = tree.findPathWithSum(16);
    assert(result.empty());
  }
}

int main() {
  runTests();
  return 0;
}
