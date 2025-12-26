/*
 * COUNT SET BITS IN INTEGER
 *
 * This program demonstrates three modern C++ implementations to count the
 * number of set bits (1s) in the binary representation of an integer. It
 * includes:
 *
 * 1. Simple (Brute-force) Solution using Bit Masking:
 *    Iterates through every bit position using a shifting mask.
 *    Complexity: O(n) where n is the number of bits (fixed at 32 or 64).
 *
 * 2. Optimal (Efficient) Solution using Brian Kernighan's Algorithm:
 *    Repeatedly removes the lowest set bit until the number is zero.
 *    Complexity: O(k) where k is the number of set bits.
 *
 * 3. Additional Modern C++ Alternative using std::bitset:
 *    Leverages the standard library's bitset to count set bits.
 *
 * ASCII Illustration:
 *
 *      Input number: 13 (binary: 1101)
 *                13  =  1 1 0 1
 *                         ↑   ↑
 *                set bits: 3 (three ones)
 *
 * Example Input/Output:
 * Input:  13
 * Output: 3
 *
 * Explanation:
 * The binary representation of 13 is "1101", which contains three set bits.
 */

#include <algorithm>
#include <bitset>
#include <cassert>
#include <iostream>
#include <vector>

// Simple (Brute-force) Solution using Bit Masking
int countSetBitsSimple(int number) {
  int count = 0;
  for (unsigned int mask = 1; mask; mask <<= 1) {
    if (number & mask) {
      ++count;
    }
  }
  return count;
}

// Optimal (Efficient) Solution using Brian Kernighan's Algorithm
int countSetBitsOptimal(int number) {
  int count = 0;
  while (number) {
    number &= (number - 1);
    ++count;
  }
  return count;
}

// Additional Modern C++ Alternative using std::bitset
int countSetBitsAlternative(int number) {
  return static_cast<int>(std::bitset<32>(number).count());
}

// Test cases for correctness
void test() {
  std::vector<std::pair<int, int>> testCases = {
      {0, 0},
      {1, 1},
      {13, 3},  // 13 in binary: 1101
      {255, 8}, // 255 in binary: 11111111
      {0x7FFFFFFF, 31}};

  for (const auto &testCase : testCases) {
    int input = testCase.first;
    int expected = testCase.second;
    assert(countSetBitsSimple(input) == expected);
    assert(countSetBitsOptimal(input) == expected);
    assert(countSetBitsAlternative(input) == expected);
  }

  std::cout << "All tests passed!\n";
}

int main() {
  test();
  return 0;
}
