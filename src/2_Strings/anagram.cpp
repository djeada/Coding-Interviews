/**
 * This program checks if two strings are anagrams of each other.
 * An anagram is a word or phrase formed by rearranging the letters of a
 * different word or phrase, typically using all the original letters exactly
 * once. For instance, "silent" and "listen" are anagrams.
 */

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>

/**
 * Check if the given character exists as a key in the provided histogram.
 * @param histogram: An unordered_map containing characters as keys and their
 * frequencies as values.
 * @param key: The character to be checked.
 * @return: True if the key is present, otherwise False.
 */
bool containsKey(const std::unordered_map<char, int> &histogram, char key) {
  return histogram.find(key) != histogram.end();
}

/**
 * Check if two strings are anagrams of each other.
 * @param str1: The first string.
 * @param str2: The second string.
 * @return: True if the strings are anagrams, otherwise False.
 */
bool areAnagrams(const std::string &str1, const std::string &str2) {
  if (str1.size() != str2.size())
    return false;

  std::unordered_map<char, int> charFrequency;
  for (const auto &ch : str1) {
    if (containsKey(charFrequency, ch))
      charFrequency[ch]++;
    else
      charFrequency[ch] = 1;
  }

  for (const auto &ch : str2) {
    if (!containsKey(charFrequency, ch))
      return false;

    charFrequency[ch]--;
    if (charFrequency[ch] == 0)
      charFrequency.erase(ch);
  }

  return charFrequency.empty();
}

void testAnagrams() {
  assert(areAnagrams("silent", "listen"));
  assert(areAnagrams("evil", "live"));
  assert(areAnagrams("eleven plus two", "twelve plus one"));
  assert(!areAnagrams("there", "their"));
  std::cout << "All tests passed!\n";
}

int main() {
  testAnagrams();
  return 0;
}
