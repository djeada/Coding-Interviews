#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

void fillArray(vector<int> &m, int x) {
  for (int i = 0; i < x; i++)
    m.push_back(0);
}

int GetMinCount(int total, vector<int> coins) {
  vector<int> counts;
  fillArray(counts, total + 1);
  counts[0] = 0;

  const int MAX = INT_MAX;

  for (int i = 1; i <= total; ++i) {
    int count = MAX;
    for (int j = 0; j < coins.size(); ++j) {
      if (i - coins[j] >= 0 && count > counts[i - coins[j]])
        count = counts[i - coins[j]];
    }
    if (count < MAX)
      counts[i] = count + 1;
    else
      counts[i] = MAX;
  }

  return counts[total];
}

// ============================ test code ============================
void Test(const string &testName, int total, vector<int> coins, int expected) {
  cout << testName << " begins: ";

  if (GetMinCount(total, coins) == expected)
    cout << "Passed.\n";
  else
    cout << "FAILED.\n";
}

void Test1() {
  vector<int> coins{1, 5, 10, 20, 25};
  int total = 40;
  int expected = 2;

  Test("test1", total, coins, expected);
}

void Test2() {
  vector<int> coins{1, 3, 9, 10};
  int total = 15;
  int expected = 3;

  Test("test2", total, coins, expected);
}

void Test3() {
  vector<int> coins{1, 2, 5, 21, 25};
  int total = 63;
  int expected = 3;

  Test("test3", total, coins, expected);
}

// Impossible to make changes
void Test4() {
  vector<int> coins{2, 4, 8, 16};
  int total = 63;
  int expected = INT_MAX;

  Test("test4", total, coins, expected);
}

// Total value is in the array for coins
void Test5() {
  vector<int> coins{1, 3, 9, 10};
  int total = 9;
  int expected = 1;

  Test("test5", total, coins, expected);
}

int main(int argc, char *argv[]) {
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();

  return 0;
}
