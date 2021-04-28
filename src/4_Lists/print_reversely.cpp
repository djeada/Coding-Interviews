#include "list.h"
#include <iostream>
#include <stack>

void printReverseIter(List &list) {
  std::stack<int> nodes;

  for (unsigned int i = 0; i < list.size(); i++)
    nodes.push(list.get(i));

  while (!nodes.empty()) {
    std::cout << nodes.top() << std::endl;
    nodes.pop();
  }
}

void printReverseRecursive(List &list, int i = -1) {

  if (i == list.size() - 1)
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
