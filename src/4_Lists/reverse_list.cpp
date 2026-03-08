/*
 * Task: Reverse a singly linked list in-place using pointer re-linking.
 *
 * REVERSE LINKED LIST
 *
 * Problem:
 * Given the head of a singly linked list, reverse the list in-place and return
 * the reversed list.
 *
 * Constraints:
 * - 0 <= n <= 10^5
 * - Node values are 32-bit signed integers.
 *
 * Example 1:
 * Input: head = [1,2,3,4,5]
 * Output: [5,4,3,2,1]
 *
 * Example 2:
 * Input: head = []
 * Output: []
 */

#include "list.h"
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

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
    expectEqual(list, expected, "reverse multi");
  }

  {
    ListWithReversion list;
    list.append(1);

    List expected;
    expected.append(1);

    list.reverse();
    expectEqual(list, expected, "reverse single");
  }

  {
    ListWithReversion list;
    List expected;

    list.reverse();
    expectEqual(list, expected, "reverse empty");
  }

  summary();
  return 0;
}
