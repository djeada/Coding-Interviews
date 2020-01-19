#include <stdio.h>

int strToInt(char* s) {
	int x = 0;
	while(*s != 0) {
		x = x * 10 + *s - '0';
		s++;
	}
	return x;
}

int main() {  
 
   	char c = 'a';
    char s[] = "hello";
	
	printf("\n %s: %d \n", &c, strToInt(&c));
	printf("\n %s: %d \n", s, strToInt(s));

    return 0;
}
