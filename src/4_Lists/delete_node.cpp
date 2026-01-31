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

int main() {
  int total = 0;
  int failed = 0;

  auto listToString = [](const List &list) {
    std::ostringstream oss;
    oss << "{";
    bool first = true;
    for (int value : list) {
      if (!first)
        oss << ", ";
      oss << value;
      first = false;
    }
    oss << "}";
    return oss.str();
  };

  auto expectEqual = [&](const List &got, const List &expected,
                         const std::string &label) {
    ++total;
    if (got == expected) {
      std::cout << "[PASS] " << label << "\n";
      return;
    }
    ++failed;
    std::cout << "[FAIL] " << label << " expected=" << listToString(expected)
              << " got=" << listToString(got) << "\n";
  };

  auto summary = [&]() {
    std::cout << "Tests: " << total - failed << " passed, " << failed
              << " failed, " << total << " total\n";
  };

  {
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

    expectEqual(list, expectedResult, "remove middle node");
  }

  {
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

    expectEqual(list, expectedResult, "remove tail node");
  }

  {
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

    expectEqual(list, expectedResult, "remove head node");
  }

  {
    ListWithDeletion list;
    list.append(1);

    list.remove(1);

    List expectedResult;

    expectEqual(list, expectedResult, "remove sole node");
  }

  summary();

  return 0;
}
