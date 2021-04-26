#include <algorithm>
#include <exception>
#include <vector>
#include <cassert>

template <typename T> class DynamicArray {
public:
  void insert(T num) {
    if (((minHeap.size() + maxHeap.size()) & 1) == 0) {
      if (maxHeap.size() > 0 && num < maxHeap[0]) {
        maxHeap.push_back(num);
        std::push_heap(maxHeap.begin(), maxHeap.end(), std::less<T>());

        num = maxHeap[0];

        std::pop_heap(maxHeap.begin(), maxHeap.end(), std::less<T>());
        maxHeap.pop_back();
      }

      minHeap.push_back(num);
      push_heap(minHeap.begin(), minHeap.end(), std::greater<T>());
    } else {
      if (minHeap.size() > 0 && minHeap[0] < num) {
        minHeap.push_back(num);
        std::push_heap(minHeap.begin(), minHeap.end(), std::greater<T>());

        num = minHeap[0];

        std::pop_heap(minHeap.begin(), minHeap.end(), std::greater<T>());
        minHeap.pop_back();
      }

      maxHeap.push_back(num);
      std::push_heap(maxHeap.begin(), maxHeap.end(), std::less<T>());
    }
  }

  int getMedian() {
    int size = minHeap.size() + maxHeap.size();
    if (size == 0)
      throw std::runtime_error("No numbers are available");

    T median = 0;
    if (size & 1 == 1)
      median = minHeap[0];
    else
      median = (minHeap[0] + maxHeap[0]) / 2;

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

  return 0;
}
