#include "list.h"

#include <iostream>
#include <sstream>

int main() {
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

  auto printState = [&](const std::string &label, const List &list) {
    std::cout << label << " size=" << list.size()
              << " empty=" << std::boolalpha << list.empty()
              << " values=" << listToString(list) << "\n";
  };

  List list;
  for (int value : {1, 2, 3, 4}) {
    list.append(value);
  }
  printState("initial", list);

  std::cout << "get(2)=" << list.get(2) << "\n";

  List copied(list);
  printState("copied", copied);
  std::cout << "copied == list? " << std::boolalpha << (copied == list)
            << "\n";

  list.connectNodes(0, 3);
  printState("after connectNodes(0,3)", list);

  List moved(std::move(list));
  printState("moved", moved);
  printState("original after move", list);

  moved.clear();
  printState("cleared moved", moved);

  return 0;
}
