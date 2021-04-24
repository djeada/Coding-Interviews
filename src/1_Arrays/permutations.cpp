#include <functional>
#include <cassert>
#include <vector>
#include <set>

std::vector<std::set<int>> permute(std::vector<std::vector<int>> &arrays) {

  std::vector<std::set<int>> result;

  std::function<void(std::vector<std::vector<int>> &, std::set<int> &)>
      permuteCore;
  permuteCore = [&](std::vector<std::vector<int>> &arrays,
                    std::set<int> &permutation) {
    if (permutation.size() == arrays.size()) {
      result.push_back(permutation);
      return;
    }

    std::vector<int> array = arrays[permutation.size()];

    for (unsigned int i = 0; i < array.size(); ++i) {
      permutation.insert(array[i]);
      permuteCore(arrays, permutation);
      permutation.erase(array[i]);
    }
  };

  std::set<int> permutation;
  permuteCore(arrays, permutation);

  return result;
}

void test1() {
  std::vector<std::vector<int>> arrays{{1, 2}, {3, 4}, {5, 6}};

  std::vector<std::set<int>> result{
      std::set<int>({5, 3, 1}), std::set<int>({6, 3, 1}),
      std::set<int>({5, 4, 1}), std::set<int>({6, 4, 1}),
      std::set<int>({5, 3, 2}), std::set<int>({6, 3, 2}),
      std::set<int>({5, 4, 2}), std::set<int>({6, 4, 2})};

  assert(permute(arrays) == result);
}

void test2() {
  std::vector<std::vector<int>> arrays{{1, 2, 3, 4, 5}};

  std::vector<std::set<int>> result{
      std::set<int>({1}), std::set<int>({2}), std::set<int>({3}),
      std::set<int>({4}), std::set<int>({5})};

  assert(permute(arrays) == result);
}

void test3() {
  std::vector<std::vector<int>> arrays{{6}, {7}, {8}, {9}};

  std::vector<std::set<int>> result{std::set<int>({6, 7, 8, 9})};

  assert(permute(arrays) == result);
}

int main() {

  test1();
  test2();
  test3();

  return 0;
}
