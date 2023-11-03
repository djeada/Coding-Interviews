/**
 * This program finds the first non-repeating character in a given string.
 * If a character appears only once in the string, it is considered
 * non-repeating. The program checks for the first occurrence of such
 * characters.
 */

#include <cassert>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

/**
 * Inserts a character into the occurrence array and updates its index.
 * @param occurrence: An array tracking the occurrence of each character.
 * @param ch: The character to be inserted.
 * @param index: The current index in the string.
 * @return: The incremented index.
 */
int insertCharacter(int occurrence[], char ch, int index) {
  int ascii_value = static_cast<int>(ch);
  if (occurrence[ascii_value] == -1) {
    occurrence[ascii_value] = index;
  } else if (occurrence[ascii_value] >= 0) {
    occurrence[ascii_value] = -2;
  }
  return ++index;
}

/**
 * Finds the first non-repeating character in a string.
 * @param str: The input string.
 * @return: The first non-repeating character.
 */
char findFirstNonRepeatingCharacter(const std::string &str) {
  int index = 0;
  int occurrence[256];
  std::fill(std::begin(occurrence), std::end(occurrence), -1);

  for (auto c : str) {
    index = insertCharacter(occurrence, c, index);
  }

  char ch = '\0';
  int minIndex = std::numeric_limits<int>::max();
  for (int i = 0; i < 256; ++i) {
    if (occurrence[i] >= 0 && occurrence[i] < minIndex) {
      ch = static_cast<char>(i);
      minIndex = occurrence[i];
    }
  }

  return ch;
}

/**
 * Run tests to validate the findFirstNonRepeatingCharacter function.
 */
void runTests() {
  // Test Case 1
  assert(findFirstNonRepeatingCharacter("abc") == 'a');

  // Test Case 2
  assert(findFirstNonRepeatingCharacter("ababac") == 'c');

  // Test Case 3
  assert(findFirstNonRepeatingCharacter("xyza") == 'x');

  // Test Case 4
  assert(findFirstNonRepeatingCharacter("lol") == 'o');

  std::cout << "All tests passed!\n";
}

int main() {
  runTests();
  return 0;
}
