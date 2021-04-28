#include <utility>
#include <vector>
#include <cassert>
#include <cmath>

int findFirstBitIs1(int num) {
  int indexBit = 0;

  while (((num & 1) == 0) && (indexBit < 32)) {
    num = num >> 1;
    ++indexBit;
  }

  return indexBit;
}

bool isBitOne(int num, int indexBit) {
  num = num >> indexBit;
  return (num & 1) == 1;
}

void getOnce(std::vector<int> &numbers, std::pair<int, int> &once) {

  if (numbers.size() < 2)
    return;

  int resultExclusiveOR = 0;

  for (unsigned int i = 0; i < numbers.size(); ++i)
    resultExclusiveOR ^= numbers[i];

  int indexOf1 = findFirstBitIs1(resultExclusiveOR);

  once.first = once.second = 0;

  for (unsigned int j = 0; j < numbers.size(); ++j) {
    if (isBitOne(numbers[j], indexOf1))
      once.second ^= numbers[j];
    else
      once.first ^= numbers[j];
  }
}

std::pair<int, int> findMissingV1(const std::vector<int> &numbers) {

  std::pair<int, int> missing;

  int sum1 = 0;
  int product1 = 1;

  for (unsigned int i = 0; i < numbers.size(); ++i) {
    sum1 += numbers[i];
    product1 *= numbers[i];
  }

  int sum2 = 0;
  int product2 = 1;

  for (unsigned int i = 1; i <= numbers.size() + 2; ++i) {
    sum2 += i;
    product2 *= i;
  }

  int s = sum2 - sum1;
  int p = product2 / product1;

  missing.first = (s + (int)(sqrt(s * s - 4 * p))) / 2;
  missing.second = s - missing.first;

  return std::pair<int, int>(missing);
}

std::pair<int, int> findMissingV2(const std::vector<int> &numbers) {

  std::pair<int, int> missing;

  int originalLength = numbers.size();
  int extendedLength = originalLength * 2 + 2;

  std::vector<int> extention(extendedLength, 0);

  for (int i = 0; i < originalLength; ++i)
    extention[i] = numbers[i];

  for (int i = originalLength; i < extendedLength; ++i)
    extention[i] = i - originalLength + 1;

  getOnce(extention, missing);

  if (missing.first < missing.second) {
   auto temp = missing.first;
   missing.first = missing.second;
   missing.second = temp;
  }

  return std::pair<int, int>(missing);
}

void test1() {
  std::vector<int> numbers{1, 3, 5, 6, 4, 7};
  std::pair<int, int> expected{8, 2};

  assert(findMissingV1(numbers) == expected);
  assert(findMissingV2(numbers) == expected);
}

void test2() {
  std::vector<int> numbers{1};
  std::pair<int, int> expected{3, 2};

  assert(findMissingV1(numbers) == expected);
  assert(findMissingV2(numbers) == expected);
}

void test3() {
  std::vector<int> numbers{3, 4};
  std::pair<int, int> expected{2, 1};

  assert(findMissingV1(numbers) == expected);
  assert(findMissingV2(numbers) == expected);
}

int main() {
  test1();
  test2();
  test3();

  return 0;
}
