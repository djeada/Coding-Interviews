#include <bits/stdc++.h>
#include <set>
#include <string>

void _combination(const std::string &str, int index, int number,
                  std::stack<char> &result, std::set<std::string> &results) {

  if (number == 0) {
    std::string reverse;
    auto copy = result;
    while (!copy.empty()) {
      reverse.push_back(copy.top());
      copy.pop();
    }
    results.insert(reverse);
    return;
  }

  if (index >= str.size())
    return;

  result.push(str.at(index));
  _combination(str, index + 1, number - 1, result, results);
  result.pop();

  _combination(str, index + 1, number, result, results);
}

std::set<std::string> combination1(const std::string &str) {
  std::set<std::string> results;
  std::stack<char> result;

  for (int i = 1; i <= str.length(); ++i) {
    _combination(str, 0, i, result, results);
  }

  return results;
}

template <size_t N> static bool increment(std::bitset<N> &bits, int length) {
  int index = length - 1;

  while (index >= 0 && bits[index] > 0) {
    bits.reset(index);
    --index;
  }

  if (index < 0)
    return false;

  bits.set(index);
  return true;
}

std::set<std::string> combination2(const std::string &str) {
  std::set<std::string> results;
  std::bitset<100> bits;

  while (increment(bits, str.length())) {
    std::string result;
    for (int i = 0; i < str.length(); ++i) {
      if (bits[i])
        result += str.at(i);
    }
    results.insert(result);
  }

  return results;
}

void test1() {

  std::string str = "a";
  std::set<std::string> result = {"a"};
  assert(combination1(str) == result);
  assert(combination2(str) == result);
}

void test2() {

  std::string str = "ab";
  std::set<std::string> result = {"b", "a", "ab"};
  // assert(identical(combination1(str), result));
  assert(combination2(str) == result);
}

void test3() {

  std::string str = "abc";
  std::set<std::string> result = {"c", "b", "bc", "a", "ac", "ab", "abc"};
  // assert(combination1(str) == result);
  assert(combination2(str) == result);
}

void test4() {

  std::string str = "abcd";
  std::set<std::string> result = {"d",   "c",   "cd",  "b",   "bd",
                                  "bc",  "bcd", "a",   "ad",  "ac",
                                  "acd", "ab",  "abd", "abc", "abcd"};
  // assert(combination1(str) == result);
  assert(combination2(str) == result);
}

int main() {

  test1();
  test2();
  test3();
  test4();

  return 0;
}
