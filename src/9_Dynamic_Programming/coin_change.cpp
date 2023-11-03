/**
 * This program determines the minimum number of coins required to make up a
 * given total amount. Given a vector of coin denominations and a total amount,
 * it uses dynamic programming to compute the fewest number of coins needed to
 * make up that amount. If it's impossible to make the total with the given
 * coins, it returns INT_MAX.
 */

#include <cassert>
#include <climits>
#include <vector>

int findMinCoinCount(unsigned int targetAmount,
                     const std::vector<int> &coinDenominations) {
  std::vector<int> minCoinsForAmount(targetAmount + 1, INT_MAX);
  minCoinsForAmount[0] =
      0; // Base case: 0 coins are needed to make a total of 0

  for (int currentAmount = 1; currentAmount <= targetAmount; ++currentAmount) {
    for (const auto &coin : coinDenominations) {
      if (currentAmount - coin >= 0 && minCoinsForAmount[currentAmount - coin] <
                                           minCoinsForAmount[currentAmount]) {
        minCoinsForAmount[currentAmount] =
            minCoinsForAmount[currentAmount - coin] + 1;
      }
    }
  }

  return minCoinsForAmount[targetAmount];
}

void testMinimumCoinCount() {
  std::vector<int> testCoins1{1, 5, 10, 20, 25};
  assert(findMinCoinCount(40, testCoins1) == 2);

  std::vector<int> testCoins2{1, 3, 9, 10};
  assert(findMinCoinCount(15, testCoins2) == 3);

  std::vector<int> testCoins3{1, 2, 5, 21, 25};
  assert(findMinCoinCount(63, testCoins3) == 3);

  std::vector<int> testCoins4{2, 4, 8, 16};
  assert(findMinCoinCount(63, testCoins4) == INT_MAX);
}

int main() {
  testMinimumCoinCount();
  return 0;
}
