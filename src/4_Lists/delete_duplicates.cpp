/*
 * Task: Delete duplicate values from a singly linked list.
 *
 * DELETE DUPLICATE NODES IN A LINKED LIST
 *
 * Define a class named UniqueList that extends a basic singly linked list
 * (from list.h) and provides an operation to delete duplicate nodes from the
 * list. The deletion process is implemented by traversing the list and using
 * an unordered_set to keep track of seen values. When a duplicate node is
 * encountered, it is removed from the list.
 *
 * ASCII Illustration:
 *
 *      Before: 1 -> 2 -> 3 -> 4 -> 4 -> 5
 *                      |         |
 *                      +---------+
 *
 *      After:  1 -> 2 -> 3 -> 4 -> 5
 *
 * Example Input/Output:
 * Input List: 1, 2, 3, 4, 4, 5
 * Output List: 1, 2, 3, 4, 5
 *
 * Explanation:
 * The duplicate node containing 4 is removed so that each value appears only
 * once.
 */

#include "list.h"
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_set>

// UniqueList is derived from List and provides deletion of duplicate nodes.
class UniqueList : public List {
public:
  UniqueList() : List() {}

  // Delete duplicate nodes in the list.
  void deleteDuplication() {
    if (empty())
      return;

    std::unordered_set<int> visited;
    Node *current = head.get();
    Node *previous = nullptr;

    while (current) {
      if (visited.find(current->data) != visited.end()) {
        // Duplicate found: remove the node.
        if (!previous) {
          // If current is at head (shouldn't happen after first unique value),
          // update head.
          head = std::move(current->next);
          current = head.get();
          --count;
        } else {
          previous->next = std::move(current->next);
          current = previous->next.get();
          --count;
        }
      } else {
        // First occurrence: mark as visited and move forward.
        visited.insert(current->data);
        previous = current;
        current = current->next.get();
      }
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
    UniqueList duplicateList;
    duplicateList.append(1);
    duplicateList.append(2);
    duplicateList.append(3);
    duplicateList.append(4);
    duplicateList.append(4);
    duplicateList.append(5);

    UniqueList uniqueList;
    uniqueList.append(1);
    uniqueList.append(2);
    uniqueList.append(3);
    uniqueList.append(4);
    uniqueList.append(5);

    duplicateList.deleteDuplication();
    expectEqual(duplicateList, uniqueList, "delete duplicates #1");
  }

  {
    UniqueList duplicateList;
    duplicateList.append(1);
    duplicateList.append(2);
    duplicateList.append(3);
    duplicateList.append(4);
    duplicateList.append(5);

    UniqueList uniqueList;
    uniqueList.append(1);
    uniqueList.append(2);
    uniqueList.append(3);
    uniqueList.append(4);
    uniqueList.append(5);

    duplicateList.deleteDuplication();
    expectEqual(duplicateList, uniqueList, "delete duplicates #2");
  }

  {
    UniqueList duplicateList;
    duplicateList.append(1);
    duplicateList.append(1);
    duplicateList.append(1);
    duplicateList.append(1);
    duplicateList.append(2);

    UniqueList uniqueList;
    uniqueList.append(1);
    uniqueList.append(2);

    duplicateList.deleteDuplication();
    expectEqual(duplicateList, uniqueList, "delete duplicates #3");
  }

  {
    UniqueList duplicateList;
    duplicateList.append(1);
    duplicateList.append(1);
    duplicateList.append(1);
    duplicateList.append(1);
    duplicateList.append(1);

    UniqueList uniqueList;
    uniqueList.append(1);

    duplicateList.deleteDuplication();
    expectEqual(duplicateList, uniqueList, "delete duplicates #4");
  }

  summary();
  return 0;
}
