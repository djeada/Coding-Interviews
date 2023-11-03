/**
 * This program removes duplicate characters from a given string.
 * It demonstrates the use of a hash table to efficiently track characters
 * and two pointers technique to construct the string without duplicates.
 */

#include <cassert>
#include <cstring>
#include <iostream>

/**
 * Removes duplicate characters from a string.
 * @param str: The input string from which duplicate characters are to be
 * removed.
 */
void removeDuplicates(char *str) {
  if (!str)
    return;

  bool isCharPresent[256] = {false};
  char *writePtr = str;

  for (char *readPtr = str; *readPtr; ++readPtr) {
    if (!isCharPresent[*readPtr]) {
      isCharPresent[*readPtr] = true;
      *writePtr++ = *readPtr;
    }
  }

  *writePtr = '\0';
}

/**
 * Compares two strings for equality.
 * @param strA: First string to be compared.
 * @param strB: Second string to be compared.
 * @return: True if the strings are identical, False otherwise.
 */
bool areStringsIdentical(const char *strA, const char *strB) {
  return strcmp(strA, strB) == 0;
}

/**
 * Run tests to validate the removeDuplicates function.
 */
void runTests() {
  // Test Case 1
  {
    char str[] = "google";
    const char *expectedResult = "gole";
    removeDuplicates(str);
    assert(areStringsIdentical(str, expectedResult));
  }

  // Test Case 2
  {
    char str[] = "aaaaaaaaaaaaaaaaaaaaa";
    const char *expectedResult = "a";
    removeDuplicates(str);
    assert(areStringsIdentical(str, expectedResult));
  }

  // Test Case 3
  {
    char str[] = "";
    const char *expectedResult = "";
    removeDuplicates(str);
    assert(areStringsIdentical(str, expectedResult));
  }

  // Test Case 4
  {
    char str[] = "abcacbbacbcacabcba";
    const char *expectedResult = "abc";
    removeDuplicates(str);
    assert(areStringsIdentical(str, expectedResult));
  }

  std::cout << "All tests passed!\n";
}

int main() {
  runTests();
  return 0;
}
