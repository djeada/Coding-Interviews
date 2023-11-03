#include "list.h"
#include <cassert>
#include <iostream>

List merge(const List &list1, const List &list2) {
  List result;

  unsigned int i = 0, j = 0;

  while (i < list1.size() && j < list2.size()) {
    auto data1 = list1.get(i);
    auto data2 = list2.get(j);

    if (data1 < data2) {
      result.append(data1);
      ++i;
    } else {
      result.append(data2);
      ++j;
    }
  }

  // Append remaining elements
  for (; i < list1.size(); ++i)
    result.append(list1.get(i));
  for (; j < list2.size(); ++j)
    result.append(list2.get(j));

  return result;
}

void test1() {
  List list1;
  list1.append(1);
  list1.append(3);
  list1.append(5);

  List list2;
  list2.append(2);
  list2.append(4);
  list2.append(6);

  List expected;
  expected.append(1);
  expected.append(2);
  expected.append(3);
  expected.append(4);
  expected.append(5);
  expected.append(6);

  auto result = merge(list1, list2);
  assert(result == expected);
}

void test2() {
  List list1;
  list1.append(1);
  list1.append(2);
  list1.append(3);

  List list2;
  list2.append(4);
  list2.append(5);
  list2.append(6);

  List expected;
  expected.append(1);
  expected.append(2);
  expected.append(3);
  expected.append(4);
  expected.append(5);
  expected.append(6);

  auto result = merge(list1, list2);
  assert(result == expected);
}

void test3() {
  List list1;
  list1.append(1);
  list1.append(2);
  list1.append(3);

  List list2;

  List expected;
  expected.append(1);
  expected.append(2);
  expected.append(3);

  auto result = merge(list1, list2);
  assert(result == expected);
}

void test4() {
  List list1;
  list1.append(1);
  list1.append(3);
  list1.append(5);

  List list2;
  list2.append(2);
  list2.append(4);
  list2.append(6);

  List expected;
  expected.append(1);
  expected.append(2);
  expected.append(3);
  expected.append(4);
  expected.append(5);
  expected.append(6);

  auto result = merge(list1, list2);
  assert(result == expected);
}

int main() {
  test1();
  test2();
  test3();
  test4();

  return 0;
}