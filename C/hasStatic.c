#include <stdio.h>

int n = 5;

int hasStatic(int n){
	static int x = 0;
	x += n;
	return x;
}

int main() {   
    int sum = 0;
	
	for(int i = 0; i < n; i++){
		sum += hasStatic(i);
	}

	printf("Result of sum is %d.\n", sum);
    
    return 0;
}
