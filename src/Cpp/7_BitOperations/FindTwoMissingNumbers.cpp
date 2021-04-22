#include <bits/stdc++.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

typedef struct node {
  int num1;
  int num2;
} NumbersOccurringOnce;

int findFirstBitIs1(int num);
void getOnce(vector<int> numbers, NumbersOccurringOnce once);
bool isBit1(int num, int indexBit);

void fillArray(vector<int> &m, int x) {
  for (int i = 0; i < x; i++)
    m.push_back(0);
}

void findMissing_solution1(vector<int> numbers, NumbersOccurringOnce &missing) {
  int sum1 = 0;
  int product1 = 1;
  for (int i = 0; i < numbers.size(); ++i) {
    sum1 += numbers[i];
    product1 *= numbers[i];
  }

  int sum2 = 0;
  int product2 = 1;
  for (int i = 1; i <= numbers.size() + 2; ++i) {
    sum2 += i;
    product2 *= i;
  }

  int s = sum2 - sum1;
  int p = product2 / product1;

  missing.num1 = (s + (int)(sqrt(s * s - 4 * p))) / 2;
  missing.num2 = s - missing.num1;
}

void findMissing_solution2(vector<int> numbers, NumbersOccurringOnce &missing) {
  int originalLength = numbers.size();
  int extendedLength = originalLength * 2 + 2;
  vector<int> extention;
  fillArray(extention, extendedLength);
  for (int i = 0; i < originalLength; ++i)
    extention[i] = numbers[i];
  for (int i = originalLength; i < extendedLength; ++i)
    extention[i] = i - originalLength + 1;

  getOnce(extention, missing);
}

void getOnce(vector<int> numbers, NumbersOccurringOnce once) {
  if (numbers.size() < 2)
    return;

  int resultExclusiveOR = 0;
  for (int i = 0; i < numbers.size(); ++i)
    resultExclusiveOR ^= numbers[i];

  int indexOf1 = findFirstBitIs1(resultExclusiveOR);

  once.num1 = once.num2 = 0;
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

// check whether the bit with index indexBit is 1
bool isBit1(int num, int indexBit) {
  num = num >> indexBit;
  return (num & 1) == 1;
}

void test(const string &testName, vector<int> numbers,
          NumbersOccurringOnce &expected) {

  cout << testName << " begins: ";

  NumbersOccurringOnce missing;
  findMissing_solution1(numbers, missing);

  if ((missing.num1 == expected.num1 && missing.num2 == expected.num2) ||
      (missing.num1 == expected.num2 && missing.num2 == expected.num1))
    cout << "Solution1 passed; ";
  else
    cout << "Solution1 FAILED; ";

  findMissing_solution2(numbers, missing);

  if ((missing.num1 == expected.num1 && missing.num2 == expected.num2) ||
      (missing.num1 == expected.num2 && missing.num2 == expected.num1))
    cout << "Solution2 passed.\n";
  else
    cout << "Solution2 FAILED.\n";
}

void Test1() {
  vector<int> numbers{1, 3, 5, 6, 4, 7};
  NumbersOccurringOnce expected;
  expected.num1 = 2;
  expected.num2 = 8;

  test("test1", numbers, expected);
}

void Test2() {
  vector<int> numbers{1};
  NumbersOccurringOnce expected;
  expected.num1 = 2;
  expected.num2 = 3;

  test("test2", numbers, expected);
}

void Test3() {
  vector<int> numbers{3, 4};
  NumbersOccurringOnce expected;
  expected.num1 = 1;
  expected.num2 = 2;

  test("test3", numbers, expected);
}

int main(int argc, char *argv[]) {
  Test1();
  Test2();
  Test3();

  return 0;
}
