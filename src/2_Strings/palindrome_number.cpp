/*
 * PALINDROME INTEGER CHECK
 *
 * Given an integer, determine whether it is a palindrome. An integer is a
 * palindrome if it reads the same backward as forward.
 *
 * This task provides two approaches:
 * 1. Convert the integer to a string and compare characters.
 * 2. Reverse the integer mathematically and compare with the original.
 *
 * Constraints:
 * - The integer can be positive, zero, or negative.
 * - Negative integers are not considered palindromes.
 *
 * Example Input/Output:
 * Input: 121
 * Output: true
 *
 * Input: -121
 * Output: false
 * Explanation: Negative numbers are not palindromes.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

// Simple Solution (string conversion) O(N)
bool simpleSolution(int x) {
  if (x < 0)
    return false;
  std::string s = std::to_string(x);
  int n = s.size();
  for (int i = 0; i < n / 2; ++i) {
    if (s[i] != s[n - i - 1])
      return false;
  }
  return true;
}

// Optimal Solution (numeric reversal) O(N)
bool optimalSolution(int x) {
  if (x < 0 || (x % 10 == 0 && x != 0))
    return false;
  int original = x, reversed = 0;
  while (x > 0) {
    reversed = reversed * 10 + (x % 10);
    x /= 10;
  }
  return reversed == original;
}

struct TestCase {
  std::string name;
  int input;
  bool expected;
};

void testSimple(const std::vector<TestCase> &cases) {
  std::cout << "=== Testing simpleSolution ===\n";
  for (const auto &tc : cases) {
    bool got = simpleSolution(tc.input);
    bool pass = (got == tc.expected);
    std::cout << tc.name << ": input=" << tc.input
              << ", expected=" << (tc.expected ? "true" : "false")
              << ", got=" << (got ? "true" : "false") << " -> "
              << (pass ? "PASS" : "FAIL") << "\n";
    assert(pass);
  }
  std::cout << "\n";
}

void testOptimal(const std::vector<TestCase> &cases) {
  std::cout << "=== Testing optimalSolution ===\n";
  for (const auto &tc : cases) {
    bool got = optimalSolution(tc.input);
    bool pass = (got == tc.expected);
    std::cout << tc.name << ": input=" << tc.input
              << ", expected=" << (tc.expected ? "true" : "false")
              << ", got=" << (got ? "true" : "false") << " -> "
              << (pass ? "PASS" : "FAIL") << "\n";
    assert(pass);
  }
  std::cout << "\n";
}

int main() {
  std::vector<TestCase> cases = {{"Palindrome positive", 121, true},
                                 {"Negative number", -121, false},
                                 {"Non-palindrome", 1234, false},
                                 {"Even-length palindrome", 1331, true},
                                 {"Zero", 0, true},
                                 {"Trailing zero", 10, false},
                                 {"Single digit", 7, true}};

  testSimple(cases);
  testOptimal(cases);

  std::cout << "All tests passed successfully!\n";
  return 0;
}
