#include <algorithm>
#include <cassert>
#include <queue>
#include <vector>

std::vector<int> getLeastNumbers(std::vector<int> input, int k) {

  std::vector<int> output;
  std::priority_queue<int> maxQueue;

  auto compare = [](int num1, int num2) {
    if (num1 < num2)
      return 1;
    else if (num1 == num2)
      return 0;
    return -1;
  };

  auto _getLeastNumbers = [&](std::vector<int> input,
                              std::priority_queue<int> &output, int k) {
    output = std::priority_queue<int>();

    for (int i = 0; i < input.size(); ++i) {
      if (output.size() < k)
        output.push(input[i]);
      else {
        int max = output.top();
        int number = input[i];
        if (compare(number, max) > 0) {
          output.pop();
          output.push(number);
        }
      }
    }
  };

  _getLeastNumbers(input, maxQueue, k);

  int i = 0;
  while (!maxQueue.empty()) {
    output.push_back(maxQueue.top());
    maxQueue.pop();
    i++;
  }

  std::sort(output.begin(), output.end());
  return output;
}

void test1() {
  std::vector<int> numbers{4, 5, 1, 6, 2, 7, 3, 8};
  std::vector<int> expected{1, 2, 3, 4};

  assert(getLeastNumbers(numbers, expected.size()) == expected);
}

void test2() {
  std::vector<int> numbers{4, 5, 1, 6, 2, 7, 3, 8};
  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8};

  assert(getLeastNumbers(numbers, expected.size()) == expected);
}

void test3() {
  std::vector<int> numbers{4, 5, 1, 6, 2, 7, 3, 8};
  std::vector<int> expected{1};

  assert(getLeastNumbers(numbers, expected.size()) == expected);
}

void test4() {
  std::vector<int> numbers{4, 5, 1, 6, 2, 7, 2, 8};
  std::vector<int> expected{1, 2};

  assert(getLeastNumbers(numbers, expected.size()) == expected);
}

int main() {
  test1();
  test2();
  test3();
  test4();
  return 0;
}
