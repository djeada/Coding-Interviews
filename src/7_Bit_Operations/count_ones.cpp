/**
 * This program contains two functions to count the number of set bits (1s)
 * in an integer and test cases to validate their correctness.
 */

#include <cassert>
#include <iostream>

/**
 * @brief Counts the number of set bits (1s) in the binary representation of a
 * given integer using bit masking.
 *
 * @param number The integer whose set bits are to be counted.
 * @return The count of set bits in the input number.
 */
int countSetBitsUsingMask(int number) {
  int count = 0;
  unsigned int mask = 1;
  while (mask) {
    if (number & mask) {
      count++;
    }
    mask = mask << 1;
  }
  return count;
}

/**
 * @brief Counts the number of set bits (1s) in the binary representation of a
 * given integer using Brian Kernighan's Algorithm.
 *
 * @param number The integer whose set bits are to be counted.
 * @return The count of set bits in the input number.
 */
int countSetBitsUsingKernighan(int number) {
  int count = 0;
  while (number) {
    ++count;
    number = (number - 1) & number;
  }
  return count;
}

void runTests() {
  std::pair<int, int> testCases[] = {{0, 0}, {1, 1}, {10, 2}, {0x7FFFFFFF, 31}};

  for (const auto &[input, expectedResult] : testCases) {
    assert(countSetBitsUsingMask(input) == expectedResult);
    assert(countSetBitsUsingKernighan(input) == expectedResult);
  }
  std::cout << "All tests passed!\n";
}

int main() {
  runTests();
  return 0;
}
