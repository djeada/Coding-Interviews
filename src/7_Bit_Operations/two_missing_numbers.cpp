/**
 * This program finds two missing numbers from a sequence [1, 2, ..., n]
 * given n-2 numbers using two methods.
 */

#include <cassert>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

/**
 * @brief Finds the position of the first bit that is set to 1.
 *
 * @param num The input number.
 * @return The position of the first set bit.
 */
int findFirstSetBitPosition(int num) {
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
 * @param numbers Input array of integers.
 * @param once Pair to store the two numbers that appear only once.
 */
void findSingleOccurrences(std::vector<int> &numbers,
                           std::pair<int, int> &once) {
  if (numbers.size() < 2)
    return;

  int resultXOR = 0;
  for (const auto &num : numbers)
    resultXOR ^= num;

  int indexOf1 = findFirstSetBitPosition(resultXOR);
  once.first = once.second = 0;

  for (const auto &num : numbers) {
    if (isBitSet(num, indexOf1))
      once.second ^= num;
    else
      once.first ^= num;
  }
}

std::pair<int, int> findMissingNumbersMethod1(const std::vector<int> &numbers) {
  std::pair<int, int> missing;
  int sum1 = 0, product1 = 1, sum2 = 0, product2 = 1;

  for (const auto &num : numbers) {
    sum1 += num;
    product1 *= num;
  }

  for (int i = 1; i <= numbers.size() + 2; ++i) {
    sum2 += i;
    product2 *= i;
  }

  int s = sum2 - sum1;
  int p = product2 / product1;

  missing.first = (s + static_cast<int>(sqrt(s * s - 4 * p))) / 2;
  missing.second = s - missing.first;

  return missing;
}

std::pair<int, int> findMissingNumbersMethod2(const std::vector<int> &numbers) {
  std::pair<int, int> missing;
  int extendedLength = numbers.size() * 2 + 2;
  std::vector<int> extension(extendedLength, 0);

  for (int i = 0; i < numbers.size(); ++i)
    extension[i] = numbers[i];
  for (int i = numbers.size(); i < extendedLength; ++i)
    extension[i] = i - numbers.size() + 1;

  findSingleOccurrences(extension, missing);

  if (missing.first > missing.second)
    std::swap(missing.first, missing.second);
  return missing;
}

void runTests() {
  std::vector<std::pair<std::vector<int>, std::pair<int, int>>> testCases = {
      {{1, 3, 5, 6, 4, 7}, {2, 8}},
      {{1}, {2, 3}},
      {{3, 4}, {1, 2}},
  };

  for (const auto &[input, expected] : testCases) {
    assert(findMissingNumbersMethod1(input) == expected);
    assert(findMissingNumbersMethod2(input) == expected);
  }
  std::cout << "All tests passed!\n";
}

int main() {
  runTests();
  return 0;
}
