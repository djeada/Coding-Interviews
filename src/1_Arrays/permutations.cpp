#include <bits/stdc++.h>
#include <cassert>
#include <vector>

std::vector<std::stack<int>> permute(std::vector<std::vector<int>> &arrays) {

  std::vector<std::stack<int>> result;

  std::function<void(std::vector<std::vector<int>> &, std::stack<int> &)>
      permuteCore;
  permuteCore = [&](std::vector<std::vector<int>> &arrays,
                    std::stack<int> &permutation) {
    if (permutation.size() == arrays.size()) {
      result.push_back(permutation);
      return;
    }

    std::vector<int> array = arrays[permutation.size()];

    for (unsigned int i = 0; i < array.size(); ++i) {
      permutation.push(array[i]);
      permuteCore(arrays, permutation);
      permutation.pop();
    }
  };

  std::stack<int> permutation;
  permuteCore(arrays, permutation);

  return result;
}

void test1() {
  std::vector<std::vector<int>> arrays{{1, 2}, {3, 4}, {5, 6}};

  std::vector<std::stack<int>> result{
      std::stack<int>({5, 3, 1}), std::stack<int>({6, 3, 1}),
      std::stack<int>({5, 4, 1}), std::stack<int>({6, 4, 1}),
      std::stack<int>({5, 3, 2}), std::stack<int>({6, 3, 2}),
      std::stack<int>({5, 4, 2}), std::stack<int>({6, 4, 2})};

  assert(permute(arrays) == result);
}

void test2() {
  std::vector<std::vector<int>> arrays{{1, 2, 3, 4, 5}};

  std::vector<std::stack<int>> result{
      std::stack<int>({1}), std::stack<int>({2}), std::stack<int>({3}),
      std::stack<int>({4}), std::stack<int>({5})};

  assert(permute(arrays) == result);
}

void test3() {
  std::vector<std::vector<int>> arrays{{6}, {7}, {8}, {9}};

  std::vector<std::stack<int>> result{std::stack<int>({6, 7, 8, 9})};

  assert(permute(arrays) == result);
}

int main() {

  test1();
  test2();
  test3();

  return 0;
}
