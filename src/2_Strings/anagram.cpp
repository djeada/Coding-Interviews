#include <cassert>
#include <string>
#include <unordered_map>

bool containsKey(std::unordered_map<char, int> hist, char key) {
  if (hist.find(key) != hist.end())
    return true;
  return false;
}

bool anagrams(const std::string &str1, const std::string &str2) {
  if (str1.size() != str2.size())
    return false;

  std::unordered_map<char, int> times;
  for (int i = 0; i < str1.size(); ++i) {
    char ch = str1.at(i);
    if (containsKey(times, ch))
      times[ch] += 1;
    else
      times[ch] = 1;
  }

  for (int i = 0; i < str2.size(); ++i) {
    char ch = str2.at(i);
    if (!containsKey(times, ch))
      return false;

    times[ch] -= 1;
  }

  return true;
}

void test1() { assert(anagrams("silent", "listen")); }

void test2() { assert(anagrams("evil", "live")); }

void test3() { assert(anagrams("eleven plus two", "twelve plus one")); }

void test4() { assert(!anagrams("there", "their")); }

int main(int argc, char *argv[]) {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
