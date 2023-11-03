#include <cassert>
#include <iostream>
#include <vector>

/**
 * @struct NumbersOccurringOnce
 * @brief A structure to store two numbers that occur only once in an array.
 */
struct NumbersOccurringOnce {
  int num1;
  int num2;
};

/**
 * @brief Finds the position of the first bit set to 1 in a number.
 *
 * @param num The input number.
 * @return The position of the first set bit.
 */
int findFirstSetBit(int num) {
  int indexBit = 0;
  while (((num & 1) == 0) && (indexBit < 32)) {
    num >>= 1;
    ++indexBit;
  }
  return indexBit;
}

/**
 * @brief Checks if the bit at a specified position is set to 1.
 *
 * @param num The input number.
 * @param indexBit The position to check.
 * @return true if the bit at the specified position is 1, otherwise false.
 */
bool isBitSet(int num, int indexBit) {
  num >>= indexBit;
  return (num & 1) == 1;
}

/**
 * @brief Finds two numbers that appear only once in a given array.
 *
 * @param numbers The input array of integers.
 * @param once A reference to the struct storing the two numbers.
 */
void findSingleOccurrences(const std::vector<int> &numbers,
                           NumbersOccurringOnce &once) {
  once.num1 = once.num2 = 0;
  if (numbers.size() < 2)
    return;

  int resultXOR = 0;
  for (const auto &num : numbers)
    resultXOR ^= num;

  int indexOf1 = findFirstSetBit(resultXOR);

  for (const auto &num : numbers) {
    if (isBitSet(num, indexOf1))
      once.num1 ^= num;
    else
      once.num2 ^= num;
  }
}

void test(const std::string &testName, const std::vector<int> &numbers,
          const NumbersOccurringOnce &expected) {
  NumbersOccurringOnce once;
  findSingleOccurrences(numbers, once);

  bool condition = (once.num1 == expected.num1 && once.num2 == expected.num2) ||
                   (once.num1 == expected.num2 && once.num2 == expected.num1);
  assert(condition);
}

int main() {
  test("Test1", {2, 4, 3, 6, 3, 2, 5, 5}, {4, 6});
  test("Test2", {4, 6}, {4, 6});
  test("Test3", {4, 6, 1, 1, 1, 1}, {4, 6});

  return 0;
}
