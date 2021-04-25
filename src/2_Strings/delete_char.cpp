#include <cassert>
#include <cstring>

void deleteCharacters(char *pString, char const *chars) {
  int hashTable[256];
  const char *pTemp = chars;
  char *pSlow = pString;
  char *pFast = pString;

  if (pString == NULL || chars == NULL)
    return;

  memset(hashTable, 0, sizeof(hashTable));
  while (*pTemp != '\0') {
    hashTable[*pTemp] = 1;
    ++pTemp;
  }

  while (*pFast != '\0') {
    if (hashTable[*pFast] != 1) {
      *pSlow = *pFast;
      ++pSlow;
    }
    ++pFast;
  }

  *pSlow = '\0';
}

bool identical(char const *strA, char const *strB) {
  return 0 == strcmp(strA, strB);
}

void test1() {
  char const *chars = "aeiou";
  char const *result = "W r stdnts";
  deleteCharacters(string, chars);
  assert(identical(string, result));
}

void test2() {
  char string[] = "We are students";
  char const *chars = "wxyz";
  char const *result = "We are students";
  deleteCharacters(string, chars);
  assert(identical(string, result));
}

void test3() {
  char string[] = "8613761352066";
  char const *chars = "1234567890";
  char const *result = "";
  deleteCharacters(string, chars);
  assert(identical(string, result));
}

void test4() {
  char string[] = "119911";
  char const *chars = "";
  char const *result = "119911";
  deleteCharacters(string, chars);
  assert(identical(string, result));
}

int main() {

  test1();
  test2();
  test3();
  test4();

  return 0;
}
