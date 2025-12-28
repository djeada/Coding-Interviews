/*
 * REVERSE WORDS IN A STRING
 *
 * Given a string s, reverse the order of the words.
 * A word is defined as a sequence of non-space characters.
 * The words in s will be separated by a single space with no leading or
 * trailing spaces.
 *
 * Return the resulting string after reversing the order of words.
 *
 * Constraints:
 * - 1 <= s.length <= 10^5
 * - s consists of printable ASCII characters.
 * - Words are separated by a single space.
 * - The goal is O(n) time complexity with minimal extra space.
 *
 * ASCII Illustration:
 *
 *     Input:  "hello world"
 *             +------------+
 *             |hello world |
 *             +------------+
 *                   |
 *         (reverse word order)
 *                   V
 *             +------------+
 *             |world hello |
 *             +------------+
 *
 * Example 1:
 * Input:
 *   s = "hello world"
 * Output:
 *   "world hello"
 *
 * Example 2:
 * Input:
 *   s = "the sky is blue"
 * Output:
 *   "blue is sky the"
 *
 * Example 3:
 * Input:
 *   s = "a b c"
 * Output:
 *   "c b a"
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Simple (Brute-force) Solution using string splitting.
std::string simpleSolution(const std::string &input) {
  std::istringstream iss(input);
  std::vector<std::string> words;
  words.reserve(input.size() / 2 + 1);
  std::string word;
  while (iss >> word) {
    words.push_back(word);
  }
  std::reverse(words.begin(), words.end());
  std::string result;
  for (size_t i = 0; i < words.size(); ++i) {
    if (i > 0)
      result.push_back(' ');
    result += words[i];
  }
  return result;
}

// Optimal (Efficient) Solution: In-place reversal via two-step reverse.
void reverseSubstring(std::string &str, size_t left, size_t right) {
  while (left < right) {
    std::swap(str[left++], str[right--]);
  }
}

std::string normalizeSpaces(const std::string &input) {
  std::string s;
  s.reserve(input.size());
  size_t i = 0;
  while (i < input.size() && input[i] == ' ')
    ++i;
  for (; i < input.size(); ++i) {
    if (input[i] == ' ' && (s.empty() || s.back() == ' '))
      continue;
    s.push_back(input[i]);
  }
  if (!s.empty() && s.back() == ' ')
    s.pop_back();
  return s;
}

std::string optimalSolution(const std::string &input) {
  // First, normalize spaces
  std::string str = normalizeSpaces(input);
  const size_t n = str.size();
  size_t start = 0;

  // Reverse each word in-place
  for (size_t i = 0; i <= n; ++i) {
    if (i == n || str[i] == ' ') {
      if (i > start)
        reverseSubstring(str, start, i - 1);
      start = i + 1;
    }
  }
  // Reverse the whole string
  if (!str.empty())
    reverseSubstring(str, 0, n - 1);
  return str;
}

// Alternative Solution using string splitting and reverse join.
std::string alternativeSolution(const std::string &input) {
  std::istringstream iss(input);
  std::vector<std::string> words;
  std::string word;
  while (iss >> word) {
    words.push_back(word);
  }
  std::string result;
  for (size_t i = words.size(); i > 0; --i) {
    if (i < words.size())
      result.push_back(' ');
    result += words[i - 1];
  }
  return result;
}

// --- Test case struct ---
struct TestCase {
  std::string name;
  std::string input;
  std::string expected;
};

// --- Test runners ---
template <typename Func>
void runTests(const std::string &label, const std::vector<TestCase> &cases,
              Func func) {
  std::cout << "=== Testing " << label << " ===\n";
  for (auto &tc : cases) {
    std::string got = func(tc.input);
    bool pass = (got == tc.expected);
    std::cout << tc.name << ": expected=\"" << tc.expected << "\", got=\""
              << got << "\" -> " << (pass ? "PASS" : "FAIL") << "\n";
    assert(pass);
  }
  std::cout << "\n";
}

int main() {
  std::vector<TestCase> cases = {
      {"Two words", "hello world", "world hello"},
      {"Single word", "adam", "adam"},
      {"Multiple words", "the quick brown fox", "fox brown quick the"},
      {"C++ phrase", "C++ is modern", "modern is C++"},
      {"Leading/trailing spaces", "  trim this  ", "this trim"},
      {"Repeated spaces", "a  lot   of    spaces", "spaces of lot a"}};

  runTests("simpleSolution", cases, simpleSolution);
  runTests("optimalSolution", cases, optimalSolution);
  runTests("alternativeSolution", cases, alternativeSolution);

  std::cout << "All tests passed successfully!\n";
  return 0;
}
