#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 

/* Wrong
It is local!
char *allocateMemory() {
	char str[20] = "Hello world";
	return str;
*/

char* pointer = NULL;

void allocateMemory(char* str, int length){
	pointer = (char*)malloc(length);
}

int main() {   

	allocateMemory(pointer, 20);
	strcpy(pointer, "Hello my friend");
	printf("\n %s \n", pointer);
    
    return 0;
}
