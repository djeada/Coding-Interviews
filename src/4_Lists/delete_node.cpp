/*
 * Task: Remove the first occurrence of a value from a singly linked list.
 *
 * REMOVE ELEMENT FROM A LINKED LIST
 *
 * Extend a basic singly linked list (as defined in list.h) by providing a
 * function to remove the first occurrence of a given value from the list.
 *
 * The remove operation works as follows:
 * - It traverses the list looking for the node containing the target value.
 * - If found, it adjusts the pointers to exclude the node from the list.
 * - Special handling is provided for removing the head node.
 *
 * ASCII Illustration:
 *
 *     Before removal: 1 -> 2 -> 3 -> 4 -> 5
 *                     remove(3)
 *     After removal:  1 -> 2 -> 4 -> 5
 *
 * Example:
 * Input:  List = [1, 2, 3, 4, 5], remove(3)
 * Output: List = [1, 2, 4, 5]
 *
 * Edge Cases:
 * - Removing the head element.
 * - Removing the tail element.
 * - Removing from a list with a single element.
 */

#include "list.h"
#include <iostream>
#include <sstream>
#include <string>

class ListWithDeletion : public List {
public:
  // Remove the first occurrence of the node containing the specified value.
  void remove(int value) {
    Node *prev = nullptr;
    auto current = head.get();

    // Traverse the list until the target value is found.
    while (current && current->data != value) {
      prev = current;
      current = current->next.get();
    }

    // If the node with the target value is found, remove it.
    if (current && current->data == value) {
      if (prev) {
        // Node is not the head: update previous node's next pointer.
        prev->next = std::move(current->next);
      } else {
        // Node is the head: update the head pointer.
        head = std::move(current->next);
      }
      --count;
    }
  }
};

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

// ------------------- Test Cases -------------------

void test1(TestRunner &runner) {
  ListWithDeletion list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);

  list.remove(3);

  List expectedResult;
  expectedResult.append(1);
  expectedResult.append(2);
  expectedResult.append(4);
  expectedResult.append(5);

  runner.expectEqual(list, expectedResult, "remove middle node");
}

void test2(TestRunner &runner) {
  ListWithDeletion list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);

  list.remove(5);

  List expectedResult;
  expectedResult.append(1);
  expectedResult.append(2);
  expectedResult.append(3);
  expectedResult.append(4);

  runner.expectEqual(list, expectedResult, "remove tail node");
}

void test3(TestRunner &runner) {
  ListWithDeletion list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);

  list.remove(1);

  List expectedResult;
  expectedResult.append(2);
  expectedResult.append(3);
  expectedResult.append(4);
  expectedResult.append(5);

  runner.expectEqual(list, expectedResult, "remove head node");
}

void test4(TestRunner &runner) {
  ListWithDeletion list;
  list.append(1);

  list.remove(1);

  List expectedResult;

  runner.expectEqual(list, expectedResult, "remove sole node");
}

int main() {
  TestRunner runner;
  test1(runner);
  test2(runner);
  test3(runner);
  test4(runner);
  runner.summary();

  return 0;
}
