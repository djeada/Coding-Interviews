/*
 * FIND NODES AT K DISTANCE FROM ROOT IN A BINARY TREE
 *
 * This program extends an assumed BinaryTree implementation (from "binary_tree.h") by adding
 * functionality to find all nodes that are exactly K edges away from the root.
 *
 * The algorithm uses a recursive helper function that traverses the tree, decrementing the 
 * distance until it reaches zero. When the distance is zero, the node's value is added to the result.
 *
 * ASCII Illustration:
 *             9
 *            / \
 *           8   13
 *          /   /  \
 *         4   10  16
 *          \
 *           7        <- Node at distance 3
 *                \
 *                15     <- Node at distance 3
 *
 * Example Input/Output:
 * Input: Tree built by inserting values {9, 8, 13, 4, 10, 16, 7, 15} and k = 3.
 * Output: Nodes at distance 3 are [7, 15].
 *
 * Explanation:
 * Starting from the root (distance 0), the algorithm recursively explores the tree, reducing the
 * distance by one at each level. When the distance becomes zero, the current node is part of the result.
 */

#include "binary_tree.h"
#include <cassert>
#include <vector>

class TreeWithKDistanceNodes : public BinaryTree {
public:
    TreeWithKDistanceNodes() : BinaryTree() {}

    // Returns a vector containing the values of all nodes at distance k from the root.
    std::vector<int> findNodesAtDistance(unsigned int k) const {
        std::vector<int> result;
        findNodesAtDistanceFromNode(root.get(), k, result);
        return result;
    }

private:
    // Recursive helper function to collect nodes at a given distance from the current node.
    void findNodesAtDistanceFromNode(const Node *node, int distance, std::vector<int> &result) const {
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
        for (const auto &value : {9, 8, 13, 4, 10, 16, 7, 15})
            tree.add(value);
        const auto result = tree.findNodesAtDistance(3);
        assert((result == std::vector<int>{7, 15}));
    }

    {
        TreeWithKDistanceNodes tree;
        for (const auto &value : {5, 4, 3, 2, 1})
            tree.add(value);
        const auto result = tree.findNodesAtDistance(4);
        assert((result == std::vector<int>{1}));
    }

    {
        TreeWithKDistanceNodes tree;
        for (const auto &value : {1, 2, 3, 4, 5})
            tree.add(value);
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
