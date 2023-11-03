/**
 * This program generates all combinations of a given string and tests if the
 * generated combinations are correct. It uses two approaches: a recursive
 * backtracking method and a bit manipulation method.
 */

#include <bitset>
#include <cassert>
#include <iostream>
#include <set>
#include <stack>
#include <string>

/**
 * Recursive function to generate all combinations of a given string.
 * @param str: The input string.
 * @param index: The current index being processed.
 * @param number: The number of characters to select.
 * @param currentCombination: A stack containing the current combination being
 * processed.
 * @param allCombinations: A set to store all unique combinations.
 */
void generateCombinations(const std::string &str, int index, int number,
                          std::stack<char> &currentCombination,
                          std::set<std::string> &allCombinations) {

  if (number == 0) {
    std::string combination;
    auto tempStack = currentCombination;
    while (!tempStack.empty()) {
      combination.push_back(tempStack.top());
      tempStack.pop();
    }
    allCombinations.insert(combination);
    return;
  }

  if (index >= str.size())
    return;

  currentCombination.push(str[index]);
  generateCombinations(str, index + 1, number - 1, currentCombination,
                       allCombinations);
  currentCombination.pop();

  generateCombinations(str, index + 1, number, currentCombination,
                       allCombinations);
}

/**
 * Wrapper function for the recursive generation of combinations using
 * backtracking.
 * @param str: The input string.
 * @return: A set containing all unique combinations.
 */
std::set<std::string> findAllCombinationsRecursive(const std::string &str) {
  std::set<std::string> allCombinations;
  std::stack<char> currentCombination;

  for (int i = 1; i <= str.length(); ++i) {
    generateCombinations(str, 0, i, currentCombination, allCombinations);
  }

  return allCombinations;
}

/**
 * Generate all combinations of a given string using bit manipulation.
 * @param str: The input string.
 * @return: A set containing all unique combinations.
 */
std::set<std::string> findAllCombinationsBitset(const std::string &str) {
  std::set<std::string> allCombinations;
  std::bitset<100> bits;

  do {
    std::string combination;
    for (int i = 0; i < str.length(); ++i) {
      if (bits[i])
        combination += str[i];
    }
    allCombinations.insert(combination);
  } while (increment(bits, str.length()));

  return allCombinations;
}

/**
 * Increment the bitset as if it were a binary number.
 * @param bits: The bitset representing the binary number.
 * @param length: The length of the string being processed.
 * @return: False if the bitset has reached its maximum value, otherwise True.
 */
template <size_t N> bool increment(std::bitset<N> &bits, int length) {
  int index = length - 1;

  while (index >= 0 && bits[index]) {
    bits.reset(index);
    --index;
  }

  if (index < 0)
    return false;

  bits.set(index);
  return true;
}

void runTests() {
  assert(findAllCombinationsRecursive("a") == std::set<std::string>{"a"});
  assert(findAllCombinationsBitset("a") == std::set<std::string>{"a"});

  assert(findAllCombinationsRecursive("ab") ==
         std::set<std::string>{"a", "b", "ab"});
  assert(findAllCombinationsBitset("ab") ==
         std::set<std::string>{"a", "b", "ab"});

  assert(findAllCombinationsRecursive("abc") ==
         std::set<std::string>{"a", "b", "c", "ab", "ac", "bc", "abc"});
  assert(findAllCombinationsBitset("abc") ==
         std::set<std::string>{"a", "b", "c", "ab", "ac", "bc", "abc"});

  std::cout << "All tests passed!\n";
}

int main() {
  runTests();
  return 0;
}
