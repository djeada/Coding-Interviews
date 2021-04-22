#include <cassert>
#include <random>
#include <stdexcept>
#include <vector>

bool checkMajorityExistence(std::vector<int> arr, int number) {
  unsigned int times = 0;
  for (unsigned int i = 0; i < arr.size(); ++i) {
    if (arr[i] == number)
      times++;
  }
  return (times * 2 > arr.size());
}

int randomInRange(int start, int end) {
  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_int_distribution<> distr(start, end);
  return distr(eng);
}

int partition(std::vector<int> arr, int start, int end) {
  int index = randomInRange(start, end);
  std::swap(arr[index], arr[end]);

  int small = start - 1;
  for (index = start; index < end; ++index) {
    if (arr[index] < arr[end]) {
      ++small;
      if (small != index)
        std::swap(arr[index], arr[small]);
    }
  }
  ++small;
  std::swap(arr[index], arr[end]);

  return small;
}

int getMajority_1(std::vector<int> arr) {
  int length = arr.size();
  int middle = length >> 1;
  int start = 0;
  int end = length - 1;

  int index = partition(arr, start, end);
  while (index != middle) {
    if (index > middle) {
      end = index - 1;
      index = partition(arr, start, end);
    } else {
      start = index + 1;
      index = partition(arr, start, end);
    }
  }
  int result = arr[middle];
  if (!checkMajorityExistence(arr, result))
    throw std::invalid_argument("No majority exisits.");

  return result;
}

int getMajority_2(std::vector<int> arr) {
  int result = arr[0];
  int times = 1;
  for (unsigned int i = 1; i < arr.size(); ++i) {
    if (times == 0) {
      result = arr[i];
      times = 1;
    } else if (arr[i] == result)
      times++;
    else
      times--;
  }
  if (!checkMajorityExistence(arr, result))
    throw std::invalid_argument("No majority exisits.");

  return result;
}

void test1() {
  bool exceptionThrown = false;

  try {
    std::vector<int> arr{1, 2, 3, 4, 5};
    getMajority_1(arr);
  } catch (...) {
    exceptionThrown = true;
  }

  assert(exceptionThrown);
}

void test2() {
  bool exceptionThrown = false;

  try {
    std::vector<int> arr{1, 2, 3, 4, 5};
    getMajority_2(arr);
  } catch (...) {
    exceptionThrown = true;
  }

  assert(exceptionThrown);
}

void test3() {
  std::vector<int> arr{2, 2, 2, 2, 2, 1, 3, 4, 5};
  int result = 2;
  assert(getMajority_1(arr) == result);
}

void test4() {
  std::vector<int> arr{2, 2, 2, 2, 2, 1, 3, 4, 5};
  int result = 2;
  assert(getMajority_2(arr) == result);
}

int main() {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
