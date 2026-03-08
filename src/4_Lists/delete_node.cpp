/*
 * Task: Remove the first occurrence of a value from a singly linked list.
 *
 * REMOVE LINKED LIST ELEMENT
 *
 * Problem:
 * Given the head of a singly linked list and an integer target, remove the
 * first node whose value equals target. If target does not exist, keep the
 * list unchanged.
 *
 * Constraints:
 * - 0 <= n <= 10^5
 * - Node values and target are 32-bit signed integers.
 *
 * Example 1:
 * Input: head = [1,2,3,4,5], target = 3
 * Output: [1,2,4,5]
 *
 * Example 2:
 * Input: head = [1], target = 1
 * Output: []
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
