#include<iostream>
#include <vector>

using namespace std;


vector<vector<int>> declareVector(int rows, int cols){
	vector<vector<int> > vec( rows , vector<int> (cols, 0));
	return  vec;  
}
void printRing(vector<vector<int>> numbers, int start);
void printNumber(int number) {
	cout << number << "\t";
}

void printMatrixClockwise(vector<vector<int>> numbers) {
	int rows = numbers.size();
    int columns = numbers[0].size();
    int start = 0;
    
    while(columns > start * 2 && rows > start * 2) {
    	printRing(numbers, start);
    	++start;
    }
}

void printRing(vector<vector<int>> numbers, int start) {
	int rows = numbers.size();
	int columns = numbers[0].size();
	int endX = columns - 1 - start;
	int endY = rows - 1 - start;
	
	// Print a row from left to right
	for(int i = start; i <= endX; ++i) {
		int number = numbers[start][i];
		printNumber(number);
	}
	
	// print a column top down
	if(start < endY) {
		for(int i = start + 1; i <= endY; ++i) {
			int number = numbers[i][endX];
			printNumber(number);
		}
	}
	
	// print a row from right to left
	if(start < endX && start < endY) {
		for(int i = endX - 1; i >= start; --i) {
			int number = numbers[endY][i];
			printNumber(number);
		}
	}
	
	// print a column bottom up
	if(start < endX && start < endY - 1) {
		for(int i = endY - 1; i >= start + 1; --i) {
			int number = numbers[i][start];
			printNumber(number);
		}
	}
}


    
//================= Test Code =================
void test(int columns, int rows){
	cout << "Test Begin: ";
	cout << columns;
	cout << " columns, ";
	cout << rows;
	cout << " rows.\n";
	
	if(columns < 1 || rows < 1)
		return;

	vector<vector<int>> numbers = declareVector(rows,columns);
	for(int i = 0; i < rows; ++i) {
		for(int j = 0; j < columns; ++j) {
			numbers[i][j] = i * columns + j + 1;
		}
	}
	
	printMatrixClockwise(numbers);
	cout << endl;
}
    

int main(int argc, char* argv[])
{
	/*
	1    
	*/
	test(1, 1);

	/*
	1    2
	3    4
	*/
	test(2, 2);

	/*
	1    2    3    4
	5    6    7    8
	9    10   11   12
	13   14   15   16
	*/
	test(4, 4);

	/*
	1    2    3    4    5
	6    7    8    9    10
	11   12   13   14   15
	16   17   18   19   20
	21   22   23   24   25
	*/
	test(5, 5);

	/*
	1
	2
	3
	4
	5
	*/
	test(1, 5);

	/*
	1    2
	3    4
	5    6
	7    8
	9    10
	*/
	test(2, 5);

	/*
	1    2    3
	4    5    6
	7    8    9
	10   11   12
	13   14   15
	*/
	test(3, 5);

	/*
	1    2    3    4
	5    6    7    8
	9    10   11   12
	13   14   15   16
	17   18   19   20
	*/
	test(4, 5);

	/*
	1    2    3    4    5
	*/
	test(5, 1);

	/*
	1    2    3    4    5
	6    7    8    9    10
	*/
	test(5, 2);

	/*
	1    2    3    4    5
	6    7    8    9    10
	11   12   13   14    15
	*/
	test(5, 3);

	/*
	1    2    3    4    5
	6    7    8    9    10
	11   12   13   14   15
	16   17   18   19   20
	*/
	test(5, 4);
	
    return 0;
}




