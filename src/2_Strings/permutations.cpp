/**
 * This program generates all permutations of a given input string.
 * It uses a recursive approach to construct each permutation by removing a
 * character from the input string and appending it to the output string until
 * the input string is empty. The resulting permutations are then stored in a
 * vector.
 */

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

// Helper function to generate permutations recursively
void generatePermutations(const std::string &input, std::string &output,
                          std::vector<std::string> &results) {
  if (input.empty()) {
    results.push_back(output);
    return;
  }

  for (size_t i = 0; i < input.length(); ++i) {
    std::string newInput = input.substr(0, i) + input.substr(i + 1);
    std::string newOutput = output + input[i];
    generatePermutations(newInput, newOutput, results);
  }
}

// Function to generate and return all permutations of a given string
std::vector<std::string> getAllPermutations(const std::string &input) {
  std::vector<std::string> results;
  std::string output;
  generatePermutations(input, output, results);
  return results;
}

void runTests() {
  std::string word = "Dora";
  std::vector<std::string> expectedPermutations{
      "Droa", "Daor", "aDor", "aroD", "aDro", "aorD", "raDo", "roDa",
      "rDoa", "raoD", "aoDr", "arDo", "oraD", "oaDr", "orDa", "rDao",
      "oDar", "roaD", "oarD", "oDra", "Dora", "Daro", "Doar", "Drao"};

  std::vector<std::string> generatedPermutations = getAllPermutations(word);
  std::sort(generatedPermutations.begin(), generatedPermutations.end());
  std::sort(expectedPermutations.begin(), expectedPermutations.end());

  assert(generatedPermutations == expectedPermutations);
  std::cout << "Test passed!\n";
}

int main() {
  runTests();
  return 0;
}
