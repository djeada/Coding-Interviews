#include <iostream>
#include <vector>
using namespace std;

bool checkOddBeforeEven(vector<int> nums);

void reorderOddEven_solution1(vector<int> &nums) {
	int begin = 0;
	int end = nums.size()- 1;
	while(begin < end) {
		// Move begin forwards until it meets an even number
		while(begin < end && (nums[begin] & 0x1) != 0)
			begin++;
		
		// Move end backwards until it meets an odd number
		while(begin < end && (nums[end] & 0x1) == 0)
			end--;
		
		if(begin < end) {
			int temp = nums[begin];
			nums[begin] = nums[end];
			nums[end] = temp;
		}
	}
}
    
bool check(int num) {
	if((num & 0x1) == 0)
		return true;
	return false;
}

void reorderOddEven_solution2(vector<int> nums) {
	int begin = 0;
	int end = nums.size() - 1;
	while(begin < end) {
		while(begin < end && !check(nums[begin]))
			begin++;
		
		while(begin < end && check(nums[end]))
			end--;
		
		if(begin < end) {
			int temp = nums[begin];
			nums[begin] = nums[end];
			nums[end] = temp;
		}
	}
}
    
void test(const string &testName, vector<int> nums) {
	cout << testName << " begins: ";
    vector<int> copy(nums); 

    reorderOddEven_solution1(nums);
    if(checkOddBeforeEven(nums))
    	cout << "Solution1 Passed; ";
    else
    	cout << "Solution1 FAILED; ";
    
    reorderOddEven_solution2(copy);
    if(checkOddBeforeEven(copy))
    	cout << "Solution2 Passed.\n";
   	else
		cout << "Solution2 FAILED.\n";
}
    
bool checkOddBeforeEven(vector<int> nums) {
	int i = 0;
	while(i < nums.size()) {
		if((nums[i] & 0x01) == 0)
			break;
			++i;
	}

	while(i < nums.size()) {
		if((nums[i] & 0x01) == 1)
			break;
			++i;
	}
	return (i == nums.size());
}
    
void test1() {
	vector<int> nums {1, 2, 3, 4, 5, 6, 7};
	test("Test1", nums);
}
    
void test2() {
	vector<int> nums {2, 4, 6, 1, 3, 5, 7};
	test("Test2", nums);
}
    
void test3() {
	vector<int> nums {1, 3, 5, 7, 2, 4, 6};
	test("Test3", nums);
}

void test4() {
	vector<int> nums {1};
	test("Test4", nums);
}
    
void test5() {
	vector<int> nums {2};
	test("Test5", nums);
}
int main(){    
	test1();
	test2();
	test3();
	test4();
	test5();

    return 0;    
}  
