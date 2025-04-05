/*
 * PRINT LINKED LIST IN REVERSE ORDER
 *
 * This program demonstrates two approaches to print the elements of a linked list in reverse order.
 *
 * 1. Iterative Approach:
 *    - Uses a stack to store list elements and then prints them in reverse order by popping the stack.
 *    - Time Complexity: O(n), Space Complexity: O(n)
 *
 * 2. Recursive Approach:
 *    - Uses recursion to traverse the list to the end and then prints the elements as the recursion unwinds.
 *    - Time Complexity: O(n), Space Complexity: O(n) due to the recursion stack.
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
#include <stack>

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

// Recursive approach: prints the list in reverse by recursion.
// The parameter 'i' starts at -1 and is incremented until it reaches the last index.
void printReverseRecursive(List &list, int i = -1) {
  if (i == static_cast<int>(list.size()) - 1)
    return;

  i++;
  printReverseRecursive(list, i);
  std::cout << list.get(i) << std::endl;
}

int main() {
  List list;
  list.append(1);
  list.append(2);
  list.append(3);

  std::cout << "Printing the list in reverse iteratively: " << std::endl;
  printReverseIter(list);

  std::cout << "Printing the list in reverse recursively: " << std::endl;
  printReverseRecursive(list);

  return 0;
}
