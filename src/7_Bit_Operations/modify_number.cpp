#include <cassert>

int bitsToModify(int number1, int number2) {
  int temp = number1 ^ number2;

  int bits = 0;
  while (temp != 0) {
    ++bits;
    temp = (temp - 1) & temp;
  }

  return bits;
}

void test1() {
  int number1 = 0;
  int number2 = 13;
  int expected = 3;

  assert(bitsToModify(number1, number2) == expected);
}

void test2() {
  int number1 = 0;
  int number2 = 15;
  int expected = 4;

  assert(bitsToModify(number1, number2) == expected);
}

void test3() {
  int number1 = 7;
  int number2 = 0;
  int expected = 3;

  assert(bitsToModify(number1, number2) == expected);
}

void test4() {
  int number1 = 7;
  int number2 = 7;
  int expected = 0;

  assert(bitsToModify(number1, number2) == expected);
}

int main() {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
