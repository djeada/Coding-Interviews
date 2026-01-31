/*
 * Task: Merge two sorted linked lists into one sorted list.
 *
 * MERGE TWO SORTED LINKED LISTS
 *
 * Merge two sorted linked lists into a single sorted list. Two solutions are
 * provided:
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
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// ---------------- Optimal (Two-Pointer) Solution ----------------
List mergeTwoPointer(const List &list1, const List &list2) {
  List result;
  auto it1 = list1.begin();
  auto it2 = list2.begin();
  const auto end1 = list1.end();
  const auto end2 = list2.end();

  while (it1 != end1 && it2 != end2) {
    if (*it1 < *it2) {
      result.append(*it1);
      ++it1;
    } else {
      result.append(*it2);
      ++it2;
    }
  }

  // Append any remaining elements.
  for (; it1 != end1; ++it1)
    result.append(*it1);
  for (; it2 != end2; ++it2)
    result.append(*it2);

  return result;
}

// ---------------- Alternative (Concatenate and Sort) Solution ----------------
List mergeConcatenateAndSort(const List &list1, const List &list2) {
  std::vector<int> elems;
  elems.reserve(list1.size() + list2.size());
  for (int value : list1)
    elems.push_back(value);
  for (int value : list2)
    elems.push_back(value);

  std::sort(elems.begin(), elems.end());

  List sortedResult;
  for (int val : elems)
    sortedResult.append(val);

  return sortedResult;
}

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
    expectEqual(result, expected, "merge two-pointer #1");
  }

  {
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
    expectEqual(result, expected, "merge two-pointer #2");
  }

  {
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
    expectEqual(result, expected, "merge two-pointer list2 empty");
  }

  {
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
    expectEqual(result, expected, "merge two-pointer #3");
  }

  {
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
    expectEqual(result, expected, "merge concatenate+sort");
  }

  summary();
  return 0;
}
