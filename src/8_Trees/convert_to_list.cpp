/*
 * BINARY TREE TRAVERSALS WITH VECTOR OUTPUT
 *
 * This program extends an assumed BinaryTree implementation (from "binary_tree.h") by adding
 * inorder and preorder traversal methods that return the result as a std::vector<int>.
 *
 * The inorder() method uses an iterative approach with a stack to traverse the tree in left-root-right order.
 * The preorder() method uses an iterative approach with a stack to traverse the tree in root-left-right order.
 *
 * ASCII Illustration:
 *             9
 *            / \
 *           8   13
 *          /   /  \
 *         4   10  16
 *          \
 *           7
 *                \
 *                15
 *
 * Example Input/Output:
 * When the tree is built by adding values in the order:
 *   {9, 8, 13, 4, 10, 16, 7, 15}
 * the inorder traversal returns: {4, 7, 8, 9, 10, 13, 15, 16}
 * and the preorder traversal returns: {9, 8, 4, 7, 13, 10, 16, 15}
 *
 * Explanation:
 * The tree is traversed using an iterative approach. Inorder traversal visits the left subtree, the root, then the right subtree.
 * Preorder traversal visits the root first, then the left subtree followed by the right subtree.
 */

#include "binary_tree.h"  // Assumed to exist and be implemented.
#include <cassert>
#include <stack>
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

// Simple test function using assertions
void testTreeWithVector(const TreeWithVector &tree,
                        const std::vector<int> &inorderExpected,
                        const std::vector<int> &preorderExpected) {
    assert(tree.inorder() == inorderExpected);
    assert(tree.preorder() == preorderExpected);
}

int main() {
    testTreeWithVector(
        [] {
            TreeWithVector tree;
            for (int val : {9, 8, 13, 4, 10, 16, 7, 15})
                tree.add(val);
            return tree;  // Moved (since copy is deleted)
        }(),
        {4, 7, 8, 9, 10, 13, 15, 16},
        {9, 8, 4, 7, 13, 10, 16, 15}
    );

    testTreeWithVector(
        [] {
            TreeWithVector tree;
            for (int val : {5, 4, 3, 2, 1})
                tree.add(val);
            return tree;
        }(),
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1}
    );

    testTreeWithVector(
        [] {
            TreeWithVector tree;
            for (int val : {1, 2, 3, 4, 5})
                tree.add(val);
            return tree;
        }(),
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5}
    );

    testTreeWithVector(
        [] {
            TreeWithVector tree;
            tree.add(1);
            return tree;
        }(),
        {1},
        {1}
    );

    return 0;
}
