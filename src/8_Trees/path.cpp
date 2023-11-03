#include "binary_tree.h"
#include <cassert>
#include <vector>

class TreeWithSumPath : public BinaryTree {
public:
  TreeWithSumPath() : BinaryTree() {}

  std::vector<int> findPathWithSum(int targetSum) const {
    std::vector<int> path;
    findPath(root.get(), targetSum, 0, path);
    return path;
  }

private:
  bool findPath(const Node *node, int targetSum, int currentSum,
                std::vector<int> &path) const {
    if (!node) {
      return false;
    }

    currentSum += node->value;
    path.push_back(node->value);

    if (!node->left && !node->right && currentSum == targetSum) {
      return true;
    }

    if (findPath(node->left.get(), targetSum, currentSum, path) ||
        findPath(node->right.get(), targetSum, currentSum, path)) {
      return true;
    }

    path.pop_back();
    return false;
  }
};

void runTests() {
  {
    TreeWithSumPath tree;
    for (const auto &value : {10, 5, 12, 4, 7}) {
      tree.add(value);
    }
    const auto result = tree.findPathWithSum(22);
    assert((result == std::vector<int>{10, 5, 7}));
  }

  {
    TreeWithSumPath tree;
    for (const auto &value : {10, 5, 12, 4, 7}) {
      tree.add(value);
    }
    const auto result = tree.findPathWithSum(15);
    assert(result.empty());
  }

  {
    TreeWithSumPath tree;
    for (const auto &value : {5, 4, 3, 2, 1}) {
      tree.add(value);
    }
    const auto result = tree.findPathWithSum(15);
    assert((result == std::vector<int>{5, 4, 3, 2, 1}));
  }

  {
    TreeWithSumPath tree;
    for (const auto &value : {1, 2, 3, 4, 5}) {
      tree.add(value);
    }
    const auto result = tree.findPathWithSum(16);
    assert(result.empty());
  }
}

int main() {
  runTests();
  return 0;
}
