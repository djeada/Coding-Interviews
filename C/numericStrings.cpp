#include <stdio.h>
#include <iostream>
using namespace std;

void scanDigits(char** string);
bool isExponential(char** string);

bool isNumeric(char* string){
    if(string == NULL){
        return false;
	}
    if(*string == '+' || *string == '-'){
        ++string;
    }
    if(*string == '\0'){
        return false;
   	}

    bool numeric = true;

    scanDigits(&string);
    if(*string != '\0'){
        // for floats
        if(*string == '.'){
            ++string;
            scanDigits(&string);
            
            if(*string == 'e' || *string == 'E'){
                numeric = isExponential(&string);
            }
        }
        // for integers
        else if(*string == 'e' || *string == 'E'){
            numeric = isExponential(&string);
        }
        else {
            numeric = false;
        }
    }

    return numeric && *string == '\0';
}

void scanDigits(char** string) {
    while(**string != '\0' && **string >= '0' && **string <= '9'){
        ++(*string);
    }
}

bool isExponential(char** string){
    if(**string != 'e' && **string != 'E'){
        return false;
    }
    ++(*string);
    if(**string == '+' || **string == '-'){
        ++(*string);
	}
	
    if(**string == '\0'){
        return false;
    }

    scanDigits(string);
    return (**string == '\0') ? true : false;
}

void Test(char* testName, char* string, bool expected) {
    if(testName != NULL){
        cout << testName << "begins: ";
    }

    if(isNumeric(string) == expected){
        cout << "Passed.\n";
    }
    else{
       cout << "FAILED.\n";
    }
}

int main() {
    Test("Test1", "100", true);
    Test("Test2", "123.45e+6", true);
    Test("Test3", "+500", true);
    Test("Test4", "5e2", true);
    Test("Test5", "3.1416", true);
    Test("Test6", "600.", true);
    Test("Test7", "-.123", true);
    Test("Test8", "-1E-16", true);
    Test("Test9", "1.79769313486232E+308", true);

    cout << endl << endl;

    Test("Test10", "12e", false);
    Test("Test11", "1a3.14", false);
    Test("Test12", "1+23", false);
    Test("Test13", "1.2.3", false);
    Test("Test14", "+-5", false);
    Test("Test15", "12e+5.4", false);

	return 0;
}
