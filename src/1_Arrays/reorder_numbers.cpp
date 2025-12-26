/*
 * REORDER ARRAY BY ODD AND EVEN NUMBERS
 *
 * Given an integer vector, reorder it so that all odd numbers precede all even
 * numbers. The relative ordering within the odd or even groups doesn't need to
 * be preserved.
 *
 * Constraints:
 * - The input vector length is between 0 and 10^6.
 * - Elements in the vector are integers between INT_MIN and INT_MAX.
 *
 * Example Input/Output:
 * Input: [1, 2, 3, 4, 5, 6, 7]
 * Possible Output: [1, 7, 3, 5, 4, 6, 2]
 * Explanation: All odd numbers (1,3,5,7) appear before even numbers (2,4,6).
 */
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

// Helper function to determine if a number is even
bool isEven(int num) { return (num & 1) == 0; }

// Simple Solution (uses extra space, O(n))
std::vector<int> simpleSolution(const std::vector<int> &arr) {
  std::vector<int> odds, evens;
  for (int num : arr) {
    if (isEven(num))
      evens.push_back(num);
    else
      odds.push_back(num);
  }
  odds.insert(odds.end(), evens.begin(), evens.end());
  return odds;
}

// Optimal Solution (in-place partitioning, O(n))
std::vector<int> optimalSolution(std::vector<int> arr) {
  std::partition(arr.begin(), arr.end(), [](int num) { return !isEven(num); });
  return arr;
}

struct TestCase {
  std::string name;
  std::vector<int> input;
};

void testSimpleSolution(const std::vector<TestCase> &cases) {
  std::cout << "=== Testing simpleSolution ===\n";
  for (const auto &tc : cases) {
    auto result = simpleSolution(tc.input);
    bool pass = std::is_partitioned(result.begin(), result.end(),
                                    [](int num) { return !isEven(num); });
    std::cout << tc.name << ": result={";
    for (size_t i = 0; i < result.size(); ++i) {
      std::cout << result[i] << (i + 1 < result.size() ? "," : "");
    }
    std::cout << "} -> " << (pass ? "PASS" : "FAIL") << "\n";
    assert(pass);
  }
  std::cout << "\n";
}

void testOptimalSolution(const std::vector<TestCase> &cases) {
  std::cout << "=== Testing optimalSolution ===\n";
  for (const auto &tc : cases) {
    auto result = optimalSolution(tc.input);
    bool pass = std::is_partitioned(result.begin(), result.end(),
                                    [](int num) { return !isEven(num); });
    std::cout << tc.name << ": result={";
    for (size_t i = 0; i < result.size(); ++i) {
      std::cout << result[i] << (i + 1 < result.size() ? "," : "");
    }
    std::cout << "} -> " << (pass ? "PASS" : "FAIL") << "\n";
    assert(pass);
  }
  std::cout << "\n";
}

int main() {
  std::vector<TestCase> cases = {
      {"Mixed odds and evens", {1, 2, 3, 4, 5, 6, 7}},
      {"Odds already first", {1, 3, 5, 7, 2, 4, 6}},
      {"All evens", {2, 4, 6, 8}},
      {"All odds", {1, 3, 5, 7}},
      {"Empty array", {}},
      {"Single element odd", {9}},
      {"Single element even", {8}},
      {"Alternating start even", {2, 1, 4, 3, 6, 5}},
      {"Alternating start odd", {1, 2, 3, 4, 5, 6}}};

  testSimpleSolution(cases);
  testOptimalSolution(cases);

  std::cout << "All tests passed successfully!\n";
  return 0;
}
