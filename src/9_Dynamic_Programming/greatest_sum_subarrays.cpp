#include <bits/stdc++.h>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

using namespace std;
int getGreatestSumOfSubArray(vector<int> numbers) {
  int curSum = 0;
  int greatestSum = INT_MIN;
  for (int i = 0; i < numbers.size(); ++i) {
    if (curSum <= 0)
      curSum = numbers[i];
    else
      curSum += numbers[i];
    if (curSum > greatestSum)
      greatestSum = curSum;
  }
  return greatestSum;
}

void test1() {
  vector<int> numbers{1, -2, 3, 10, -4, 7, 2, -5};
  int expected = 18;
  test("Test1", numbers, expected);
}

// all numbers are negative
void test2() {
  vector<int> numbers{-2, -8, -1, -5, -9};
  int expected = -1;
  test("Test2", numbers, expected);
}

// all numbers are positive
void test3() {
  vector<int> numbers{2, 8, 1, 5, 9};
  int expected = 25;
  test("Test3", numbers, expected);
}

// only one number
void test4() {
  vector<int> numbers{2};
  int expected = 2;
  test("Test4", numbers, expected);
}

int main() {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
