/*
 * FIND NUMBERS OCCURRING ONCE
 *
 * This program finds the two unique numbers in an array where every other number appears exactly twice.
 * Two solutions are provided:
 *
 * 1. Simple (Brute-force) Solution using an unordered_map:
 *    Counts the frequency of each number and returns the ones that appear once.
 *    Complexity: O(n) time and O(n) space.
 *
 * 2. Optimal (Efficient) Solution using Bitwise XOR:
 *    Utilizes XOR properties to first get the XOR of the two unique numbers, then finds a bit where they differ
 *    and separates the numbers accordingly.
 *    Complexity: O(n) time and O(1) space.
 *
 * ASCII Illustration:
 *
 *   Input array: [2, 4, 3, 6, 3, 2, 5, 5]
 *
 *   - All numbers appearing twice cancel each other via XOR.
 *   - The result XOR gives us (4 XOR 6), meaning there is at least one bit set in the XOR of 4 and 6.
 *   - Using that bit, the array is partitioned into two groups that isolate 4 and 6.
 *
 * Example Input/Output:
 * Input:  [2, 4, 3, 6, 3, 2, 5, 5]
 * Output: [4, 6]  (order does not matter)
 */

#include <cassert>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

// Structure to store two numbers that occur only once in an array.
struct NumbersOccurringOnce {
  int num1;
  int num2;
};

// Simple (Brute-force) Solution using unordered_map
NumbersOccurringOnce simpleSolution(const std::vector<int>& numbers) {
  std::unordered_map<int, int> freq;
  for (const auto &num : numbers)
    ++freq[num];

  NumbersOccurringOnce result{0, 0};
  bool firstFound = false;
  for (const auto &entry : freq) {
    if (entry.second == 1) {
      if (!firstFound) {
        result.num1 = entry.first;
        firstFound = true;
      } else {
        result.num2 = entry.first;
        break;
      }
    }
  }
  return result;
}

// Optimal (Efficient) Solution using Bitwise XOR
int findFirstSetBit(int num) {
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

NumbersOccurringOnce optimalSolution(const std::vector<int>& numbers) {
  NumbersOccurringOnce result{0, 0};
  if (numbers.size() < 2)
    return result;

  int resultXOR = 0;
  for (const auto &num : numbers)
    resultXOR ^= num;

  int indexOf1 = findFirstSetBit(resultXOR);

  for (const auto &num : numbers) {
    if (isBitSet(num, indexOf1))
      result.num1 ^= num;
    else
      result.num2 ^= num;
  }
  return result;
}

// Test cases for correctness
void test(const std::string &testName, const std::vector<int> &numbers,
          const NumbersOccurringOnce &expected) {
  NumbersOccurringOnce simpleRes = simpleSolution(numbers);
  NumbersOccurringOnce optimalRes = optimalSolution(numbers);

  bool condition = 
      ((simpleRes.num1 == expected.num1 && simpleRes.num2 == expected.num2) ||
       (simpleRes.num1 == expected.num2 && simpleRes.num2 == expected.num1)) &&
      ((optimalRes.num1 == expected.num1 && optimalRes.num2 == expected.num2) ||
       (optimalRes.num1 == expected.num2 && optimalRes.num2 == expected.num1));

  assert(condition);
}

int main() {
  test("Test1", {2, 4, 3, 6, 3, 2, 5, 5}, {4, 6});
  test("Test2", {4, 6}, {4, 6});
  test("Test3", {4, 6, 1, 1, 1, 1}, {4, 6});

  std::cout << "All tests passed!\n";
  return 0;
}
