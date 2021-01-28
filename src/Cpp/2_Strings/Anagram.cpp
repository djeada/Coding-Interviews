#include <iostream>
#include <string>
#include <unordered_map> 
using namespace std;

bool containsKey(unordered_map<char, int> hist, char key){
 	if (hist.find(key) != hist.end())
 		return true;
 	return false;
}
bool areAnagrams(const string &str1, const string &str2){
	if(str1.size() != str2.size())
		return false;
	
	unordered_map<char, int> times;
	for(int i = 0; i < str1.size(); ++i){
		char ch = str1.at(i);
		if(containsKey(times, ch))
			times[ch] += 1;
		else
			times[ch] = 1;
	}
	
	for(int i = 0; i < str2.size(); ++i){
		char ch = str2.at(i);
		if(!containsKey(times,ch))
			return false;

		times[ch] -= 1;
	}
        
	// If two strings with same length and containing
	// same set of chars are not anagrams,
	// it returns false before, because values of some
	// chars reach 0 in the second for loop above.
	// Therefore, it is safe to return true here.
	return true;
}

//================= Test Code =================
void test(const string &testName, const string &str1, const string &str2, bool expected){
	cout << testName << " begins: ";

	if(areAnagrams(str1, str2) == expected)
		cout << "passed.\n";
	else
		cout << "FAILED.\n";
}
    
void test1(){
	test("Test1", "silent", "listen", true);
}
    
void test2(){
	test("Test2", "evil", "live", true);
}
    
void test3(){
  	test("Test3", "eleven plus two", "twelve plus one", true);
}
    
void test4(){
	test("Test4", "there", "their", false);
}
    
void test5(){
	test("Test5", "an", "and", false);
}
    
int main(int argc, char* argv[])
{
    test1();
    test2();
    test3();
    test4();
    test5();
    
    return 0;
}
