#include <cassert>

int countOnes1(int n) {
  int count = 0;
  unsigned int flag = 1;
  while (flag) {
    if (n & flag)
      count++;

    flag = flag << 1;
  }

  return count;
}

int countOnes2(int n) {
  int count = 0;

  while (n) {
    ++count;
    n = (n - 1) & n;
  }

  return count;
}

void test1() {
  int x = 0;
  int result = 0;
  assert(countOnes1(x) == result);
  assert(countOnes2(x) == result);
}

void test2() {
  int x = 1;
  int result = 1;
  assert(countOnes1(x) == result);
  assert(countOnes2(x) == result);
}

void test3() {
  int x = 10;
  int result = 2;
  assert(countOnes1(x) == result);
  assert(countOnes2(x) == result);
}

void test4() {
  int x = 0x7FFFFFFF;
  int result = 31;
  assert(countOnes1(x) == result);
  assert(countOnes2(x) == result);
}

int main(int argc, char *argv[]) {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
