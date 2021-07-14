#include <cassert>
#include <climits>
#include <vector>

int getMinCount(unsigned int total, std::vector<int> &coins) {
  std::vector<int> counts(total + 1);

  const int MAX = INT_MAX;

  for (int i = 1; i <= total; ++i) {
    int count = MAX;
    for (unsigned int j = 0; j < coins.size(); ++j) {
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

void test1() {
  std::vector<int> coins{1, 5, 10, 20, 25};
  unsigned int total = 40;
  int expected = 2;

  assert(getMinCount(total, coins) == expected);
}

void test2() {
  std::vector<int> coins{1, 3, 9, 10};
  unsigned int total = 15;
  int expected = 3;

  assert(getMinCount(total, coins) == expected);
}

void test3() {
  std::vector<int> coins{1, 2, 5, 21, 25};
  unsigned int total = 63;
  int expected = 3;

  assert(getMinCount(total, coins) == expected);
}

void test4() {
  std::vector<int> coins{2, 4, 8, 16};
  unsigned int total = 63;
  int expected = INT_MAX;

  assert(getMinCount(total, coins) == expected);
}

int main() {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
