#include <bits/stdc++.h>
#include <iostream>
#include <vector>

void print(const std::stack<int> &stk) {

  for (std::stack<int> dump = stk; !dump.empty(); dump.pop())
    std::cout << dump.top() << ' ';

  std::cout << std::endl;
}

void permute(std::vector<std::vector<int>> &arrays) {

  std::function<void(std::vector<std::vector<int>> &, std::stack<int> &)>
      permuteCore;
  permuteCore = [&](std::vector<std::vector<int>> &arrays,
                    std::stack<int> &permutation) {
    if (permutation.size() == arrays.size()) {
      print(permutation);
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
  std::cout << std::endl;
}

void test1() {
  std::vector<std::vector<int>> arrays;

  std::vector<int> array1{1, 2};
  std::vector<int> array2{3, 4};
  std::vector<int> array3{5, 6};

  arrays.push_back(array1);
  arrays.push_back(array2);
  arrays.push_back(array3);

  permute(arrays);
}

void test2() {
  std::vector<std::vector<int>> arrays;
  std::vector<int> array1{1, 2, 3, 4, 5};
  arrays.push_back(array1);

  permute(arrays);
  std::cout << std::endl;
}

void test3() {
  std::vector<std::vector<int>> arrays;
  std::vector<int> array1{6};
  std::vector<int> array2 = {7};
  std::vector<int> array3 = {8};
  std::vector<int> array4 = {9};

  arrays.push_back(array1);
  arrays.push_back(array2);
  arrays.push_back(array3);
  arrays.push_back(array4);

  permute(arrays);
  std::cout << std::endl;
}

int main() {

  test1();
  test2();
  test3();

  return 0;
}
