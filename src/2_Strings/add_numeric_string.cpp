#include <cassert>
#include <string>

int checkInvalidInput(std::string &num1, std::string &num2, std::string &sum) {
  int length1, length2, i;

  if (num1.empty() || num2.empty() || !sum.empty())
    return -1;

  length1 = num1.size();
  for (i = 0; i < length1; ++i) {
    if (num1[i] < '0' || num1[i] > '9')
      return -1;
  }

  length2 = num2.size();
  for (i = 0; i < length2; ++i) {
    if (num2[i] < '0' || num2[i] > '9')
      return -1;
  }

  return 0;
}

void reverse(std::string &str) {
  int length = str.size();
  char temp;

  for (int i = 0; i < length / 2; ++i) {
    temp = str[i];
    str[i] = str[length - 1 - i];
    str[length - 1 - i] = temp;
  }
}

int add(std::string &num1, std::string &num2, std::string &sum) {
  unsigned int index1, index2, indexSum;
  int sumDigit, carry, digit1, digit2;

  if (checkInvalidInput(num1, num2, sum))
    return -1;

  reverse(num1);
  reverse(num2);

  index1 = index2 = indexSum = 0;
  carry = 0;
  while (index1 < num1.size() || index2 < num2.size()) {
    digit1 = (index1 == num1.size()) ? 0 : num1[index1] - '0';
    digit2 = (index2 == num2.size()) ? 0 : num2[index2] - '0';

    sumDigit = digit1 + digit2 + carry;
    carry = (sumDigit >= 10) ? 1 : 0;
    sumDigit = (sumDigit >= 10) ? sumDigit - 10 : sumDigit;

    sum += std::string(1, sumDigit + '0');

    if (index1 < num1.size())
      ++index1;
    if (index2 < num2.size())
      ++index2;
  }

  if (carry != 0)
    sum += std::string(1, carry + '0');

  reverse(sum);

  return 0;
}

void test1() {
  std::string num1 = "999";
  std::string num2 = "3";
  std::string sum;
  std::string result = "1002";
  add(num1, num2, sum);
  assert(sum == result);
}

void test2() {
  std::string num1 = "33";
  std::string num2 = "9999";
  std::string sum;
  std::string result = "10032";
  add(num1, num2, sum);
  assert(sum == result);
}

void test3() {
  std::string num1 = "3333333";
  std::string num2 = "222";
  std::string sum;
  std::string result = "3333555";
  add(num1, num2, sum);
  assert(sum == result);
}

void test4() {
  std::string num1 = "33abc33";
  std::string num2 = "222";
  std::string sum;
  std::string result = "";
  add(num1, num2, sum);
  assert(sum == result);
}

int main(int argc, char *argv[]) {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
