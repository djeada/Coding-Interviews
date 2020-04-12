#include <iostream>
#include <vector>
#include <bits/stdc++.h> 
using namespace std;


template < typename T > void print( const std::stack<T>& stk )
{
    struct cheat : std::stack<T> { using std::stack<T>::c ; } ;
    const auto& seq = static_cast< const cheat& >(stk).c ;

    for( const auto& v : seq ) std::cout << v << ' ' ;
    std::cout << '\n' ;
}

void permuteCore(vector<vector<int>> arrays, stack <int> permutation){
	if(permutation.size() == arrays.size()){
		print(permutation);
		return;
	}
	
	vector<int> array = arrays[permutation.size()];
	for(int i = 0; i < array.size(); ++i){
		permutation.push(array[i]);
		permuteCore(arrays, permutation);
		permutation.pop();
	}
}

void permute(vector<vector<int>> arrays){
	stack <int> permutation;
	permuteCore(arrays, permutation);
}
 
//================= Test Code =================
void test(const string &testName, vector<vector<int>> arrays){
	cout << testName << " begins: \n";
	permute(arrays);
}

void test1(){
	vector<vector<int>> arrays;
	
	vector<int> array1 {1, 2};
	vector<int> array2 {3, 4};
	vector<int> array3 {5, 6};
	
	arrays.push_back(array1);
	arrays.push_back(array2);
	arrays.push_back(array3);
	
	test("Test1", arrays);
}
    
void test2(){
	vector<vector<int>> arrays;
	
	vector<int> array1 {1, 2};
	vector<int> array2 {3, 4, 5};
	vector<int> array3 {6};
	
	arrays.push_back(array1);
	arrays.push_back(array2);
	arrays.push_back(array3);
	
	test("Test2", arrays);
}
    
void test3(){
	vector<vector<int>> arrays;
        
	vector<int> array1 {1, 2, 3};
	vector<int> array2 {4, 5, 6};
	vector<int> array3 {7, 8};
        
	arrays.push_back(array1);
	arrays.push_back(array2);
	arrays.push_back(array3);

	test("Test3", arrays);
}
    
void test4(){
	vector<vector<int>> arrays;
	vector<int> array1 {1, 2, 3, 4, 5};
	arrays.push_back(array1);

	test("Test4", arrays);
}
    
void test5(){ 
	vector<vector<int>> arrays;
	vector<int>  array1 {6};
	vector<int>  array2 = {7};
	vector<int>  array3 = {8};
	vector<int>  array4 = {9};
        
	arrays.push_back(array1);
	arrays.push_back(array2);
	arrays.push_back(array3);
	arrays.push_back(array4);

	test("Test4", arrays);
}
    
int main(int argc, char* argv[]){
	test1();
	test2();
	test3();
	test4();
	test5();
	return 1;
}
