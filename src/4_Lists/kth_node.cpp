/*
 * FIND KTH TO TAIL ELEMENT IN A LINKED LIST
 *
 * This program finds the kth element from the tail (0-indexed) of a singly linked list.
 * Three solutions are provided:
 *
 * 1. Simple Solution:
 *    - Traverses the list to store all elements in a vector and then indexes from the end.
 *    - Easy to implement and understand, but uses O(n) extra space.
 *
 * 2. Optimal (Efficient) Solution:
 *    - Uses the two-pointer technique: one pointer is moved k steps ahead,
 *      then both pointers move until the lead pointer reaches the end.
 *    - Achieves O(n) time and O(1) space complexity.
 *
 * 3. Alternative Solution:
 *    - Uses recursion to determine the kth element from the tail.
 *    - Although elegant, it uses additional stack space due to recursive calls.
 *
 * ASCII Illustration:
 *
 *      Linked List: 1 -> 2 -> 3 -> 4 -> 5
 *
 *      For k = 0 (0th from tail), the answer is 5.
 *      For k = 4 (4th from tail), the answer is 1.
 *
 * Example Input/Output:
 * Input:  List = 1 -> 2 -> 3 -> 4 -> 5, k = 1
 * Output: 4
 *
 * Explanation:
 * For k=1, the kth element from the tail is the second-to-last element in the list.
 */

#include "list.h"
#include <cassert>
#include <stdexcept>
#include <vector>
#include <functional>

// Inherits from the pre-defined List class.
class ListWithFind : public List {
public:
  ListWithFind() : List() {}

  // ---------------- Simple (Brute-force) Solution ----------------
  // Traverse the list and store the elements in a vector.
  // Then, return the element at the position (size - 1 - k).
  int findKthToTailSimple(unsigned int k) {
    std::vector<int> elems;
    for (auto* node = head.get(); node != nullptr; node = node->next.get()) {
      elems.push_back(node->data);
    }
    if (k >= elems.size())
      throw std::out_of_range("Index out of range!");
    return elems[elems.size() - 1 - k];
  }

  // ---------------- Optimal (Efficient) Solution ----------------
  // Uses a two-pointer technique to find the kth element from the tail in one pass.
  int findKthToTailOptimal(unsigned int k) {
    if (empty())
      throw std::out_of_range("Index out of range!");
    auto* current = head.get();
    auto* follower = head.get();
    for (unsigned int i = 0; i < k; ++i) {
      if (!current->next)
        throw std::out_of_range("Index out of range!");
      current = current->next.get();
    }
    while (current->next) {
      current = current->next.get();
      follower = follower->next.get();
    }
    return follower->data;
  }

  // ---------------- Alternative Solution ----------------
  // Recursive approach: traverses to the end and then counts backwards.
  // The helper function returns the count from the tail.
  int findKthToTailAlternativeHelper(Node* node, unsigned int k, int& result) {
    if (!node)
      return 0;
    int index = findKthToTailAlternativeHelper(node->next.get(), k, result) + 1;
    if (index - 1 == k)
      result = node->data;
    return index;
  }
  int findKthToTailAlternative(unsigned int k) {
    int result = -1;
    int count = findKthToTailAlternativeHelper(head.get(), k, result);
    if (k >= static_cast<unsigned int>(count))
      throw std::out_of_range("Index out of range!");
    return result;
  }
};

// ---------------- Test Cases ----------------
void test1() {
  ListWithFind list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);

  int k = 0;
  int expected = 5;
  assert(list.findKthToTailSimple(k) == expected);
  assert(list.findKthToTailOptimal(k) == expected);
  assert(list.findKthToTailAlternative(k) == expected);
}

void test2() {
  ListWithFind list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);

  int k = 4;
  int expected = 1;
  assert(list.findKthToTailSimple(k) == expected);
  assert(list.findKthToTailOptimal(k) == expected);
  assert(list.findKthToTailAlternative(k) == expected);
}

void test3() {
  ListWithFind list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);

  int k = 1;
  int expected = 4;
  assert(list.findKthToTailSimple(k) == expected);
  assert(list.findKthToTailOptimal(k) == expected);
  assert(list.findKthToTailAlternative(k) == expected);
}

void test4() {
  ListWithFind list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);

  int k = 10;
  bool exceptionThrown = false;
  try {
    list.findKthToTailSimple(k);
  } catch (...) {
    exceptionThrown = true;
  }
  assert(exceptionThrown);

  exceptionThrown = false;
  try {
    list.findKthToTailOptimal(k);
  } catch (...) {
    exceptionThrown = true;
  }
  assert(exceptionThrown);

  exceptionThrown = false;
  try {
    list.findKthToTailAlternative(k);
  } catch (...) {
    exceptionThrown = true;
  }
  assert(exceptionThrown);
}

int main() {
  test1();
  test2();
  test3();
  test4();
  return 0;
}
