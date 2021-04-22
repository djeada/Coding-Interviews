#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

typedef struct node {
  int num1;
  int num2;
} NumbersOccurringOnce;

bool isBit1(int num, int indexBit);
int findFirstBitIs1(int num);

void getOnce(vector<int> numbers, NumbersOccurringOnce &once) {
  once.num1 = 0;
  once.num2 = 0;
  if (numbers.size() < 2)
    return;

  int resultExclusiveOR = 0;
  for (int i = 0; i < numbers.size(); ++i)
    resultExclusiveOR ^= numbers[i];

  int indexOf1 = findFirstBitIs1(resultExclusiveOR);

  for (int j = 0; j < numbers.size(); ++j) {
    if (isBit1(numbers[j], indexOf1))
      once.num1 ^= numbers[j];
    else
      once.num2 ^= numbers[j];
  }
}

// The first 1 bit from the rightmost
int findFirstBitIs1(int num) {
  int indexBit = 0;
  while (((num & 1) == 0) && (indexBit < 32)) {
    num = num >> 1;
    ++indexBit;
  }
  return indexBit;
}

bool isBit1(int num, int indexBit) {
  num = num >> indexBit;
  return (num & 1) == 1;
}

void test(const string &testName, vector<int> numbers,
          NumbersOccurringOnce expected) {
  cout << testName << " begins: ";

  NumbersOccurringOnce once;
  getOnce(numbers, once);

  if ((once.num1 == expected.num1 && once.num2 == expected.num2) ||
      (once.num1 == expected.num2 && once.num2 == expected.num1))
    cout << "passed.\n";
  else
    cout << "FAILED.\n";
}

void Test1() {
  vector<int> numbers{2, 4, 3, 6, 3, 2, 5, 5};
  NumbersOccurringOnce expected;
  expected.num1 = 4;
  expected.num2 = 6;
  test("test1", numbers, expected);
}

void Test2() {
  vector<int> numbers{4, 6};
  NumbersOccurringOnce expected;
  expected.num1 = 4;
  expected.num2 = 6;
  test("test2", numbers, expected);
}

void Test3() {
  vector<int> numbers{4, 6, 1, 1, 1, 1};
  NumbersOccurringOnce expected;
  expected.num1 = 4;
  expected.num2 = 6;
  test("test3", numbers, expected);
}

int main(int argc, char *argv[]) {
  Test1();
  Test2();
  Test3();

  return 0;
}
