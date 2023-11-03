/**
 * This program calculates the number of bits needed to be flipped
 * to convert one integer to another.
 */

#include <cassert>
#include <iostream>
#include <utility>

/**
 * @brief Computes the number of bits that need to be flipped to convert one
 * integer to another.
 *
 * @param number1 The first integer.
 * @param number2 The second integer.
 * @return The number of bits that need to be flipped to convert number1 to
 * number2.
 */
int countBitsToModify(int number1, int number2) {
  int xorResult = number1 ^ number2;

  int bitCount = 0;
  while (xorResult != 0) {
    ++bitCount;
    xorResult = (xorResult - 1) & xorResult;
  }

  return bitCount;
}

void runTests() {
  std::pair<std::pair<int, int>, int> testCases[] = {
      {{0, 13}, 3}, {{0, 15}, 4}, {{7, 0}, 3}, {{7, 7}, 0}};

  for (const auto &[input, expectedResult] : testCases) {
    const auto &[number1, number2] = input;
    assert(countBitsToModify(number1, number2) == expectedResult);
  }
  std::cout << "All tests passed!\n";
}

int main() {
  runTests();
  return 0;
}
