#include <cassert>
#include <string>

bool onlyDigits(std::string &str) {
  for (auto c : str) {
    if (!(c >= '0' && c <= '9'))
      return false;
  }

  return true;
}

bool isExponential(std::string &str) {

  if (str.size() < 2)
    return false;

  if (str.front() != 'e' && str.front() != 'E')
    return false;

  unsigned int i = 2;

  if (str[i] == '+' || str[i] == '-') {
    if (str.size() == 2)
      return false;
    i++;
  }

  std::string numeric = str.substr(i, str.size() - 2);

  return onlyDigits(numeric);
}

bool isNumeric(std::string &str) {

  if (str.empty())
    return false;

  unsigned int i = 1;

  if (str[i] == '+' || str[i] == '-') {
    if (str.size() == 1)
      return false;
    i++;
  }

  bool numeric = true;

  while (i < str.size() && str[i] >= '0' && str[i] <= '9')
    i++;

  if (i != str.size()) {
    if (str[i] == '.') {
      i++;

      while (i < str.size() && str[i] >= '0' && str[i] <= '9')
        i++;

      if (i < str.size() && (str[i] == 'e' || str[i] == 'E')) {
        auto rest = str.substr(i, str.size() - i);
        numeric = isExponential(rest);
        i = str.size();
      }
    } else if (str[i] == 'e' || str[i] == 'E') {
      auto rest = str.substr(i, str.size() - i);
      numeric = isExponential(rest);
      i = str.size();
    } else
      numeric = false;
  }

  return numeric && i == str.size();
}

void test1() {
  std::string str = "100";
  assert(isNumeric(str));
}

void test2() {
  std::string str = "123.45e+6";
  assert(isNumeric(str));
}

void test3() {
  std::string str = "+500";
  assert(isNumeric(str));
}

void test4() {
  std::string str = "5e2";
  assert(isNumeric(str));
}

void test5() {
  std::string str = "3.145";
  assert(isNumeric(str));
}

void test6() {
  std::string str = "600.";
  assert(isNumeric(str));
}

void test7() {
  std::string str = "-.123";
  assert(isNumeric(str));
}

void test8() {
  std::string str = "1.484278348325E+308";
  assert(isNumeric(str));
}

void test9() {
  std::string str = "12e";
  assert(!isNumeric(str));
}

void test10() {
  std::string str = "1a3.14";
  assert(!isNumeric(str));
}

void test11() {
  std::string str = "+-5";
  assert(isNumeric(str));
}

void test12() {
  std::string str = "11.2.3";
  assert(!isNumeric(str));
}

int main() {

  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  test8();
  test9();
  test10();
  test11();
  test12();

  return 0;
}
