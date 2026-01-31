#include "binary_tree.h"

#include <iostream>
#include <vector>

int main() {
  auto printContains = [](const BinaryTree &tree,
                          const std::vector<int> &values) {
    std::cout << "contains: ";
    for (int value : values) {
      std::cout << value << "=" << std::boolalpha << tree.contains(value)
                << " ";
    }
    std::cout << "\n";
  };

  auto printState = [](const std::string &label, const BinaryTree &tree) {
    std::cout << label << " size=" << tree.size()
              << " empty=" << std::boolalpha << tree.empty() << "\n";
  };

  BinaryTree tree;
  for (int value : {9, 8, 13, 4, 10, 16, 7, 15}) {
    tree.add(value);
  }
  printState("initial", tree);
  printContains(tree, {4, 7, 11, 15});

  BinaryTree copied(tree);
  printState("copied", copied);
  std::cout << "copied == tree? " << std::boolalpha << (copied == tree)
            << "\n";

  BinaryTree moved(std::move(tree));
  printState("moved", moved);
  printState("original after move", tree);

  moved.clear();
  printState("cleared moved", moved);

  return 0;
}
