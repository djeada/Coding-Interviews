/*
 * DETECT LOOP IN A LINKED LIST (WITH LOOPS)
 *
 * This program defines a linked list class (ListWithLoops) that supports creating loops
 * in the list by connecting nodes arbitrarily. Memory management is handled by storing all
 * allocated nodes in a vector so that they can be safely deleted even if a loop exists.
 *
 * The class provides:
 *  - append: Add a new node with a given value.
 *  - connectNodes: Connect one node to another (forming a loop if desired).
 *  - hasLoop: Detects a loop in the list using Floyd's cycle-finding algorithm.
 *
 * ASCII Illustration:
 *
 *      Without Loop:
 *        1 -> nullptr
 *
 *      With Loop:
 *        1 -> 2 -> 3 -> 4 -> 5
 *                 ^         |
 *                 |_________|
 *
 * Example:
 * Input:  List = [1, 2, 3, 4, 5] with connection from node 5 to node 3.
 * Output: hasLoop() returns true.
 *
 * Edge Cases:
 *  - A single node with no loop.
 *  - A node connected to itself.
 */

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cassert>
#include <algorithm>

// A simple node that holds an int and a pointer to the next node.
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// A list class that supports loops.
// Memory management is done by storing all allocated nodes in a vector.
class ListWithLoops {
public:
    ListWithLoops() : head(nullptr) {}

    ~ListWithLoops() {
        // Delete each node exactly once regardless of loop structure.
        for (Node* node : nodes) {
            delete node;
        }
    }

    // Append a new node with the given value.
    void append(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            // Traverse until the end of the list.
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        nodes.push_back(newNode);
    }

    // Connect the node at index 'from' to the node at index 'to'.
    // Indices are 0-based.
    // Throws std::out_of_range if indices are invalid.
    void connectNodes(int from, int to) {
        if (from < 0 || from >= size() || to < 0 || to >= size()) {
            throw std::out_of_range("Index out of range!");
        }
        Node* fromNode = getNode(from);
        Node* toNode   = getNode(to);
        if (!fromNode || !toNode) {
            throw std::runtime_error("Unexpected null node encountered.");
        }
        fromNode->next = toNode;
    }

    // Detects a loop using Floyd's cycle-finding algorithm.
    bool hasLoop() {
        Node* slow = head;
        Node* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
                return true;
        }
        return false;
    }

    // Return the number of nodes in the list.
    int size() const { 
      return static_cast<int>(nodes.size()); 
    }

private:
    Node* head;
    // Store pointers to all nodes allocated. This list owns the nodes.
    std::vector<Node*> nodes;

    // Helper method to retrieve the node at a given index.
    Node* getNode(int index) {
        if (index < 0 || index >= size()) {
            return nullptr;
        }
        return nodes[index];
    }
};

// ------------------- Test Cases -------------------

void test1() {
  ListWithLoops list;
  list.append(1);
  // Single node should not have a loop.
  assert(!list.hasLoop());
}

void test2() {
  ListWithLoops list;
  list.append(1);
  // Connect the only node to itself to form a loop.
  list.connectNodes(0, 0);
  assert(list.hasLoop());
}

void test3() {
  ListWithLoops list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);
  // Connect the last node (index 4) to the node at index 2.
  list.connectNodes(4, 2);
  assert(list.hasLoop());
}

void test4() {
  ListWithLoops list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);
  // Connect the last node (index 4) to the first node (index 0).
  list.connectNodes(4, 0);
  assert(list.hasLoop());
}

int main() {
  test1();
  test2();
  test3();
  test4();
  std::cout << "All tests passed!\n";
  return 0;
}
