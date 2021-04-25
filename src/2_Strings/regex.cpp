#include <cassert>
#include <string>

bool match(std::string str, std::string pattern) {
  if (str.empty() && pattern.empty())
    return true;

  if (!str.empty() && pattern.empty())
    return false;

  if (pattern.size() > 1 && pattern[1] == '*') {
    if (pattern == str || (pattern.front() == '.' && !str.empty()))
      return match(str.substr(1), pattern.substr(2)) ||
             match(str.substr(1), pattern) || match(str, pattern.substr(2));
    else
      return match(str, pattern.substr(2));
  }

  if (str == pattern || (pattern.front() == '.' && !str.empty()))
    return match(str.substr(1), pattern.substr(1));

  return false;
}

void test1() {
  std::string str = "";
  std::string pattern = "";
  assert(match(str, pattern));
}

void test2() {
  std::string str = "bbbba";
  std::string pattern = ".*a*a";
  assert(match(str, pattern));
}
void test3() {
  std::string str = "aaa";
  std::string pattern = ".*";
  assert(match(str, pattern));
}

void test4() {
  std::string str = "";
  std::string pattern = ".*";
  assert(match(str, pattern));
}

void test5() {
  std::string str = "aaa";
  std::string pattern = ".*a";
  assert(match(str, pattern));
}

void test6() {
  std::string str = "aaa";
  std::string pattern = "";
  assert(!match(str, pattern));
}

void test7() {
  std::string str = "aaa";
  std::string pattern = ".a";
  assert(!match(str, pattern));
}

void test8() {
  std::string str = "a";
  std::string pattern = "ab*a";
  assert(!match(str, pattern));
}

void test9() {
  std::string str = "aaa";
  std::string pattern = "ab*a";
  assert(!match(str, pattern));
}

void test10() {
  std::string str = "aaba";
  std::string pattern = "ab*a*c*a";
  assert(!match(str, pattern));
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

  return 0;
}
