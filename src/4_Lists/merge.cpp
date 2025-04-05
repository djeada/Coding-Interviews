/*
 * MERGE TWO SORTED LINKED LISTS
 *
 * This program merges two sorted linked lists into a single sorted list.
 * Two solutions are provided:
 *
 * 1. Optimal (Two-Pointer) Solution:
 *    - Uses two indices to traverse both lists simultaneously, appending the
 *      smaller element at each step.
 *    - Time Complexity: O(n + m) where n and m are the sizes of the two lists.
 *
 * 2. Alternative (Concatenate and Sort) Solution:
 *    - First concatenates both lists into one, then sorts the resulting list.
 *    - Simpler to implement but less efficient due to the sorting step.
 *    - Time Complexity: O((n + m) log(n + m))
 *
 * ASCII Illustration:
 *
 *    List1: 1 -> 3 -> 5
 *    List2: 2 -> 4 -> 6
 *
 *    Merged: 1 -> 2 -> 3 -> 4 -> 5 -> 6
 *
 * Example:
 * Input:  list1 = [1, 3, 5], list2 = [2, 4, 6]
 * Output: [1, 2, 3, 4, 5, 6]
 *
 * Edge Cases:
 * - One or both lists are empty.
 * - Lists of different lengths.
 */

#include "list.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>

// ---------------- Optimal (Two-Pointer) Solution ----------------
List mergeTwoPointer(const List &list1, const List &list2) {
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
  
  // Append any remaining elements.
  for (; i < list1.size(); ++i)
    result.append(list1.get(i));
  for (; j < list2.size(); ++j)
    result.append(list2.get(j));
  
  return result;
}

// ---------------- Alternative (Concatenate and Sort) Solution ----------------
List mergeConcatenateAndSort(const List &list1, const List &list2) {
  List result;
  
  // Concatenate list1 and list2 into result.
  for (unsigned int i = 0; i < list1.size(); ++i)
    result.append(list1.get(i));
  for (unsigned int j = 0; j < list2.size(); ++j)
    result.append(list2.get(j));
  
  // Extract elements, sort them, and rebuild the list.
  std::vector<int> elems;
  for (unsigned int i = 0; i < result.size(); ++i)
    elems.push_back(result.get(i));
  
  std::sort(elems.begin(), elems.end());
  
  List sortedResult;
  for (int val : elems)
    sortedResult.append(val);
  
  return sortedResult;
}

// ------------------- Test Cases -------------------

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

  auto result = mergeTwoPointer(list1, list2);
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

  auto result = mergeTwoPointer(list1, list2);
  assert(result == expected);
}

void test3() {
  List list1;
  list1.append(1);
  list1.append(2);
  list1.append(3);

  List list2; // Empty list

  List expected;
  expected.append(1);
  expected.append(2);
  expected.append(3);

  auto result = mergeTwoPointer(list1, list2);
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

  auto result = mergeTwoPointer(list1, list2);
  assert(result == expected);
}

void testAlternative() {
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

  auto result = mergeConcatenateAndSort(list1, list2);
  assert(result == expected);
}

int main() {
  test1();
  test2();
  test3();
  test4();
  testAlternative();

  std::cout << "All tests passed!\n";
  return 0;
}
