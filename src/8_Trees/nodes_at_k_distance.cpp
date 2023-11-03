#include "binary_tree.h"
#include <cassert>
#include <vector>

class TreeWithKDistanceNodes : public BinaryTree {
public:
  TreeWithKDistanceNodes() : BinaryTree() {}

  std::vector<int> findNodesAtDistance(unsigned int k) const {
    std::vector<int> result;
    findNodesAtDistanceFromNode(root.get(), k, result);
    return result;
  }

private:
  void findNodesAtDistanceFromNode(const Node *node, int distance,
                                   std::vector<int> &result) const {
    if (!node || distance < 0) {
      return;
    }

    if (distance == 0) {
      result.push_back(node->value);
      return;
    }

    findNodesAtDistanceFromNode(node->left.get(), distance - 1, result);
    findNodesAtDistanceFromNode(node->right.get(), distance - 1, result);
  }
};

void runTests() {
  {
    TreeWithKDistanceNodes tree;
    for (const auto &value : {9, 8, 13, 4, 10, 16, 7, 15}) {
      tree.add(value);
    }
    const auto result = tree.findNodesAtDistance(3);
    assert((result == std::vector<int>{7, 15}));
  }

  {
    TreeWithKDistanceNodes tree;
    for (const auto &value : {5, 4, 3, 2, 1}) {
      tree.add(value);
    }
    const auto result = tree.findNodesAtDistance(4);
    assert((result == std::vector<int>{1}));
  }

  {
    TreeWithKDistanceNodes tree;
    for (const auto &value : {1, 2, 3, 4, 5}) {
      tree.add(value);
    }
    const auto result = tree.findNodesAtDistance(4);
    assert((result == std::vector<int>{5}));
  }

  {
    TreeWithKDistanceNodes tree;
    tree.add(1);
    const auto result = tree.findNodesAtDistance(1);
    assert(result.empty());
  }
}

int main() {
  runTests();
  return 0;
}
