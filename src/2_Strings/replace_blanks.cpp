/**
 * This program replaces all spaces in a C-style string with '%20'.
 * It performs the replacement in-place considering the capacity of the input
 * array.
 */

#include <cassert>
#include <cstring>
#include <iostream>

void replaceSpaces(char str[], int capacity) {
  if (str == nullptr || capacity <= 0) {
    return;
  }

  int originalLength = 0;
  int spaceCount = 0;
  int i = 0;
  while (str[i] != '\0') {
    originalLength++;
    if (str[i] == ' ') {
      spaceCount++;
    }
    i++;
  }

  int newLength = originalLength + spaceCount * 2;
  if (newLength > capacity) {
    return;
  }

  int originalIndex = originalLength;
  int newIndex = newLength;
  while (originalIndex >= 0 && newIndex > originalIndex) {
    if (str[originalIndex] == ' ') {
      str[newIndex--] = '0';
      str[newIndex--] = '2';
      str[newIndex--] = '%';
    } else {
      str[newIndex--] = str[originalIndex];
    }
    originalIndex--;
  }
}

bool areStringsIdentical(const char *strA, const char *strB) {
  return strcmp(strA, strB) == 0;
}

void runTests() {
  char str1[100] = "hello world";
  replaceSpaces(str1, 100);
  assert(areStringsIdentical(str1, "hello%20world"));

  char str2[100] = " helloworld";
  replaceSpaces(str2, 100);
  assert(areStringsIdentical(str2, "%20helloworld"));

  char str3[100] = "helloworld ";
  replaceSpaces(str3, 100);
  assert(areStringsIdentical(str3, "helloworld%20"));

  char str4[100] = "hello  world";
  replaceSpaces(str4, 100);
  assert(areStringsIdentical(str4, "hello%20%20world"));

  std::cout << "All tests passed!\n";
}

int main() {
  runTests();
  return 0;
}
