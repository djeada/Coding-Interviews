#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

static void combination(const string &str, int index, int number,
                        stack<char> &result);
template <typename T> void print(const std::stack<T> &stk) {
  struct cheat : std::stack<T> {
    using std::stack<T>::c;
  };
  const auto &seq = static_cast<const cheat &>(stk).c;

  for (const auto &v : seq)
    std::cout << v << ' ';
  std::cout << '\n';
}

void combination_solution1(const string &str) {
  stack<char> result;
  for (int i = 1; i <= str.length(); ++i) {
    combination(str, 0, i, result);
  }
}

static void combination(const string &str, int index, int number,
                        stack<char> &result) {
  if (number == 0) {
    print(result);
    return;
  }

  if (index == str.length()) {
    return;
  }

  // select the character str[index]
  result.push(str.at(index));
  combination(str, index + 1, number - 1, result);
  result.pop();

  // ignore the character str[index]
  combination(str, index + 1, number, result);
}

// ==================== solution 2 ====================
template <long unsigned int N> void print(const string &str, bitset<N> &bits) {
  for (int i = 0; i < str.length(); ++i) {
    if (bits[i])
      cout << str.at(i);
  }
  cout << endl;
}

template <long unsigned int N>
static bool increment(bitset<N> &bits, int length) {
  int index = length - 1;

  while (index >= 0 && bits[index] > 0) {
    bits.reset(index);
    --index;
  }

  if (index < 0)
    return false;

  bits.set(index);
  return true;
}

static void combination_solution2(const string &str) {
  bitset<100> bits;
  while (increment(bits, str.length())) {
    print(str, bits);
  }
}

// ==================== test code ====================
void test(const string &str) {
  cout << "Test Begins for " << str;

  cout << "\nSolution 1 \n";
  combination_solution1(str);

  cout << "\nSolution 2 \n";
  combination_solution2(str);
}

int main() {
  test("");
  test("a");
  test("ab");
  test("abc");
  test("abcd");

  return 0;
}
