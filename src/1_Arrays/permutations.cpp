#include <cassert>
#include <functional>
#include <set>
#include <vector>

/**
 * This program generates all permutations of the elements from a given list of
 * integer vectors. Each permutation is represented as a set of integers.
 */

std::vector<std::set<int>>
generatePermutations(const std::vector<std::vector<int>> &inputVectors) {

  std::vector<std::set<int>> permutations;

  std::function<void(const std::vector<std::vector<int>> &, std::set<int> &)>
      computePermutations;
  computePermutations = [&](const std::vector<std::vector<int>> &inputVectors,
                            std::set<int> &currentPermutation) {
    if (currentPermutation.size() == inputVectors.size()) {
      permutations.push_back(currentPermutation);
      return;
    }

    const auto &currentVector = inputVectors[currentPermutation.size()];

    for (const auto &value : currentVector) {
      currentPermutation.insert(value);
      computePermutations(inputVectors, currentPermutation);
      currentPermutation.erase(value);
    }
  };

  std::set<int> currentPermutation;
  computePermutations(inputVectors, currentPermutation);

  return permutations;
}

void testGeneratePermutations() {
  // Test Case 1
  {
    std::vector<std::vector<int>> inputVectors{{1, 2}, {3, 4}, {5, 6}};
    std::vector<std::set<int>> expectedPermutations{
        {5, 3, 1}, {6, 3, 1}, {5, 4, 1}, {6, 4, 1},
        {5, 3, 2}, {6, 3, 2}, {5, 4, 2}, {6, 4, 2}};
    assert(generatePermutations(inputVectors) == expectedPermutations);
  }

  // Test Case 2
  {
    std::vector<std::vector<int>> inputVectors{{1, 2, 3, 4, 5}};
    std::vector<std::set<int>> expectedPermutations{{1}, {2}, {3}, {4}, {5}};
    assert(generatePermutations(inputVectors) == expectedPermutations);
  }

  // Test Case 3
  {
    std::vector<std::vector<int>> inputVectors{{6}, {7}, {8}, {9}};
    std::vector<std::set<int>> expectedPermutations{{6, 7, 8, 9}};
    assert(generatePermutations(inputVectors) == expectedPermutations);
  }
}

int main() {
  testGeneratePermutations();
  return 0;
}
