#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

void permutation(std::string &strIn, std::string &strOut,
                 std::vector<std::string> &result) {
  if (strIn.empty()) {
    result.push_back(strOut);
    return;
  }

  for (unsigned int i = 0; i < strIn.length(); ++i) {
    std::string newStrIn = strIn;
    std::string newStrOut = strOut;
    newStrIn.erase(i, 1);
    newStrOut += strIn.at(i);
    permutation(newStrIn, newStrOut, result);
  }
}

std::vector<std::string> permutations(std::string &strIn) {

  std::vector<std::string> result;

  std::string strOut;
  permutation(strIn, strOut, result);

  return result;
}

void test1() {
  std::string slowo = "Dora";

  std::vector<std::string> listOfPermutations = permutations(slowo);

  std::vector<std::string> result{
      "Droa", "Daor", "aDor", "aroD", "aDro", "aorD", "raDo", "roDa",
      "rDoa", "raoD", "aoDr", "arDo", "oraD", "oaDr", "orDa", "rDao",
      "oDar", "roaD", "oarD", "oDra", "Dora", "Daro", "Doar", "Drao"};

  sort(listOfPermutations.begin(), listOfPermutations.end());
  sort(result.begin(), result.end());
  assert(listOfPermutations == result);
}

int main() {
  test1();
  return 0;
}
