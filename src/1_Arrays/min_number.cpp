#include <algorithm>
#include <cassert>
#include <vector>

int minNumber(std::vector<int> &arr) {
  std::sort(arr.begin(), arr.end());
  return arr.front();
}

void test1() {
  std::vector<int> numbers{3, 5, 1, 4, 2};
  int result = 1;
  assert(minNumber(numbers) == result);
}

void test2() {
  std::vector<int> numbers{3, 5, 1, 4, 2};
  int result = 1;
  assert(minNumber(numbers) == result);
}

void test3() {
  std::vector<int> numbers{3, 5, 1, 4, 2};
  int result = 1;
  assert(minNumber(numbers) == result);
}

void test4() {
  std::vector<int> numbers{3, 5, 1, 4, 2};
  int result = 1;
  assert(minNumber(numbers) == result);
}

int main() {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
