#include <cassert>
#include <string>

void reversed(std::string &s, int l, int r) {
  while (l < r) {
    std::swap(s[l], s[r]);
    l++;
    r--;
  }
}

std::string reverse(std::string str) {
  str.insert(str.end(), ' ');

  int n = str.length();

  int j = 0;

  for (int i = 0; i < n; i++) {
    if (str[i] == ' ') {
      reversed(str, j, i - 1);
      j = i + 1;
    }
  }

  str.pop_back();

  reversed(str, 0, str.length() - 1);

  return str;
}

void test1() {
  std::string str = "hello world";
  std::string wynik = "world hello";

  assert(reverse(str) == wynik);
}

void test2() {
  std::string str = "adam";
  std::string wynik = "adam";

  assert(reverse(str) == wynik);
}

int main() {
  test1();
  test2();
  return 0;
}
