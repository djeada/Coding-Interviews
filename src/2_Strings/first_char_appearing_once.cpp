#include <cassert>
#include <limits>
#include <string>
#include <vector>

int insert(int occurrence[], char ch, int index) {
  int i = (int)ch;
  if (occurrence[i] == -1)
    occurrence[i] = index;
  else if (occurrence[i] >= 0)
    occurrence[i] = -2;

  index++;
  return index;
}

char firstAppearingOnce(std::string &str) {
  int index = 0;

  int occurrence[256];

  for (int i = 0; i < 256; ++i)
    occurrence[i] = -1;

  for (auto c : str)
    index = insert(occurrence, c, index);

  char ch = '\0';
  int minIndex = std::numeric_limits<int>::max();
  for (int i = 0; i < 256; ++i) {
    if (occurrence[i] >= 0 && occurrence[i] < minIndex) {
      ch = (char)i;
      minIndex = occurrence[i];
    }
  }

  return ch;
}

void test1() {
  std::string str = "abc";
  char result = 'a';
  assert(firstAppearingOnce(str) == result);
}

void test2() {
  std::string str = "ababac";
  char result = 'c';
  assert(firstAppearingOnce(str) == result);
}

void test3() {
  std::string str = "xyza";
  char result = 'x';
  assert(firstAppearingOnce(str) == result);
}

void test4() {
  std::string str = "lol";
  char result = 'o';

  assert(firstAppearingOnce(str) == result);
}

int main() {
  test1();
  test2();
  test3();
  test4();
  return 0;
}
