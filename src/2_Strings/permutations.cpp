/*
 * GENERATING ALL PERMUTATIONS OF A STRING
 *
 * Given an input string, generate all possible permutations of the characters.
 * Permutations are unique arrangements where the order of characters matters.
 *
 * Constraints:
 * - The input string may contain duplicate characters.
 * - Input length is reasonable (typically less than 10 characters) to avoid
 * combinational explosion.
 *
 * Example:
 * Input: "abc"
 * Output: ["abc", "acb", "bac", "bca", "cab", "cba"]
 * Explanation: All unique orders of characters are returned.
 *
 * ASCII illustration for clarity:
 * Input: "ab"
 *
 *      a                b
 *      |                |
 *      b                a
 *     "ab"             "ba"
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <string>
#include <vector>

// --- Implementations ---

// Simple (Brute-force) Solution
void permuteSimple(std::string s, int l, int r,
                   std::set<std::string> &results) {
  if (l == r) {
    results.insert(s);
    return;
  }
  for (int i = l; i <= r; ++i) {
    std::swap(s[l], s[i]);
    permuteSimple(s, l + 1, r, results);
    std::swap(s[l], s[i]);
  }
}

std::vector<std::string> simpleSolution(const std::string &input) {
  if (input.empty())
    return {""};
  std::set<std::string> resultSet;
  permuteSimple(input, 0, (int)input.size() - 1, resultSet);
  return {resultSet.begin(), resultSet.end()};
}

// Optimal Solution (using next_permutation)
std::vector<std::string> optimalSolution(const std::string &input) {
  if (input.empty())
    return {""};
  std::vector<std::string> results;
  std::string s = input;
  std::sort(s.begin(), s.end());
  do {
    results.push_back(s);
  } while (std::next_permutation(s.begin(), s.end()));
  return results;
}

// Alternative (Iterative) Solution
std::vector<std::string> alternativeSolution(const std::string &input) {
  if (input.empty())
    return {""};
  std::vector<std::string> results = {std::string(1, input[0])};
  for (size_t i = 1; i < input.size(); ++i) {
    std::vector<std::string> newPerms;
    for (const auto &str : results) {
      for (size_t pos = 0; pos <= str.size(); ++pos) {
        newPerms.push_back(str.substr(0, pos) + input[i] + str.substr(pos));
      }
    }
    results = std::move(newPerms);
  }
  std::set<std::string> uniqueSet(results.begin(), results.end());
  return {uniqueSet.begin(), uniqueSet.end()};
}

// --- Testing Infrastructure ---

struct TestCase {
  std::string name;
  std::string input;
  std::vector<std::string> expected; // must be sorted
};

void runTest(const std::string &label, const std::vector<TestCase> &cases,
             std::vector<std::string> (*func)(const std::string &)) {
  std::cout << "=== Testing " << label << " ===\n";
  for (const auto &tc : cases) {
    auto got = func(tc.input);
    std::sort(got.begin(), got.end());
    bool pass = (got == tc.expected);
    std::cout << tc.name << ": expected={";
    for (size_t i = 0; i < tc.expected.size(); ++i) {
      std::cout << tc.expected[i] << (i + 1 < tc.expected.size() ? "," : "");
    }
    std::cout << "}, got={";
    for (size_t i = 0; i < got.size(); ++i) {
      std::cout << got[i] << (i + 1 < got.size() ? "," : "");
    }
    std::cout << "} -> " << (pass ? "PASS" : "FAIL") << "\n";
    assert(pass);
  }
  std::cout << "\n";
}

int main() {
  std::vector<TestCase> cases = {
      {"Three distinct chars",
       "abc",
       {"abc", "acb", "bac", "bca", "cab", "cba"}},
      {"With duplicate char", "aab", {"aab", "aba", "baa"}},
      {"Empty string", "", {""}}};

  runTest("simpleSolution", cases, simpleSolution);
  runTest("optimalSolution", cases, optimalSolution);
  runTest("alternativeSolution", cases, alternativeSolution);

  std::cout << "All tests passed successfully!\n";
  return 0;
}
