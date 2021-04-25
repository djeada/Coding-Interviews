#include <cassert>
#include <string>

bool isPalindrome1(int x) {
  auto str = std::to_string(x);
  for (unsigned int i = 0; i < str.size() / 2; i++) {
    if (str[i] != str[str.size() - i - 1])
      return false;
  }
  return true;
}

bool isPalindrome2(int x) {
  int reversed = 0;
  int copy = x;
  while (x != 0) {
    reversed = reversed * 10 + x % 10;
    x /= 10;
  }

  return reversed == copy;
}

void test1() {
  int number = 121;
  assert(isPalindrome1(number));
  assert(isPalindrome2(number));
}

void test2() {
  int number = 3356;
  assert(!isPalindrome1(number));
  assert(!isPalindrome2(number));
}

void test3() {
  int number = 55855;
  assert(isPalindrome1(number));
  assert(isPalindrome2(number));
}

void test4() {
  int number = 12811;
  assert(!isPalindrome1(number));
  assert(!isPalindrome2(number));
}

int main() {

  test1();
  test2();
  test3();
  test4();

  return 0;
}
