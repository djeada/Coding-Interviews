/**
 * This program removes specified characters from a given string.
 * It demonstrates two approaches:
 * 1. Using a hash table to efficiently determine whether a character should be
 * deleted.
 * 2. Comparing strings to ensure the deletion works as expected.
 */

#include <cassert>
#include <cstring>
#include <iostream>

/**
 * Deletes specified characters from a string.
 * @param str: The input string from which characters are to be deleted.
 * @param charsToDelete: The characters to be deleted from the input string.
 */
void deleteCharacters(char *str, const char *charsToDelete) {
  if (!str || !charsToDelete)
    return;

  bool shouldDelete[256] = {false};

  while (*charsToDelete) {
    shouldDelete[*charsToDelete++] = true;
  }

  char *writePtr = str;
  for (char *readPtr = str; *readPtr; ++readPtr) {
    if (!shouldDelete[*readPtr]) {
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
 * Run tests to validate the deleteCharacters function.
 */
void runTests() {
  // Test Case 1
  {
    char str[] = "We are students";
    const char *charsToDelete = "aeiou";
    const char *expectedResult = "W r stdnts";
    deleteCharacters(str, charsToDelete);
    assert(areStringsIdentical(str, expectedResult));
  }

  // Test Case 2
  {
    char str[] = "We are students";
    const char *charsToDelete = "wxyz";
    const char *expectedResult = "We are students";
    deleteCharacters(str, charsToDelete);
    assert(areStringsIdentical(str, expectedResult));
  }

  // Test Case 3
  {
    char str[] = "8613761352066";
    const char *charsToDelete = "1234567890";
    const char *expectedResult = "";
    deleteCharacters(str, charsToDelete);
    assert(areStringsIdentical(str, expectedResult));
  }

  // Test Case 4
  {
    char str[] = "119911";
    const char *charsToDelete = "";
    const char *expectedResult = "119911";
    deleteCharacters(str, charsToDelete);
    assert(areStringsIdentical(str, expectedResult));
  }

  std::cout << "All tests passed!\n";
}

int main() {
  runTests();
  return 0;
}
