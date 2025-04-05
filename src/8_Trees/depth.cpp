/*
 * BINARY TREE DEPTH CALCULATION
 *
 * This program extends an assumed BinaryTree implementation (from "binary_tree.h") by adding
 * a method to calculate the depth (height) of the tree. The depth is defined as the number of nodes
 * along the longest path from the root node down to the farthest leaf node.
 *
 * The algorithm is implemented recursively:
 *   - For an empty node, the depth is 0.
 *   - For a non-empty node, the depth is the maximum depth of its left and right subtrees plus one.
 *
 * ASCII Illustration:
 *           9
 *          / \
 *         8   13
 *        /    / \
 *       4    10  16
 *        \
 *         7
 *            \
 *            15
 *
 * Example Input/Output:
 * Input: Build the tree by adding values: {9, 8, 13, 4, 10, 16, 7, 15}
 * Output: The depth of the tree is 4.
 *
 * Explanation:
 * The longest path in the tree is from the root (9) to the leaf (15) with a total of 4 nodes.
 */

#include "binary_tree.h"  // Assumed to exist and be implemented.
#include <algorithm>
#include <cassert>

// TreeWithDepth extends BinaryTree with a method to compute the tree's depth.
class TreeWithDepth : public BinaryTree {
public:
    TreeWithDepth() : BinaryTree() {}

    // Public method to get the depth of the tree.
    unsigned int depth() const { return _depth(root.get()); }

private:
    // Private recursive helper function that computes the depth.
    unsigned int _depth(const Node *node) const {
        if (!node)
            return 0;
        unsigned int left = _depth(node->left.get());
        unsigned int right = _depth(node->right.get());
        return std::max(left, right) + 1;
    }
};

// Test function to verify that the computed depth matches the expected depth.
void testTreeWithDepth(const TreeWithDepth &tree, unsigned int expectedDepth) {
    assert(tree.depth() == expectedDepth);
}

int main() {
    testTreeWithDepth(
        [] {
            TreeWithDepth tree;
            for (int val : {9, 8, 13, 4, 10, 16, 7, 15})
                tree.add(val);
            return tree;
        }(),
        4
    );

    testTreeWithDepth(
        [] {
            TreeWithDepth tree;
            for (int val : {5, 4, 3, 2, 1})
                tree.add(val);
            return tree;
        }(),
        5
    );

    testTreeWithDepth(
        [] {
            TreeWithDepth tree;
            for (int val : {1, 2, 3, 4, 5})
                tree.add(val);
            return tree;
        }(),
        5
    );

    testTreeWithDepth(
        [] {
            TreeWithDepth tree;
            tree.add(1);
            return tree;
        }(),
        1
    );

    return 0;
}
