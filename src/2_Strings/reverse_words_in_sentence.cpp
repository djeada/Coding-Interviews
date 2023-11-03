/**
 * This program changes the order of words in a given string.
 */

#include <cassert>
#include <iostream>
#include <string>

void reverseSubstring(std::string &str, int left, int right) {
  while (left < right) {
    std::swap(str[left], str[right]);
    left++;
    right--;
  }
}

std::string reverseWords(const std::string &input) {
  std::string str = input + ' ';

  int startIndex = 0;
  for (int i = 0; i < str.length(); i++) {
    if (str[i] == ' ') {
      reverseSubstring(str, startIndex, i - 1);
      startIndex = i + 1;
    }
  }

  str.pop_back();
  reverseSubstring(str, 0, str.length() - 1);

  return str;
}

void runTests() {
  assert(reverseWords("hello world") == "world hello");
  assert(reverseWords("adam") == "adam");

  std::cout << "All tests passed!\n";
}

int main() {
  runTests();
  return 0;
}
