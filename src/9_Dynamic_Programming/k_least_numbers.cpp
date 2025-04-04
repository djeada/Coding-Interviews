/**
 * This program finds the smallest 'k' numbers from a given list of numbers.
 * It uses a max heap (priority queue) to keep track of the smallest numbers
 * encountered so far.
 */

#include <algorithm>
#include <cassert>
#include <queue>
#include <vector>

std::vector<int> findSmallestKNumbers(const std::vector<int> &input, int k) {
  std::vector<int> output;
  std::priority_queue<int> maxHeap;

  for (const auto &num : input) {
    if (maxHeap.size() < k) {
      maxHeap.push(num);
    } else if (num < maxHeap.top()) {
      maxHeap.pop();
      maxHeap.push(num);
    }
  }

  while (!maxHeap.empty()) {
    output.push_back(maxHeap.top());
    maxHeap.pop();
  }

  std::sort(output.begin(), output.end());
  return output;
}

void testFindSmallestKNumbers() {
  assert(findSmallestKNumbers({4, 5, 1, 6, 2, 7, 3, 8}, 4) ==
         (std::vector<int>{1, 2, 3, 4}));
  assert(findSmallestKNumbers({4, 5, 1, 6, 2, 7, 3, 8}, 8) ==
         (std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8}));
  assert(findSmallestKNumbers({4, 5, 1, 6, 2, 7, 3, 8}, 1) ==
         (std::vector<int>{1}));
  assert(findSmallestKNumbers({4, 5, 1, 6, 2, 7, 2, 8}, 2) ==
         (std::vector<int>{1, 2}));
}

int main() {
  testFindSmallestKNumbers();
  return 0;
}
