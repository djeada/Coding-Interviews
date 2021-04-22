#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;
int Min(int num1, int num2, int num3);
int GetEditDistanceHelp(const string &str1, const string &str2,
                        vector<vector<int>> &distances, int len1, int len2);
void fillMatrix(vector<vector<int>> &m, int x, int y);

int GetEditDistance(const string &str1, const string &str2) {
  int len1 = str1.length();
  int len2 = str2.length();

  vector<vector<int>> distances;
  fillMatrix(distances, len1 + 1, len2 + 1);

  int editDistance = GetEditDistanceHelp(str1, str2, distances, len1, len2);

  return editDistance;
}

int GetEditDistanceHelp(const string &str1, const string &str2,
                        vector<vector<int>> &distances, int len1, int len2) {
  for (int i = 0; i < len2 + 1; ++i)
    distances[i][0] = i;

  for (int j = 0; j < len1 + 1; ++j)
    distances[0][j] = j;

  for (int i = 1; i < len2 + 1; ++i) {
    for (int j = 1; j < len1 + 1; ++j) {
      if (str1[j - 1] == str2[i - 1])
        distances[i][j] = distances[i - 1][j - 1];
      else {
        int deletion = distances[i][j - 1] + 1;
        int insertion = distances[i - 1][j] + 1;
        int substitution = distances[i - 1][j - 1] + 1;
        distances[i][j] = Min(deletion, insertion, substitution);
      }
    }
  }
  return distances[len2][len1];
}

int Min(int num1, int num2, int num3) {
  int less = (num1 < num2) ? num1 : num2;
  return (less < num3) ? less : num3;
}

void fillMatrix(vector<vector<int>> &m, int x, int y) {
  for (int i = 0; i < y; i++) {
    m.push_back({}); // We insert a blank row until there are X rows
    for (int j = 0; j < x; j++) {
      m[i].push_back(0); // Within the j'th row, we insert the element
                         // corresponding to the i'th column
    }
  }
}

void Test(const string &testName, const string &str1, const string &str2,
          int expected) {
  cout << testName << " begins: ";

  if (GetEditDistance(str1, str2) == expected)
    cout << "Passed.\n";
  else
    cout << "FAILED.\n";
}

void Test1() { Test("Test1", "kitten", "kitten", 0); }

void Test2() { Test("Test2", "kitten", "sitting", 3); }

void Test3() { Test("Test3", "Saturday", "Sunday", 3); }

void Test4() { Test("Test4", "ant", "parent", 3); }

void Test5() { Test("Test5", "parent", "ant", 3); }

void Test6() { Test("Test6", "parent", "", 6); }

void Test7() { Test("Test7", "", "parent", 6); }

int main(int argc, char *argv[]) {
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
  Test6();
  Test7();

  return 0;
}
