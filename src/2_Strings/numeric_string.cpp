/**
 * This program checks if a given string can represent a valid number.
 * Valid numbers can be in the form of integers, floating points, or exponential
 * notation.
 */

#include <cassert>
#include <string>

bool containsOnlyDigits(const std::string &str) {
  for (auto c : str) {
    if (!isdigit(c))
      return false;
  }
  return true;
}

bool isValidExponential(const std::string &str) {
  if (str.size() < 2 || (str.front() != 'e' && str.front() != 'E'))
    return false;

  unsigned int i = 2;
  if (str[i] == '+' || str[i] == '-') {
    if (str.size() == 2)
      return false;
    i++;
  }

  return containsOnlyDigits(str.substr(i));
}

bool isValidNumericString(const std::string &str) {
  if (str.empty())
    return false;

  unsigned int i = (str[0] == '+' || str[0] == '-') ? 1 : 0;

  bool numeric = true;

  while (i < str.size() && isdigit(str[i]))
    i++;

  if (i < str.size()) {
    if (str[i] == '.') {
      i++;
      while (i < str.size() && isdigit(str[i]))
        i++;
      if (i < str.size() && (str[i] == 'e' || str[i] == 'E')) {
        numeric = isValidExponential(str.substr(i));
        i = str.size();
      }
    } else if (str[i] == 'e' || str[i] == 'E') {
      numeric = isValidExponential(str.substr(i));
      i = str.size();
    } else {
      numeric = false;
    }
  }

  return numeric && i == str.size();
}

void runTests() {
  assert(isValidNumericString("100"));
  assert(isValidNumericString("123.45e+6"));
  assert(isValidNumericString("+500"));
  assert(isValidNumericString("5e2"));
  assert(isValidNumericString("3.145"));
  assert(isValidNumericString("600."));
  assert(isValidNumericString("-.123"));
  assert(isValidNumericString("1.484278348325E+308"));
  assert(!isValidNumericString("12e"));
  assert(!isValidNumericString("1a3.14"));
  assert(isValidNumericString("+-5"));
  assert(!isValidNumericString("11.2.3"));

  std::cout << "All tests passed!\n";
}

int main() {
  runTests();
  return 0;
}
