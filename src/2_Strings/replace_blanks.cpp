#include <cassert>
#include <cstring>

void replaceBlank(char string[], int capacity) {
  int originalLength, numberOfBlank, newLength;
  int i, indexOfOriginal, indexOfNew;

  if (string == NULL || capacity <= 0)
    return;

  originalLength = numberOfBlank = i = 0;
  while (string[i] != '\0') {
    originalLength++;

    if (string[i] == ' ')
      numberOfBlank++;

    i++;
  }

  newLength = originalLength + numberOfBlank * 2;
  if (newLength > capacity)
    return;

  indexOfOriginal = originalLength;
  indexOfNew = newLength;
  while (indexOfOriginal >= 0 && indexOfNew > indexOfOriginal) {
    if (string[indexOfOriginal] == ' ') {
      string[indexOfNew--] = '0';
      string[indexOfNew--] = '2';
      string[indexOfNew--] = '%';
    } else {
      string[indexOfNew--] = string[indexOfOriginal];
    }

    indexOfOriginal--;
  }
}

bool identical(char const *strA, char const *strB) {
  return 0 == strcmp(strA, strB);
}

void test1() {
  char string[100] = "hello world";
  char const *result = "hello%20world";
  replaceBlank(string, 100);
  assert(identical(string, result));
}

void test2() {
  char string[100] = " helloworld";
  char const *result = "%20helloworld";
  replaceBlank(string, 100);
  assert(identical(string, result));
}

void test3() {
  char string[100] = "helloworld ";
  char const *result = "helloworld%20";
  replaceBlank(string, 100);
  assert(identical(string, result));
}

void test4() {
  char string[100] = "hello  world";
  char const *result = "hello%20%20world";
  replaceBlank(string, 100);
  assert(identical(string, result));
}

int main(int argc, char *argv[]) {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
