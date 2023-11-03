/** *
 * This program defines a template class `DynamicArray` which efficiently
 * calculates the median of a dynamic set of numbers using two heaps (min and
 * max). The `getMedian()` function returns the current median of the set.
 */

#include <algorithm>
#include <cassert>
#include <exception>
#include <iostream>
#include <vector>

template <typename T> class DynamicArray {
public:
  void insert(T num) {
    if ((minHeap.size() + maxHeap.size()) % 2 == 0) {
      if (!maxHeap.empty() && num < maxHeap.front()) {
        maxHeap.push_back(num);
        std::push_heap(maxHeap.begin(), maxHeap.end(), std::less<T>());
        num = maxHeap.front();
        std::pop_heap(maxHeap.begin(), maxHeap.end(), std::less<T>());
        maxHeap.pop_back();
      }

      minHeap.push_back(num);
      std::push_heap(minHeap.begin(), minHeap.end(), std::greater<T>());
    } else {
      if (!minHeap.empty() && minHeap.front() < num) {
        minHeap.push_back(num);
        std::push_heap(minHeap.begin(), minHeap.end(), std::greater<T>());
        num = minHeap.front();
        std::pop_heap(minHeap.begin(), minHeap.end(), std::greater<T>());
        minHeap.pop_back();
      }

      maxHeap.push_back(num);
      std::push_heap(maxHeap.begin(), maxHeap.end(), std::less<T>());
    }
  }

  T getMedian() {
    int size = minHeap.size() + maxHeap.size();
    if (size == 0)
      throw std::runtime_error("No numbers are available");

    T median = 0;
    if (size % 2 == 1)
      median = minHeap.front();
    else
      median = (minHeap.front() + maxHeap.front()) / 2.0;

    return median;
  }

private:
  std::vector<T> minHeap;
  std::vector<T> maxHeap;
};

void test1() {
  DynamicArray<double> numbers;
  numbers.insert(5);
  double expected = 5;
  assert(abs(numbers.getMedian() - expected) < 0.0000001);
}

void test2() {
  DynamicArray<double> numbers;
  numbers.insert(5);
  numbers.insert(2);
  numbers.insert(3);
  numbers.insert(3);
  double expected = 3.5;
  assert(abs(numbers.getMedian() - expected) < 0.0000001);
}

int main() {
  test1();
  test2();
  std::cout << "All tests passed!\n";
  return 0;
}
