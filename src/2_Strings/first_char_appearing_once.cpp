/*
 * FIND FIRST NON-REPEATING CHARACTER
 *
 * Given a string s, return the first non-repeating character in s.
 * A non-repeating character is one that appears exactly once in the string.
 * If no such character exists, return a special value (e.g., '\0').
 *
 * Constraints:
 * - 1 <= s.length <= 10^5
 * - s may consist of lowercase and uppercase letters, digits, spaces, or
 * special characters.
 * - Aim for O(n) time and O(1) or O(σ) extra space,
 *   where σ is the character set size (e.g., 256 for ASCII).
 *
 * Example 1:
 * Input:
 *   s = "ababac"
 * Output:
 *   "c"
 * Explanation:
 *   Characters 'a' and 'b' repeat, so the first non-repeating character is 'c'.
 *
 * Example 2:
 * Input:
 *   s = "aabb"
 * Output:
 *   ""
 * Explanation:
 *   All characters repeat. No non-repeating character exists.
 *
 * Example 3:
 * Input:
 *   s = "leetcode"
 * Output:
 *   "l"
 */

#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

// --- Implementations ---

// Simple (Brute-force) Solution O(n²)
char simpleSolution(const std::string &input) {
  const size_t size = input.size();
  for (size_t i = 0; i < size; ++i) {
    bool repeating = false;
    for (size_t j = 0; j < size; ++j) {
      if (i != j && input[i] == input[j]) {
        repeating = true;
        break;
      }
    }
    if (!repeating) {
      return input[i];
    }
  }
  return '\0';
}

// Optimal (Hash map) Solution O(n)
char optimalSolution(const std::string &input) {
  std::unordered_map<char, int> freq;
  freq.reserve(input.size());
  for (char c : input) {
    ++freq[c];
  }
  for (char c : input) {
    if (freq[c] == 1)
      return c;
  }
  return '\0';
}

// Alternative (Fixed-size array) Solution O(n), O(1) space
char alternativeSolution(const std::string &input) {
  constexpr size_t ASCII = 256;
  std::array<int, ASCII> firstIdx;
  std::array<int, ASCII> count{};
  firstIdx.fill(-1);
  for (size_t i = 0; i < input.size(); ++i) {
    unsigned char c = static_cast<unsigned char>(input[i]);
    if (firstIdx[c] == -1) {
      firstIdx[c] = static_cast<int>(i);
    }
    ++count[c];
  }
  int minPos = std::numeric_limits<int>::max();
  char result = '\0';
  for (size_t c = 0; c < ASCII; ++c) {
    if (count[c] == 1 && firstIdx[c] < minPos) {
      minPos = firstIdx[c];
      result = static_cast<char>(c);
    }
  }
  return result;
}

// --- Testing Infrastructure ---

struct TestCase {
  std::string name;
  std::string input;
  char expected;
};

std::string printableChar(char c) {
  if (c == '\0') {
    return "\\0";
  }
  return std::string(1, c);
}

void testSimple(const std::vector<TestCase> &cases) {
  std::cout << "=== Testing simpleSolution ===\n";
  for (const auto &tc : cases) {
    char got = simpleSolution(tc.input);
    bool pass = (got == tc.expected);
    std::cout << tc.name << ": expected='" << printableChar(tc.expected)
              << "', got='" << printableChar(got) << "' -> "
              << (pass ? "PASS" : "FAIL") << "\n";
    assert(pass);
  }
  std::cout << "\n";
}

void testOptimal(const std::vector<TestCase> &cases) {
  std::cout << "=== Testing optimalSolution ===\n";
  for (const auto &tc : cases) {
    char got = optimalSolution(tc.input);
    bool pass = (got == tc.expected);
    std::cout << tc.name << ": expected='" << printableChar(tc.expected)
              << "', got='" << printableChar(got) << "' -> "
              << (pass ? "PASS" : "FAIL") << "\n";
    assert(pass);
  }
  std::cout << "\n";
}

void testAlternative(const std::vector<TestCase> &cases) {
  std::cout << "=== Testing alternativeSolution ===\n";
  for (const auto &tc : cases) {
    char got = alternativeSolution(tc.input);
    bool pass = (got == tc.expected);
    std::cout << tc.name << ": expected='" << printableChar(tc.expected)
              << "', got='" << printableChar(got) << "' -> "
              << (pass ? "PASS" : "FAIL") << "\n";
    assert(pass);
  }
  std::cout << "\n";
}

int main() {
  std::vector<TestCase> cases = {{"All unique", "abc", 'a'},
                                 {"Repeat at end", "ababac", 'c'},
                                 {"Unique first", "xyza", 'x'},
                                 {"Middle unique", "lol", 'o'},
                                 {"No unique", "aabbcc", '\0'}};

  testSimple(cases);
  testOptimal(cases);
  testAlternative(cases);

  std::cout << "All tests passed successfully!\n";
  return 0;
}
