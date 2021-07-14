#include <queue>
#include <random>
#include <vector>

int randomInRange(int start, int end) {
  random_device rd;  // obtain a random number from hardware
  mt19937 eng(rd()); // seed the generator
  uniform_int_distribution<> distr(start, end);
  return distr(eng);
}

int compare(int num1, int num2) {
  if (num1 < num2)
    return 1;
  else if (num1 == num2)
    return 0;
  return -1;
}
void getLeastNumbers(vector<int> input, priority_queue<int> &output, int k);

void getLeastNumbers_1(vector<int> input, vector<int> &output) {

  priority_queue<int> maxQueue;
  getLeastNumbers(input, maxQueue, output.size());

  int i = 0;
  while (!maxQueue.empty()) {
    output[i] = maxQueue.top();
    maxQueue.pop();
    i++;
  }
}

void getLeastNumbers(vector<int> input, priority_queue<int> &output, int k) {
  // that's how you clear the queue
  output = priority_queue<int>();

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
}

int partition(vector<int> numbers, int start, int end);
void getLeastNumbers_2(vector<int> input, vector<int> &output) {
  int start = 0;
  int end = input.size() - 1;
  int k = output.size();
  int index = partition(input, start, end);
  while (index != k - 1) {
    if (index > k - 1) {
      end = index - 1;
      index = partition(input, start, end);
    } else {
      start = index + 1;
      index = partition(input, start, end);
    }
  }

  for (int i = 0; i < k; ++i)
    output[i] = input[i];
}

int partition(vector<int> numbers, int start, int end) {
  int index = randomInRange(start, end);
  swap(numbers[index], numbers[end]);

  int small = start - 1;
  for (index = start; index < end; ++index) {
    if (numbers[index] < numbers[end]) {
      ++small;
      if (small != index)
        swap(numbers[index], numbers[small]);
    }
  }

  ++small;
  swap(numbers[small], numbers[end]);

  return small;
}

void test1() {
  vector<int> numbers{4, 5, 1, 6, 2, 7, 3, 8};
  vector<int> expected{1, 2, 3, 4};

  test("Test1", numbers, expected);
}

void test2() {
  vector<int> numbers{4, 5, 1, 6, 2, 7, 3, 8};
  vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8};

  test("Test2", numbers, expected);
}

void test3() {
  vector<int> numbers{4, 5, 1, 6, 2, 7, 3, 8};
  vector<int> expected{1};
  test("Test3", numbers, expected);
}

void test4() {
  vector<int> numbers{4, 5, 1, 6, 2, 7, 2, 8};
  vector<int> expected{1, 2};
  test("Test4", numbers, expected);
}

int main() {
  test1();
  test2();
  test3();
  test4();
  return 1;
}
