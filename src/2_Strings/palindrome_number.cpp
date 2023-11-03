/**
 * This program checks if a given integer is a palindrome.
 * It provides two approaches to solve the problem:
 * 1. By converting the integer to a string.
 * 2. By reversing the integer without converting it to a string.
 */

#include <cassert>
#include <iostream>
#include <string>

bool isPalindromeUsingString(int x) {
  auto str = std::to_string(x);
  auto strSize = str.size();
  for (unsigned int i = 0; i < strSize / 2; i++) {
    if (str[i] != str[strSize - i - 1])
      return false;
  }
  return true;
}

bool isPalindromeUsingMath(int x) {
  if (x < 0)
    return false;

  int reversed = 0;
  int original = x;
  while (x != 0) {
    reversed = reversed * 10 + x % 10;
    x /= 10;
  }

  return reversed == original;
}

void runTests() {
  assert(isPalindromeUsingString(121) && isPalindromeUsingMath(121));
  assert(!isPalindromeUsingString(3356) && !isPalindromeUsingMath(3356));
  assert(isPalindromeUsingString(55855) && isPalindromeUsingMath(55855));
  assert(!isPalindromeUsingString(12811) && !isPalindromeUsingMath(12811));

  std::cout << "All tests passed!\n";
}

int main() {
  runTests();
  return 0;
}
