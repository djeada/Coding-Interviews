/*
 * COUNT BITS TO MODIFY
 *
 * This program calculates the number of bits that need to be flipped to convert
 * one integer to another. In other words, it finds the number of bit positions
 * where the two numbers differ. This is done by computing the XOR of the two
 * numbers and counting the number of set bits (1s) in the result.
 *
 * Three modern C++ solutions are provided:
 *
 * 1. Simple (Brute-force) Solution:
 *    Iterates through every bit of the XOR result (assumed 32 bits) and counts
 * the 1s. Complexity: O(n) where n is the number of bits (typically 32 or 64).
 *
 * 2. Optimal (Efficient) Solution using Brian Kernighan's Algorithm:
 *    Repeatedly removes the rightmost set bit until the XOR result becomes 0.
 *    Complexity: O(k) where k is the number of set bits.
 *
 * 3. Additional Modern Alternative using std::popcount (C++20):
 *    Utilizes the built-in popcount function to directly count the set bits.
 *    Complexity: Typically O(1) if hardware instructions are available.
 *
 * ASCII Illustration:
 *
 *   Consider number1 = 13 (binary: 1101) and number2 = 0 (binary: 0000)
 *
 *      13 (1101)
 *   XOR  0 (0000)
 *   ------------
 *         1101  -> 3 set bits (1s)
 *
 * Example Input/Output:
 * Input:  number1 = 13, number2 = 0
 * Output: 3
 *
 * Explanation:
 * The binary representation of 13 is "1101", which differs from "0000" in three
 * positions.
 */

#include <bit> // for std::popcount (C++20)
#include <cassert>
#include <iostream>
#include <vector>

// Simple (Brute-force) Solution
// Iterates through each bit (assuming 32-bit integers) of the XOR result.
int simpleSolution(int number1, int number2) {
  int xorResult = number1 ^ number2;
  int count = 0;
  for (int i = 0; i < 32; ++i) {
    count += ((xorResult >> i) & 1);
  }
  return count;
}

// Optimal (Efficient) Solution using Brian Kernighan's Algorithm
// Repeatedly removes the rightmost set bit until xorResult is 0.
int optimalSolution(int number1, int number2) {
  int xorResult = number1 ^ number2;
  int count = 0;
  while (xorResult) {
    xorResult &= (xorResult - 1);
    ++count;
  }
  return count;
}

// Additional Modern Alternative using std::popcount (C++20)
// Directly counts the number of set bits in the XOR result.
int alternativeSolution(int number1, int number2) {
  return std::popcount(static_cast<unsigned int>(number1 ^ number2));
}

// Test cases for correctness
void test() {
  struct TestCase {
    int number1;
    int number2;
    int expected;
  };

  std::vector<TestCase> testCases = {
      {0, 13, 3},
      {0, 15, 4},
      {7, 0, 3},
      {7, 7, 0},
      {29, 15, 2} // 29 (11101) XOR 15 (01111) = 18 (10010) -> 2 set bits
  };

  for (const auto &tc : testCases) {
    int resSimple = simpleSolution(tc.number1, tc.number2);
    int resOptimal = optimalSolution(tc.number1, tc.number2);
    int resAlternative = alternativeSolution(tc.number1, tc.number2);
    assert(resSimple == tc.expected);
    assert(resOptimal == tc.expected);
    assert(resAlternative == tc.expected);
  }
  std::cout << "All tests passed!\n";
}

int main() {
  test();
  return 0;
}
