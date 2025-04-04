/**
 * This program identifies the majority element in an array.
 * A majority element is an element that appears more than n/2 times,
 * where n is the size of the array.
 * Two algorithms are provided: one using a partition-based approach,
 * and another using a counting approach.
 */

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

bool isMajorityElement(const std::vector<int> &arr, int candidate) {
  return std::count(arr.begin(), arr.end(), candidate) * 2 > arr.size();
}

int randomIndex(int start, int end) {
  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_int_distribution<> distr(start, end);
  return distr(eng);
}

int partition(std::vector<int> &arr, int start, int end) {
  int pivotIdx = randomIndex(start, end);
  std::swap(arr[pivotIdx], arr[end]);

  int small = start - 1;
  for (int idx = start; idx < end; ++idx) {
    if (arr[idx] < arr[end]) {
      ++small;
      if (small != idx)
        std::swap(arr[idx], arr[small]);
    }
  }
  ++small;
  std::swap(arr[small], arr[end]);

  return small;
}

int findMajorityPartition(std::vector<int> &arr) {
  int length = arr.size(), middle = length >> 1, start = 0, end = length - 1;

  int idx = partition(arr, start, end);
  while (idx != middle) {
    if (idx > middle) {
      end = idx - 1;
      idx = partition(arr, start, end);
    } else {
      start = idx + 1;
      idx = partition(arr, start, end);
    }
  }
  int candidate = arr[middle];
  if (!isMajorityElement(arr, candidate))
    throw std::invalid_argument("No majority exists.");

  return candidate;
}

int findMajorityCounting(const std::vector<int> &arr) {
  int candidate = arr[0], count = 1;
  for (size_t i = 1; i < arr.size(); ++i) {
    if (count == 0) {
      candidate = arr[i];
      count = 1;
    } else if (arr[i] == candidate)
      count++;
    else
      count--;
  }
  if (!isMajorityElement(arr, candidate))
    throw std::invalid_argument("No majority exists.");

  return candidate;
}

void testMajorityFinders() {
  // Wrap both majority finder functions in lambdas with the same signature.
  using MajorityFinder = std::function<int(std::vector<int>&)>;
  std::vector<MajorityFinder> majorityFinders = {
    [](std::vector<int>& arr) { return findMajorityPartition(arr); },
    [](std::vector<int>& arr) { return findMajorityCounting(arr); }
  };

  // Test cases where no majority exists.
  for (const auto &findMajority : majorityFinders) {
    std::vector<int> arr{1, 2, 3, 4, 5};
    bool exceptionThrown = false;

    try {
      findMajority(arr);
    } catch (...) {
      exceptionThrown = true;
    }
    assert(exceptionThrown);
  }

  // Test cases where a majority exists.
  std::vector<int> arr{2, 2, 2, 2, 2, 1, 3, 4, 5};
  std::vector<int> arrCopy = arr;  // Copy for the second method (since partition modifies the array)
  assert(findMajorityPartition(arr) == 2);
  assert(findMajorityCounting(arrCopy) == 2);
}

int main() {
  testMajorityFinders();
  return 0;
}
