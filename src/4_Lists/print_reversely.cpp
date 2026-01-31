/*
 * Task: Print the elements of a linked list in reverse order.
 *
 * PRINT LINKED LIST IN REVERSE ORDER
 *
 * Demonstrate two approaches to print the elements of a linked list in reverse
 * order.
 *
 * 1. Iterative Approach:
 *    - Uses a stack to store list elements and then prints them in reverse
 * order by popping the stack.
 *    - Time Complexity: O(n), Space Complexity: O(n)
 *
 * 2. Recursive Approach:
 *    - Uses recursion to traverse the list to the end and then prints the
 * elements as the recursion unwinds.
 *    - Time Complexity: O(n), Space Complexity: O(n) due to the recursion
 * stack.
 *
 * ASCII Illustration:
 *
 *     List: 1 -> 2 -> 3
 *
 *     Reverse Output:
 *         3
 *         2
 *         1
 *
 * Example:
 * Input:  List = [1, 2, 3]
 * Output:
 *         (Iterative)
 *             3
 *             2
 *             1
 *
 *         (Recursive)
 *             3
 *             2
 *             1
 */

#include "list.h"
#include <functional>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

// Iterative approach: prints the list in reverse using a stack.
void printReverseIter(List &list) {
  std::stack<int> nodes;

  for (int value : list)
    nodes.push(value);

  while (!nodes.empty()) {
    std::cout << nodes.top() << std::endl;
    nodes.pop();
  }
}

std::vector<int> collectReverseIter(const List &list) {
  std::stack<int> nodes;
  for (int value : list)
    nodes.push(value);

  std::vector<int> result;
  while (!nodes.empty()) {
    result.push_back(nodes.top());
    nodes.pop();
  }
  return result;
}

// Recursive approach: prints the list in reverse by recursion.
void printReverseRecursive(List &list) {
  std::vector<int> values;
  for (int value : list)
    values.push_back(value);
  std::function<void(int)> printAt = [&](int index) {
    if (index < 0)
      return;
    std::cout << values[index] << std::endl;
    printAt(index - 1);
  };
  printAt(static_cast<int>(values.size()) - 1);
}

void collectReverseRecursive(const List &list, std::vector<int> &out) {
  std::vector<int> values;
  for (int value : list)
    values.push_back(value);
  std::function<void(int)> collectAt = [&](int index) {
    if (index < 0)
      return;
    out.push_back(values[index]);
    collectAt(index - 1);
  };
  collectAt(static_cast<int>(values.size()) - 1);
}

int main() {
  int total = 0;
  int failed = 0;

  auto toString = [](const std::vector<int> &values) {
    std::ostringstream oss;
    oss << "{";
    for (size_t i = 0; i < values.size(); ++i) {
      if (i > 0)
        oss << ", ";
      oss << values[i];
    }
    oss << "}";
    return oss.str();
  };

  auto expectEqual = [&](const std::vector<int> &got,
                         const std::vector<int> &expected,
                         const std::string &label) {
    ++total;
    if (got == expected) {
      std::cout << "[PASS] " << label << "\n";
      return;
    }
    ++failed;
    std::cout << "[FAIL] " << label << " expected=" << toString(expected)
              << " got=" << toString(got) << "\n";
  };

  auto summary = [&]() {
    std::cout << "Tests: " << total - failed << " passed, " << failed
              << " failed, " << total << " total\n";
  };

  List list;
  list.append(1);
  list.append(2);
  list.append(3);

  std::vector<int> expected{3, 2, 1};
  expectEqual(collectReverseIter(list), expected, "reverse print iterative");
  std::vector<int> recursiveOut;
  collectReverseRecursive(list, recursiveOut);
  expectEqual(recursiveOut, expected, "reverse print recursive");
  summary();

  return 0;
}
