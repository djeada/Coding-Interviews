/**
 * This program finds two missing numbers from a sequence [1, 2, ..., n]
 * given n-2 numbers using two methods.
 */

#include <cassert>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>


int findFirstSetBitPosition(int num) {
  int indexBit = 0;
  while (((num & 1) == 0) && (indexBit < 32)) {
    num >>= 1;
    ++indexBit;
  }
  return indexBit;
}


bool isBitSet(int num, int indexBit) {
  num >>= indexBit;
  return (num & 1) == 1;
}


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

  // Calculate the sum and product of the given numbers.
  for (const auto &num : numbers) {
    sum1 += num;
    product1 *= num;
  }

  // Calculate the sum and product for the full sequence [1, 2, ..., n].
  for (int i = 1; i <= numbers.size() + 2; ++i) {
    sum2 += i;
    product2 *= i;
  }

  int s = sum2 - sum1;          // Sum of the two missing numbers.
  int p = product2 / product1;  // Product of the two missing numbers.

  // Solve the quadratic equation: x^2 - s*x + p = 0.
  missing.first = (s + static_cast<int>(sqrt(s * s - 4 * p))) / 2;
  missing.second = s - missing.first;

  // Ensure the smaller number is first.
  if (missing.first > missing.second)
    std::swap(missing.first, missing.second);

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
