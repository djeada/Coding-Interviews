/**
 * VALIDATE NUMERIC STRING
 *
 * Determine whether a given ASCII string represents a valid number.
 * Supported forms include integers, decimals, and scientific notation.
 *
 * Accepted Grammar (informal):
 *   number := [sign] integer [fraction] [exponent]
 *           | [sign]        fraction   [exponent]
 *   sign   := '+' | '-'
 *   integer:= DIGIT{1,}
 *   fraction:= '.' DIGIT{0,} | DIGIT{1,} '.' DIGIT{0,}
 *   exponent:= ('e'|'E') [sign] DIGIT{1,}
 *
 * Notes & Assumptions:
 * - Leading/trailing spaces are NOT allowed.
 * - Only ASCII digits '0'–'9' are recognized.
 * - A standalone sign ('+' or '-') is invalid.
 * - A trailing dot is allowed if the integer part exists (e.g., "600.").
 * - A leading dot is allowed if followed by digits (e.g., "-.123").
 * - Exponent must be an integer with optional sign and at least one digit.
 *
 * Examples (Valid):
 *   "100"
 *   "+500"
 *   "3.145"
 *   "600."
 *   "-.123"
 *   "5e2"
 *   "123.45e+6"
 *   "1.484278348325E+308"
 *
 * Examples (Invalid):
 *   ""              (empty)
 *   "12e"           (missing exponent digits)
 *   "1a3.14"        (invalid character)
 *   "+-5"           (misplaced signs)
 *   "11.2.3"        (multiple dots)
 *
 * Complexity:
 * - Time: O(n), single left-to-right scan.
 * - Space: O(1) auxiliary.
 */

#include <cassert>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

// --- Implementation ---

bool isValidNumericString(const std::string &str) {
  if (str.empty()) {
    return false;
  }
  size_t i = 0;
  if (str.front() == '+' || str.front() == '-') {
    ++i;
  }
  bool seenDigit = false;
  bool seenExp = false;
  bool seenDot = false;

  for (; i < str.size(); i++) {
    unsigned char c = static_cast<unsigned char>(str.at(i));
    if (std::isdigit(c)) {
      seenDigit = true;
      continue;
    }
    if (c == '.') {
      if (seenDot || seenExp) {
        return false;
      }
      seenDot = true;
      continue;
    }
    if (c == 'e' || c == 'E') {
      if (seenExp || !seenDigit) {
        return false;
      }
      seenExp = true;
      seenDigit = false;
      if (i + 1 < str.size() &&
          (str.at(i + 1) == '+' || str.at(i + 1) == '-')) {
        ++i;
      }
      continue;
    }
    return false;
  }
  return seenDigit;
}

// --- Testing Infrastructure ---

struct TestCase {
  std::string name;
  std::string input;
  bool expected;
};

void runTests(const std::vector<TestCase> &cases) {
  std::cout << "=== Testing isValidNumericString ===\n";
  for (const auto &tc : cases) {
    bool got = isValidNumericString(tc.input);
    bool pass = (got == tc.expected);
    std::cout << tc.name << ": input=\"" << tc.input << "\""
              << ", expected=" << (tc.expected ? "true" : "false")
              << ", got=" << (got ? "true" : "false") << " -> "
              << (pass ? "PASS" : "FAIL") << "\n";
    assert(pass);
  }
  std::cout << "\nAll tests passed successfully!\n";
}

int main() {
  std::vector<TestCase> cases = {
      {"Integer only", "100", true},
      {"Decimal with exp+", "123.45e+6", true},
      {"Leading plus", "+500", true},
      {"Exp shorthand", "5e2", true},
      {"Simple fraction", "3.145", true},
      {"Trailing dot", "600.", true},
      {"Leading dot", "-.123", true},
      {"Large exponent", "1.484278348325E+308", true},
      {"Missing exp digits", "12e", false},
      {"Invalid char", "1a3.14", false},
      {"Bad sign placement", "+-5", false},
      {"Multiple dots", "11.2.3", false},
      {"Empty string", "", false}};

  runTests(cases);
  return 0;
}
