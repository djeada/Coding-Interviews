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
#include <string>
#include <vector>

// --- Implementations ---

// Simple (Backtracking) Solution
void permuteSimple(std::string &s, size_t idx,
                   std::vector<std::string> &results) {
  if (idx == s.size()) {
    results.push_back(s);
    return;
  }
  bool used[256] = {false};
  for (size_t i = idx; i < s.size(); ++i) {
    unsigned char key = static_cast<unsigned char>(s[i]);
    if (used[key])
      continue;
    used[key] = true;
    std::swap(s[idx], s[i]);
    permuteSimple(s, idx + 1, results);
    std::swap(s[idx], s[i]);
  }
}

std::vector<std::string> simpleSolution(const std::string &input) {
  if (input.empty())
    return {""};
  std::string s = input;
  std::sort(s.begin(), s.end());
  std::vector<std::string> results;
  results.reserve(128);
  permuteSimple(s, 0, results);
  return results;
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
  std::vector<std::string> results{""};

  for (char ch : input) {
    std::vector<std::string> next;
    next.reserve(results.size() * (results.front().size() + 1));

    for (const auto &s : results) {
      for (std::size_t pos = 0; pos <= s.size(); ++pos) {
        auto t = s; // copy once
        t.insert(t.begin() + pos, ch);
        next.push_back(std::move(t));
      }
    }
    results = std::move(next);
  }

  std::sort(results.begin(), results.end());
  results.erase(std::unique(results.begin(), results.end()), results.end());
  return results;
}

// --- Testing Infrastructure ---

struct TestCase {
  std::string name;
  std::string input;
  std::vector<std::string> expected; // must be sorted
};

template <typename Func>
void runTest(const std::string &label, const std::vector<TestCase> &cases,
             Func func) {
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
