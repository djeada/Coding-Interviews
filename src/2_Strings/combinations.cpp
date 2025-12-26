/*
 * GENERATE ALL STRING COMBINATIONS
 *
 * Given a string, generate all possible combinations (subsequences) of its
 * characters. Combinations must include all subsets of characters from length 1
 * to N (the string length). Order of combinations does not matter.
 *
 * Constraints:
 * - The input string will consist of unique lowercase letters.
 * - The length of the string will not exceed 20 characters.
 *
 * Visual illustrations:
 *
 * Example: Input: "abc"
 *
 * Combinations:
 * a, b, c, ab, ac, bc, abc
 *
 * Example Input/Output:
 * Input: "ab"
 * Output: a, b, ab
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <string>
#include <vector>

// Simple (Recursive) Solution
std::set<std::string> simpleSolutionHelper(const std::string &str, int idx,
                                           const std::string &curr) {
  std::set<std::string> result;

  // base case
  if (idx == static_cast<int>(str.size())) {
    if (!curr.empty()) {
      result.insert(curr);
    }
    return result;
  }

  // recursive case
  auto with = simpleSolutionHelper(str, idx + 1, curr + str[idx]);
  auto without = simpleSolutionHelper(str, idx + 1, curr);

  result.merge(with);
  result.merge(without);

  return result;
}

std::set<std::string> simpleSolution(const std::string &str) {
  return simpleSolutionHelper(str, 0, "");
}

// Optimal (Bitmask) Solution
std::set<std::string> optimalSolution(const std::string &str) {
  // abc
  // 001 -> a
  // 010 -> b
  // 011 -> ab
  std::set<std::string> result;
  int n = static_cast<int>(str.size());

  for (int mask = 1; mask < (1 << n); ++mask) {
    std::string comb;

    for (int i = 0; i < n; ++i) {
      if (mask & (1 << i)) {
        comb += str[i];
      }
    }

    result.insert(comb);
  }

  return result;
}

struct TestCase {
  std::string name;
  std::string input;
  std::set<std::string> expected;
};

void testSimple(const std::vector<TestCase> &cases) {
  std::cout << "=== Testing simpleSolution ===\n";
  for (auto &tc : cases) {
    auto got = simpleSolution(tc.input);
    bool pass = (got == tc.expected);
    std::cout << tc.name << " -> " << (pass ? "PASS" : "FAIL") << "\n";
    assert(pass);
  }
  std::cout << "\n";
}

void testOptimal(const std::vector<TestCase> &cases) {
  std::cout << "=== Testing optimalSolution ===\n";
  for (auto &tc : cases) {
    auto got = optimalSolution(tc.input);
    bool pass = (got == tc.expected);
    std::cout << tc.name << " -> " << (pass ? "PASS" : "FAIL") << "\n";
    assert(pass);
  }
  std::cout << "\n";
}

int main() {
  std::vector<TestCase> cases = {
      {"Single char", "a", {"a"}},
      {"Two chars", "ab", {"a", "b", "ab"}},
      {"Three chars", "abc", {"a", "b", "c", "ab", "ac", "bc", "abc"}}};

  testSimple(cases);
  testOptimal(cases);

  std::cout << "All tests passed successfully!\n";
  return 0;
}
