#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max_len 20


void isPalindrome_1(int x);
void isPalindrome_2(int x);
int isStrPalindrome(const char* const str);

int main() {   
    int number_1 = 121;
	int number_2 = 3356;
	int number_3 = 55855;
	int number_4 = 12811;

	isPalindrome_1(number_1);
	isPalindrome_1(number_2);
   	isPalindrome_2(number_3);
	isPalindrome_2(number_4);

    return 0;
}

void isPalindrome_1(int x){
	char str[max_len];
	sprintf(str, "%d", x);
	if(isStrPalindrome(str) == 1){
		printf("Number %d is palindrome \n", x);
	}
	else {
		printf("Number %d is not palindrome \n", x);
	}
}

void isPalindrome_2(int x){
	int reversed = 0;
	int copy = x;
	while(x != 0){
		reversed = reversed * 10 + x % 10;
		x /= 10;
	}
	if(reversed == copy){
		printf("Number %d is palindrome \n", copy);
	}
	else {
		printf("Number %d is not palindrome \n", copy);
	}
}

int isStrPalindrome(const char* const str){
	if(str != NULL) {
		int len = strlen(str);
		int half = len >> 1;
		
		for(int i = 0; i < half; i++){
			if(str[i] != str[len -1 -i]){
				return 0;
			}
		}
	}
	return 1;
}

