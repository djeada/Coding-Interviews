#include <iostream>
#include <vector>
#include <stdexcept>
#include <random>

using namespace std;
// Function to print the largest number 
void printLargest(int a[], int n) 
{ 
  
    // store the index of largest 
    // left most digit of elements 
    int max = -1; 
    int ind = -1; 
  
    // Iterate for all numbers 
    for (int i = 0; i < n; i++) { 
  
        int num = a[i]; 
  
        // check for the last digit 
        while (num) { 
            int r = num % 10; 
            num = num / 10; 
            if (num == 0) { 
                // check for the largest left most digit 
                if (max < r) { 
                    max = r; 
                    ind = i; 
                } 
            } 
        } 
    } 
  
    // print the largest number 
  
    // print the rotation of array 
    for (int i = ind; i < n; i++) 
        cout << a[i]; 
  
    // print the rotation of array 
    for (int i = 0; i < ind; i++) 
        cout << a[i]; 
} 
    
// ====================Test code====================
void Test(const string &testName, int numbers[], int n, const string &expectedResult){
	cout << testName + " begins:\n";
	cout << "Expected result is: " << expectedResult << "\t";
	cout << "Actual result is: ";
	printLargest(numbers, n);
	cout << "\n\n";
}

void Test1() {
	int numbers[] = {3, 5, 1, 4, 2};
	Test("Test1", numbers, 5, "12345");
}

void Test2() {
	int numbers[] = {3, 32, 321};
	Test("Test2", numbers, 3, "321323");
}

void Test3() {
	int numbers[] = {3, 323, 32123};
	Test("Test3", numbers, 3, "321233233");
}

void Test4() {
	int numbers[] = {1, 11, 111};
	Test("Test4", numbers, 3, "111111");
}

// There is only one element in an array
void Test5(){
	int numbers[] = {321};
    Test("Test5", numbers, 1, "321");
}
   
int main(){    
	 Test1();
     Test2();
     Test3();
     Test4();
     Test5();

    return 0;    
}  
