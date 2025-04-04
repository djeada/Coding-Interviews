#include <algorithm>
#include <bitset>
#include <cassert>
#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <vector>

// Forward declaration of the increment function template.
template <size_t N>
bool increment(std::bitset<N>& bits, int length);

void generateCombinations(const std::string &str, int index, int number,
                          std::stack<char> &currentCombination,
                          std::set<std::string> &allCombinations) {
  if (number == 0) {
    // First collect the characters into a vector and then reverse it.
    std::vector<char> vec;
    auto tempStack = currentCombination;
    while (!tempStack.empty()) {
      vec.push_back(tempStack.top());
      tempStack.pop();
    }
    std::reverse(vec.begin(), vec.end());
    std::string combination(vec.begin(), vec.end());
    allCombinations.insert(combination);
    return;
  }

  if (index >= str.size())
    return;

  currentCombination.push(str[index]);
  generateCombinations(str, index + 1, number - 1, currentCombination, allCombinations);
  currentCombination.pop();

  generateCombinations(str, index + 1, number, currentCombination, allCombinations);
}

std::set<std::string> findAllCombinationsRecursive(const std::string &str) {
  std::set<std::string> allCombinations;
  std::stack<char> currentCombination;

  for (int i = 1; i <= str.length(); ++i) {
    generateCombinations(str, 0, i, currentCombination, allCombinations);
  }

  return allCombinations;
}

std::set<std::string> findAllCombinationsBitset(const std::string &str) {
  std::set<std::string> allCombinations;
  std::bitset<100> bits;

  do {
    std::string combination;
    for (int i = 0; i < str.length(); ++i) {
      if (bits[i])
        combination += str[i];
    }
    // Exclude the empty string.
    if (!combination.empty())
      allCombinations.insert(combination);
  } while (increment(bits, str.length()));

  return allCombinations;
}

template <size_t N>
bool increment(std::bitset<N>& bits, int length) {
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
  assert((findAllCombinationsRecursive("a") == std::set<std::string>{"a"}));
  assert((findAllCombinationsBitset("a") == std::set<std::string>{"a"}));

  assert((findAllCombinationsRecursive("ab") ==
          std::set<std::string>{"a", "b", "ab"}));
  assert((findAllCombinationsBitset("ab") ==
          std::set<std::string>{"a", "b", "ab"}));

  assert((findAllCombinationsRecursive("abc") ==
          std::set<std::string>{"a", "b", "c", "ab", "ac", "bc", "abc"}));
  assert((findAllCombinationsBitset("abc") ==
          std::set<std::string>{"a", "b", "c", "ab", "ac", "bc", "abc"}));

  std::cout << "All tests passed!\n";
}

int main() {
  runTests();
  return 0;
}
