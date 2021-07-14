#include <cassert>
#include <functional>
#include <vector>

int eightQueen() {
  std::vector<int> columnIndex{0, 1, 2, 3, 4, 5, 6, 7};

  int count = 0;

  auto check = [](std::vector<int> &columnIndex, int length) {
    int i, j;

    for (i = 0; i < length; ++i) {
      for (j = i + 1; j < length; ++j) {
        if ((i - j == columnIndex[i] - columnIndex[j]) ||
            (j - i == columnIndex[i] - columnIndex[j]))
          return 0;
      }
    }

    return 1;
  };

  std::function<void(std::vector<int> &, int, int, int &)> permutation;
  permutation = [&](std::vector<int> &columnIndex, int length, int index,
                    int &count) -> void {
    int i, temp;

    if (index == length) {
      if (check(columnIndex, length) != 0) {
        count++;
      }
    } else {
      for (i = index; i < length; ++i) {
        temp = columnIndex[i];
        columnIndex[i] = columnIndex[index];
        columnIndex[index] = temp;

        permutation(columnIndex, length, index + 1, count);

        temp = columnIndex[index];
        columnIndex[index] = columnIndex[i];
        columnIndex[i] = temp;
      }
    }
  };

  permutation(columnIndex, 8, 0, count);

  return count;
}

void test() { assert(eightQueen() == 92); }

int main() {

  test();
  return 0;
}
