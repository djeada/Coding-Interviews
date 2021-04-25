#include <cassert>
#include <cstring>

void deleteDuplication(char *pString) {
  int hashTable[256];
  char *pSlow = pString;
  char *pFast = pString;

  if (pString == NULL)
    return;

  memset(hashTable, 0, sizeof(hashTable));

  while (*pFast != '\0') {
    *pSlow = *pFast;

    if (hashTable[*pFast] == 0) {
      ++pSlow;
      hashTable[*pFast] = 1;
    }

    ++pFast;
  }

  *pSlow = '\0';
}

bool identical(char const *strA, char const *strB) {
  return 0 == strcmp(strA, strB);
}

void test1() {
  char string[] = "google";
  char const *result = "gole";
  deleteDuplication(string);
  assert(identical(string, result));
}

void test2() {
  char string[] = "aaaaaaaaaaaaaaaaaaaaa";
  char const *result = "a";
  deleteDuplication(string);
  assert(identical(string, result));
}

void test3() {
  char string[] = "";
  char const *result = "";
  deleteDuplication(string);
  assert(identical(string, result));
}

void test4() {
  char string[] = "abcacbbacbcacabcba";
  char const *result = "abc";
  deleteDuplication(string);
  assert(identical(string, result));
}

int main() {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
