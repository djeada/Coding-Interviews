#include <cassert>
#include <string>
#include <vector>

int min(int num1, int num2, int num3) {
  int less = (num1 < num2) ? num1 : num2;
  return (less < num3) ? less : num3;
}

int getEditDistanceHelp(const std::string &str1, const std::string &str2,
                        std::vector<std::vector<int>> &distances, int len1,
                        int len2) {
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
        distances[i][j] = min(deletion, insertion, substitution);
      }
    }
  }
  return distances[len2][len1];
}

void fillMatrix(std::vector<std::vector<int>> &m, int x, int y) {
  for (int i = 0; i < y; i++) {
    m.push_back({});
    for (int j = 0; j < x; j++) {
      m[i].push_back(0);
    }
  }
}

int getEditDistance(const std::string &str1, const std::string &str2) {
  int len1 = str1.length();
  int len2 = str2.length();

  std::vector<std::vector<int>> distances;
  fillMatrix(distances, len1 + 1, len2 + 1);

  int editDistance = getEditDistanceHelp(str1, str2, distances, len1, len2);

  return editDistance;
}

void test1() {
  std::string strA = "kitten";
  std::string strB = "kitten";
  int result = 0;
  assert(getEditDistance(strA, strB) == result);
}

void test2() {
  std::string strA = "bob";
  std::string strB = "bub";
  int result = 1;
  assert(getEditDistance(strA, strB) == result);
}

void test3() {
  std::string strA = "ROBOT";
  std::string strB = "robot";
  int result = 5;
  assert(getEditDistance(strA, strB) == result);
}

void test4() {
  std::string strA = "church";
  std::string strB = "ChUrCh";
  int result = 3;
  assert(getEditDistance(strA, strB) == result);
}

int main() {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
