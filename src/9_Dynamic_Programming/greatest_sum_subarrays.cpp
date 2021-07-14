#include <cassert>
#include <vector>
#include <climits>

int getGreatestSumOfSubArray(std::vector<int> &numbers) {
  int curSum = 0;
  int greatestSum = INT_MIN;
  for (const auto &num : numbers) {
    if (curSum <= 0)
      curSum = num;
    else
      curSum += num;
    if (curSum > greatestSum)
      greatestSum = curSum;
  }
  return greatestSum;
}

void test1() {
  std::vector<int> numbers{1, -2, 3, 10, -4, 7, 2, -5};
  int expected = 18;

  assert(getGreatestSumOfSubArray(numbers) == expected);
}

void test2() {
  std::vector<int> numbers{-2, -8, -1, -5, -9};
  int expected = -1;

  assert(getGreatestSumOfSubArray(numbers) == expected);
}

void test3() {
  std::vector<int> numbers{2, 8, 1, 5, 9};
  int expected = 25;

  assert(getGreatestSumOfSubArray(numbers) == expected);
}

void test4() {
  std::vector<int> numbers{2};
  int expected = 2;

  assert(getGreatestSumOfSubArray(numbers) == expected);
}

int main() {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
