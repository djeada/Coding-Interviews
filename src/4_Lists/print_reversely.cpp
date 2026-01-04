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
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

namespace {
struct TestRunner {
  int total = 0;
  int failed = 0;

  void expectEqual(const std::vector<int> &got,
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
  }

  void summary() const {
    std::cout << "Tests: " << total - failed << " passed, " << failed
              << " failed, " << total << " total\n";
  }

private:
  static std::string toString(const std::vector<int> &values) {
    std::ostringstream oss;
    oss << "{";
    for (size_t i = 0; i < values.size(); ++i) {
      if (i > 0)
        oss << ", ";
      oss << values[i];
    }
    oss << "}";
    return oss.str();
  }
};
} // namespace

// Iterative approach: prints the list in reverse using a stack.
void printReverseIter(List &list) {
  std::stack<int> nodes;

  for (unsigned int i = 0; i < list.size(); i++)
    nodes.push(list.get(i));

  while (!nodes.empty()) {
    std::cout << nodes.top() << std::endl;
    nodes.pop();
  }
}

std::vector<int> collectReverseIter(const List &list) {
  std::stack<int> nodes;
  for (unsigned int i = 0; i < list.size(); i++)
    nodes.push(list.get(i));

  std::vector<int> result;
  while (!nodes.empty()) {
    result.push_back(nodes.top());
    nodes.pop();
  }
  return result;
}

// Recursive approach: prints the list in reverse by recursion.
// The parameter 'i' starts at -1 and is incremented until it reaches the last
// index.
void printReverseRecursive(List &list, int i = -1) {
  if (i == static_cast<int>(list.size()) - 1)
    return;

  i++;
  printReverseRecursive(list, i);
  std::cout << list.get(i) << std::endl;
}

void collectReverseRecursive(const List &list, std::vector<int> &out,
                             int i = -1) {
  if (i == static_cast<int>(list.size()) - 1)
    return;

  i++;
  collectReverseRecursive(list, out, i);
  out.push_back(list.get(i));
}

int main() {
  TestRunner runner;
  List list;
  list.append(1);
  list.append(2);
  list.append(3);

  std::vector<int> expected{3, 2, 1};
  runner.expectEqual(collectReverseIter(list), expected,
                     "reverse print iterative");
  std::vector<int> recursiveOut;
  collectReverseRecursive(list, recursiveOut);
  runner.expectEqual(recursiveOut, expected, "reverse print recursive");
  runner.summary();

  return 0;
}
