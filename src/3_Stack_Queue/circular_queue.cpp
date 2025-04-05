/*
 * CIRCULAR QUEUE SIMULATION
 *
 * This task requires simulating a circular queue with fixed capacity. A sequence
 * of operations (given as strings) is provided, and the goal is to determine the
 * final state of the queue after processing all operations.
 *
 * Supported operations:
 *   "enQueue x" - Insert integer x at the rear of the queue. If the queue is full,
 *                 the operation is ignored.
 *   "deQueue"   - Remove the front element of the queue. If the queue is empty,
 *                 the operation is ignored.
 *
 * The final state of the queue should be returned as a vector of integers, from
 * the front element to the rear.
 *
 * ASCII Illustration:
 *
 *          enQueue(1)        enQueue(2)         enQueue(3)
 *         +----------+      +----------+       +----------+
 *         |          |      |          |       |          |
 *         |    1     | ---> |  1   2   | --->  | 1  2   3 |
 *         +----------+      +----------+       +----------+
 *                ^                                 ^
 *          Front of Queue                    Rear of Queue
 *
 * Example:
 *   Input:
 *      capacity = 3
 *      operations = {"enQueue 1", "enQueue 2", "enQueue 3", "deQueue", "enQueue 4"}
 *
 *   Output:
 *      {2, 3, 4}
 *
 *   Explanation:
 *     - "enQueue 1": Queue becomes {1}
 *     - "enQueue 2": Queue becomes {1, 2}
 *     - "enQueue 3": Queue becomes {1, 2, 3}
 *     - "deQueue":   Queue becomes {2, 3}
 *     - "enQueue 4": Queue becomes {2, 3, 4} (since capacity is 3)
 */

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Simple (Brute-force) Solution
// Uses a vector to simulate the queue; on deQueue, it shifts elements.
// Complexity: O(n) per deQueue operation due to element shifting.
std::vector<int> simpleSolution(int capacity, const std::vector<std::string>& operations) {
    std::vector<int> queue;
    for (const auto& op : operations) {
        std::istringstream iss(op);
        std::string command;
        iss >> command;
        if (command == "enQueue") {
            int x;
            iss >> x;
            if (queue.size() < static_cast<size_t>(capacity)) {
                queue.push_back(x);
            }
        } else if (command == "deQueue") {
            if (!queue.empty()) {
                queue.erase(queue.begin());
            }
        }
    }
    return queue;
}

// Optimal (Efficient) Solution
// Implements a circular queue using an array (vector) with head and tail indices.
// Complexity: O(1) for each operation.
std::vector<int> optimalSolution(int capacity, const std::vector<std::string>& operations) {
    std::vector<int> buffer(capacity);
    int head = 0;
    int tail = 0;
    int count = 0;

    for (const auto& op : operations) {
        std::istringstream iss(op);
        std::string command;
        iss >> command;
        if (command == "enQueue") {
            int x;
            iss >> x;
            if (count < capacity) {
                buffer[tail] = x;
                tail = (tail + 1) % capacity;
                count++;
            }
        } else if (command == "deQueue") {
            if (count > 0) {
                head = (head + 1) % capacity;
                count--;
            }
        }
    }

    std::vector<int> result;
    for (int i = 0; i < count; i++) {
        result.push_back(buffer[(head + i) % capacity]);
    }
    return result;
}

// Alternative (Educational) Solution
// Uses std::deque from the STL to simulate the circular queue.
// Complexity: O(1) for push/pop operations.
std::vector<int> alternativeSolution(int capacity, const std::vector<std::string>& operations) {
    std::deque<int> dq;
    for (const auto& op : operations) {
        std::istringstream iss(op);
        std::string command;
        iss >> command;
        if (command == "enQueue") {
            int x;
            iss >> x;
            if (dq.size() < static_cast<size_t>(capacity)) {
                dq.push_back(x);
            }
        } else if (command == "deQueue") {
            if (!dq.empty()) {
                dq.pop_front();
            }
        }
    }
    return std::vector<int>(dq.begin(), dq.end());
}

// Test cases for correctness
void test() {
    int capacity = 3;
    std::vector<std::string> operations = {
        "enQueue 1", "enQueue 2", "enQueue 3", "deQueue", "enQueue 4"
    };
    std::vector<int> expected = {2, 3, 4};

    auto result1 = simpleSolution(capacity, operations);
    auto result2 = optimalSolution(capacity, operations);
    auto result3 = alternativeSolution(capacity, operations);

    assert(result1 == expected);
    assert(result2 == expected);
    assert(result3 == expected);

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
