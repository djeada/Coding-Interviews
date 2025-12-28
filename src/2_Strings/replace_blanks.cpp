/*
 * REPLACE SPACES IN A STRING
 *
 * Given a string s, replace every space character ' ' with the sequence "%20".
 * Return the resulting string.
 *
 * Constraints:
 * - 0 <= s.length <= 10^5
 * - s may consist of letters, digits, spaces, or special characters.
 * - Aim for O(n) time complexity.
 * - In-place modification is encouraged when possible (assume sufficient buffer
 * capacity).
 *
 * ASCII Illustration:
 *
 *        "hello world"
 *              |
 *    replace ' ' with "%20"
 *              |
 *       "hello%20world"
 *
 * Example 1:
 * Input:
 *   s = "hello world"
 * Output:
 *   "hello%20world"
 *
 * Example 2:
 * Input:
 *   s = "Mr John Smith"
 * Output:
 *   "Mr%20John%20Smith"
 *
 * Example 3:
 * Input:
 *   s = "nospace"
 * Output:
 *   "nospace"
 */
#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

// --- Implementations ---

// Simple (Brute-force) Solution using std::string
std::string simpleSolution(const std::string &input) {
  std::string result;
  result.reserve(input.size());
  for (char c : input) {
    if (c == ' ') {
      result += "%20";
    } else {
      result.push_back(c);
    }
  }
  return result;
}

// Alternative Solution using in-place replace on std::string
std::string alternativeSolution(const std::string &input) {
  std::string result = input;
  for (size_t pos = 0; (pos = result.find(' ', pos)) != std::string::npos;) {
    result.replace(pos, 1, "%20");
    pos += 3;
  }
  return result;
}

// Optimal (In-place) Solution on C-string buffer
void optimalSolution(char str[], size_t capacity) {
  if (!str || capacity == 0)
    return;
  const size_t origLen = std::strlen(str);
  size_t spaces = 0;
  for (size_t i = 0; i < origLen; ++i) {
    if (str[i] == ' ')
      spaces++;
  }
  const size_t newLen = origLen + spaces * 2;
  if (newLen >= capacity)
    return;
  str[newLen] = '\0';
  size_t i = origLen;
  size_t j = newLen;
  while (i > 0) {
    --i;
    if (str[i] == ' ') {
      str[--j] = '0';
      str[--j] = '2';
      str[--j] = '%';
    } else {
      str[--j] = str[i];
    }
  }
}

// --- Testing Infrastructure ---

struct StrTestCase {
  std::string name, input, expected;
};

struct CStrTestCase {
  std::string name;
  const char *initial;
  std::string expected;
};

template <typename Func>
void runStringTests(const std::string &label,
                    const std::vector<StrTestCase> &cases, Func func) {
  std::cout << "=== Testing " << label << " ===\n";
  for (auto &tc : cases) {
    std::string got = func(tc.input);
    bool pass = (got == tc.expected);
    std::cout << tc.name << ": " << label << "(\"" << tc.input << "\")=\""
              << got << "\" expected=\"" << tc.expected << "\" -> "
              << (pass ? "PASS" : "FAIL") << "\n";
    assert(pass);
  }
  std::cout << "\n";
}

void testOptimal(const std::vector<CStrTestCase> &cases) {
  std::cout << "=== Testing optimalSolution (in-place) ===\n";
  for (auto &tc : cases) {
    char buffer[100];
    std::strncpy(buffer, tc.initial, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    optimalSolution(buffer, sizeof(buffer));
    const std::string got(buffer);
    bool pass = (got == tc.expected);
    std::cout << tc.name << ": got=\"" << got << "\" expected=\"" << tc.expected
              << "\" -> " << (pass ? "PASS" : "FAIL") << "\n";
    assert(pass);
  }
  std::cout << "\n";
}

int main() {
  std::vector<StrTestCase> stringCases = {
      {"Single space", "hello world", "hello%20world"},
      {"Leading/trailing", "  lead and trail  ",
       "%20%20lead%20and%20trail%20%20"},
      {"No spaces", "nospace", "nospace"},
      {"All spaces", "   ", "%20%20%20"}};

  std::vector<CStrTestCase> cstrCases = {
      {"In-place single", "hello world", "hello%20world"},
      {"In-place leading", "  hello  ", "%20%20hello%20%20"},
      {"In-place no spaces", "nospace", "nospace"},
      {"In-place all spaces", "   ", "%20%20%20"}};

  runStringTests("simpleSolution", stringCases, simpleSolution);
  runStringTests("alternativeSolution", stringCases, alternativeSolution);
  testOptimal(cstrCases);

  std::cout << "All tests passed successfully!\n";
  return 0;
}
