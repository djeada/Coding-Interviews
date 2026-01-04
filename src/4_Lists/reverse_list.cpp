/*
 * Task: Reverse a singly linked list in-place using pointer re-linking.
 *
 * REVERSE A LINKED LIST USING UNIQUE_PTR
 *
 * Define a class ListWithReversion that extends a basic singly linked list
 * (from list.h) by providing a function to reverse the list. The reversal is
 * done by re-linking the nodes, which are managed by std::unique_ptr, without
 * creating new nodes.
 *
 * The reversal algorithm works as follows:
 * - It iteratively detaches the head node from the original list.
 * - The detached node is then inserted at the front of a new list.
 * - Once all nodes are processed, the new list becomes the reversed list.
 *
 * ASCII Illustration:
 *
 *   Original List: 1 -> 2 -> 3 -> 4 -> 5
 *         |
 *       Reverse
 *         V
 *   Reversed List: 5 -> 4 -> 3 -> 2 -> 1
 *
 * Example:
 * Input:  List = [1, 2, 3, 4, 5]
 * Output: List = [5, 4, 3, 2, 1]
 *
 * Edge Cases:
 * - An empty list remains empty.
 * - A list with a single element remains unchanged.
 */

#include "list.h"
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

namespace {
struct TestRunner {
  int total = 0;
  int failed = 0;

  void expectEqual(const List &got, const List &expected,
                   const std::string &label) {
    ++total;
    if (got == expected) {
      std::cout << "[PASS] " << label << "\n";
      return;
    }
    ++failed;
    std::cout << "[FAIL] " << label << " expected=" << listToString(expected)
              << " got=" << listToString(got) << "\n";
  }

  void summary() const {
    std::cout << "Tests: " << total - failed << " passed, " << failed
              << " failed, " << total << " total\n";
  }

private:
  static std::string listToString(const List &list) {
    std::ostringstream oss;
    oss << "{";
    for (unsigned int i = 0; i < list.size(); ++i) {
      if (i > 0)
        oss << ", ";
      oss << list.get(i);
    }
    oss << "}";
    return oss.str();
  }
};
} // namespace

class ListWithReversion : public List {
public:
  ListWithReversion() : List() {}

  // Reverse the list by re-linking the unique_ptr nodes.
  void reverse() {
    std::unique_ptr<Node> new_head = nullptr;
    // Process nodes until the original list is empty.
    while (head) {
      // Detach the current head.
      auto temp = std::move(head->next);
      // Insert the detached node at the front of the new list.
      head->next = std::move(new_head);
      new_head = std::move(head);
      // Continue with the remainder of the list.
      head = std::move(temp);
    }
    // Update head to the new reversed list.
    head = std::move(new_head);
  }
};

// ------------------- Test Cases -------------------

void test1(TestRunner &runner) {
  ListWithReversion list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);

  List expected;
  expected.append(5);
  expected.append(4);
  expected.append(3);
  expected.append(2);
  expected.append(1);

  list.reverse();
  runner.expectEqual(list, expected, "reverse multi");
}

void test2(TestRunner &runner) {
  ListWithReversion list;
  list.append(1);

  List expected;
  expected.append(1);

  list.reverse();
  runner.expectEqual(list, expected, "reverse single");
}

void test3(TestRunner &runner) {
  ListWithReversion list;
  List expected;

  list.reverse();
  runner.expectEqual(list, expected, "reverse empty");
}

int main() {
  TestRunner runner;
  test1(runner);
  test2(runner);
  test3(runner);
  runner.summary();
  return 0;
}
