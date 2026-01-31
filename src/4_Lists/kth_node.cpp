/*
 * Task: Find the kth element from the tail of a singly linked list.
 *
 * FIND KTH TO TAIL ELEMENT IN A LINKED LIST
 *
 * Find the kth element from the tail (0-indexed) of a singly linked list.
 * Three solutions are provided:
 *
 * 1. Simple Solution:
 *    - Traverses the list to store all elements in a vector and then indexes
 * from the end.
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
 * For k=1, the kth element from the tail is the second-to-last element in the
 * list.
 */

#include "list.h"
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// Inherits from the pre-defined List class.
class ListWithFind : public List {
public:
  ListWithFind() : List() {}

  // ---------------- Simple (Brute-force) Solution ----------------
  // Traverse the list and store the elements in a vector.
  // Then, return the element at the position (size - 1 - k).
  int findKthToTailSimple(unsigned int k) {
    std::vector<int> elems;
    for (auto *node = head.get(); node != nullptr; node = node->next.get()) {
      elems.push_back(node->data);
    }
    if (k >= elems.size())
      throw std::out_of_range("Index out of range!");
    return elems[elems.size() - 1 - k];
  }

  // ---------------- Optimal (Efficient) Solution ----------------
  // Uses a two-pointer technique to find the kth element from the tail in one
  // pass.
  int findKthToTailOptimal(unsigned int k) {
    if (empty())
      throw std::out_of_range("Index out of range!");
    auto *current = head.get();
    auto *follower = head.get();
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
  int findKthToTailAlternativeHelper(Node *node, unsigned int k, int &result) {
    if (!node)
      return 0;
    int index = findKthToTailAlternativeHelper(node->next.get(), k, result) + 1;
    if (index - 1 == static_cast<int>(k))
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

int main() {
  int total = 0;
  int failed = 0;

  auto expectEqual = [&](int got, int expected, const std::string &label) {
    ++total;
    if (got == expected) {
      std::cout << "[PASS] " << label << "\n";
      return;
    }
    ++failed;
    std::cout << "[FAIL] " << label << " expected=" << expected
              << " got=" << got << "\n";
  };

  auto expectThrows = [&](const std::function<void()> &fn,
                          const std::string &label) {
    ++total;
    try {
      fn();
      ++failed;
      std::cout << "[FAIL] " << label << " expected=throw got=no throw\n";
    } catch (const std::exception &ex) {
      std::cout << "[PASS] " << label << " threw=\"" << ex.what() << "\"\n";
    } catch (...) {
      std::cout << "[PASS] " << label << " threw=non-std exception\n";
    }
  };

  auto summary = [&]() {
    std::cout << "Tests: " << total - failed << " passed, " << failed
              << " failed, " << total << " total\n";
  };

  {
    ListWithFind list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);

    int k = 0;
    int expected = 5;
    expectEqual(list.findKthToTailSimple(k), expected, "simple k=0");
    expectEqual(list.findKthToTailOptimal(k), expected, "optimal k=0");
    expectEqual(list.findKthToTailAlternative(k), expected, "alternative k=0");
  }

  {
    ListWithFind list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);

    int k = 4;
    int expected = 1;
    expectEqual(list.findKthToTailSimple(k), expected, "simple k=4");
    expectEqual(list.findKthToTailOptimal(k), expected, "optimal k=4");
    expectEqual(list.findKthToTailAlternative(k), expected, "alternative k=4");
  }

  {
    ListWithFind list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);

    int k = 1;
    int expected = 4;
    expectEqual(list.findKthToTailSimple(k), expected, "simple k=1");
    expectEqual(list.findKthToTailOptimal(k), expected, "optimal k=1");
    expectEqual(list.findKthToTailAlternative(k), expected, "alternative k=1");
  }

  {
    ListWithFind list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);

    int k = 10;
    expectThrows([&]() { list.findKthToTailSimple(k); },
                 "simple k=10 throws");
    expectThrows([&]() { list.findKthToTailOptimal(k); },
                 "optimal k=10 throws");
    expectThrows([&]() { list.findKthToTailAlternative(k); },
                 "alternative k=10 throws");
  }

  summary();
  return 0;
}
