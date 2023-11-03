/**
 * This program checks whether a given string matches a given pattern.
 * The pattern may contain two special characters:
 *   - '.' (period) which matches any single character.
 *   - '*' (asterisk) which matches zero or more of the preceding element.
 */

#include <cassert>
#include <string>

bool isMatch(const std::string &str, const std::string &pattern) {
  if (str.empty() && pattern.empty()) {
    return true;
  }

  if (!str.empty() && pattern.empty()) {
    return false;
  }

  if (pattern.size() > 1 && pattern[1] == '*') {
    if (str == pattern || (!str.empty() && (pattern.front() == '.' ||
                                            pattern.front() == str.front()))) {
      return isMatch(str.substr(1), pattern.substr(2)) ||
             isMatch(str.substr(1), pattern) || isMatch(str, pattern.substr(2));
    } else {
      return isMatch(str, pattern.substr(2));
    }
  }

  if (str == pattern || (!str.empty() && (pattern.front() == '.' ||
                                          pattern.front() == str.front()))) {
    return isMatch(str.substr(1), pattern.substr(1));
  }

  return false;
}

void runTests() {
  assert(isMatch("", ""));
  assert(isMatch("bbbba", ".*a*a"));
  assert(isMatch("aaa", ".*"));
  assert(isMatch("", ".*"));
  assert(isMatch("aaa", ".*a"));
  assert(!isMatch("aaa", ""));
  assert(!isMatch("aaa", ".a"));
  assert(!isMatch("a", "ab*a"));
  assert(!isMatch("aaa", "ab*a"));
  assert(!isMatch("aaba", "ab*a*c*a"));

  std::cout << "All tests passed!\n";
}

int main() {
  runTests();
  return 0;
}
