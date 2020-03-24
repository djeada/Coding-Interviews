#include<iostream>

using namespace std;

bool find(int matrix[][3], int value){
	int rows = sizeof( matrix )/sizeof( matrix[0]);
	int cols = sizeof( matrix[0])/sizeof( matrix[0][0]);
	int start = 0;
	int end = rows * cols - 1;
	
	while (start <= end) {
		int mid = start + (end - start) / 2;
        int row = mid / cols;
        int col = mid % cols;
        int v = matrix[row][col];
            
        if (v == value){
        	return true;
		}
		else if (v > value){
			end = mid - 1;
		}
		else {
			start = mid + 1;
		}
     }
        
	return false;
}
    
void test(const string &testName, int matrix[][3], int value, bool expected){
	cout << testName + " begins: ";
	
	if(find(matrix, value) == expected){
		cout << "passed.\n";
	}
    else{
    	cout << "FAILED.\n";
    }
}
    
	//  1   3   5
	//  7   9   11
	//  13  15  17
	// The value to be found, 7, is in the matrix;
void test1(){
	int matrix[][3] = {{1, 3, 5}, {7, 9, 11}, {13, 15, 17}};
	test("Test1", matrix, 7, true);
}
    
    //  1   3   5
    //  7   9   11
    //  13  15  17
    // The value to be found, 1, is in the matrix;
void test2(){
	int matrix[][3] = {{1, 3, 5}, {7, 9, 11}, {13, 15, 17}};
    test("Test2", matrix, 1, true);
}
    
    //  1   3   5
    //  7   9   11
    //  13  15  17
    // The value to be found, 17, is in the matrix;
void test3(){
	int matrix[][3] = {{1, 3, 5}, {7, 9, 11}, {13, 15, 17}};
	test("Test3", matrix, 17, true);
}
    
    //  1   3   5
    //  7   9   11
    //  13  15  17
    // The value to be found, 6, is not in the matrix;
void test4(){
	int matrix[][3] = {{1, 3, 5}, {7, 9, 11}, {13, 15, 17}};
   	test("Test4", matrix, 6, false);
}
    
    //  1   3   5
    //  7   9   11
    //  13  15  17
    // The value to be found, 0, is not in the matrix;
void test5(){
	int matrix[][3] = {{1, 3, 5}, {7, 9, 11}, {13, 15, 17}};
	test("Test5", matrix, 0, false);
}
    
    //  1   3   5
    //  7   9   11
    //  13  15  17
    // The value to be found, 18, is not in the matrix;
void test6(){
	int matrix[][3] = {{1, 3, 5}, {7, 9, 11}, {13, 15, 17}};
	test("Test6", matrix, 18, false);
}

int main(){
	 test1();
     test2();
     test3();
     test4();
     test5();
     test6();

	return 0;
}



