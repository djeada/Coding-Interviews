#include <iostream>
#include <vector>

int eightQueen() {
  std::vector<int> columnIndex{0, 1, 2, 3, 4, 5, 6, 7};

  int count = 0;

  void Permutation(int columnIndex[], int length, int index, int *count) {
    int i, temp;

    int Check(int columnIndex[], int length) {
      int i, j;

      for (i = 0; i < length; ++i) {
        for (j = i + 1; j < length; ++j) {
          if ((i - j == columnIndex[i] - columnIndex[j]) ||
              (j - i == columnIndex[i] - columnIndex[j]))
            return 0;
        }
      }

      return 1;
    }

    if (index == length) {
      if (Check(columnIndex, length) != 0) {
        (*count)++;
      }
    } else {
      for (i = index; i < length; ++i) {
        temp = columnIndex[i];
        columnIndex[i] = columnIndex[index];
        columnIndex[index] = temp;

        Permutation(columnIndex, length, index + 1, count);

        temp = columnIndex[index];
        columnIndex[index] = columnIndex[i];
        columnIndex[i] = temp;
      }
    }
  }

  Permutation(columnIndex, 8, 0, &count);

  return count;
}

int main() {

  std::cout << "The count of ways to place eight queens: " << eightQueen()
            << std::endl;

  return 0;
}
