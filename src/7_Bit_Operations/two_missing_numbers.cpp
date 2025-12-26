/*
 * FIND TWO MISSING NUMBERS IN A SEQUENCE
 *
 * This program finds two missing numbers from a sequence [1, 2, ..., n] when
 * given n-2 numbers. Two modern C++ methods are implemented:
 *
 * 1. Simple (Brute-force) Solution using Sum and Product:
 *    - Computes the sum and product of the expected full sequence and the given
 * numbers.
 *    - Derives the missing numbers by solving the equations:
 *         s = missing1 + missing2
 *         p = missing1 * missing2
 *    - Limitations: Risk of integer overflow in product calculation.
 *
 * 2. Optimal (Efficient) Solution using Bitwise XOR:
 *    - Merges the given numbers with the complete sequence.
 *    - Leverages XOR properties to cancel out duplicates and isolate the
 * missing numbers.
 *
 * ASCII Illustration:
 *
 *   Suppose n = 8 and the given numbers are: [1, 3, 5, 6, 4, 7]
 *   The full sequence is: [1, 2, 3, 4, 5, 6, 7, 8]
 *   Missing numbers: 2 and 8
 *
 * Example Input/Output:
 * Input:  [1, 3, 5, 6, 4, 7]
 * Output: [2, 8]  (order does not matter)
 */

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

// Simple (Brute-force) Solution using Sum and Product
std::pair<int, int> findMissingNumbersMethod1(const std::vector<int> &numbers) {
  std::pair<int, int> missing;
  int sumGiven = 0, prodGiven = 1;
  int n = static_cast<int>(numbers.size()) + 2;
  int sumFull = 0, prodFull = 1;

  for (int num : numbers) {
    sumGiven += num;
    prodGiven *= num;
  }
  for (int i = 1; i <= n; ++i) {
    sumFull += i;
    prodFull *= i;
  }

  int s = sumFull - sumGiven;   // Sum of the two missing numbers.
  int p = prodFull / prodGiven; // Product of the two missing numbers.

  // Solve the quadratic: x^2 - s*x + p = 0.
  missing.first = (s + static_cast<int>(sqrt(s * s - 4 * p))) / 2;
  missing.second = s - missing.first;

  if (missing.first > missing.second)
    std::swap(missing.first, missing.second);
  return missing;
}

// Helper function: Finds the position of the first set bit in num.
int findFirstSetBitPosition(int num) {
  int pos = 0;
  while (((num & 1) == 0) && (pos < 32)) {
    num >>= 1;
    ++pos;
  }
  return pos;
}

// Helper function: Checks if the bit at position pos is set.
bool isBitSet(int num, int pos) { return ((num >> pos) & 1) == 1; }

// Optimal (Efficient) Solution using Bitwise XOR
std::pair<int, int> findMissingNumbersMethod2(const std::vector<int> &numbers) {
  std::pair<int, int> missing;
  int n = static_cast<int>(numbers.size()) + 2;
  std::vector<int> combined;
  combined.reserve(numbers.size() + n);

  // Merge the given numbers with the complete sequence [1, 2, ..., n].
  combined.insert(combined.end(), numbers.begin(), numbers.end());
  for (int i = 1; i <= n; ++i) {
    combined.push_back(i);
  }

  int xorAll = 0;
  for (int num : combined) {
    xorAll ^= num;
  }

  int pos = findFirstSetBitPosition(xorAll);
  missing.first = missing.second = 0;

  for (int num : combined) {
    if (isBitSet(num, pos))
      missing.second ^= num;
    else
      missing.first ^= num;
  }

  if (missing.first > missing.second)
    std::swap(missing.first, missing.second);
  return missing;
}

// Test cases for correctness
void test() {
  using TestCase = std::pair<std::vector<int>, std::pair<int, int>>;
  std::vector<TestCase> testCases = {
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
  test();
  return 0;
}
