#include <stdio.h>    
#include <string.h>
#include <stdlib.h>

void printArr(int *arr, int len)
{
    for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
}


int howManyDuplicates(int *arr, int len){
	int count = 0;
	for(int i = 0; i < len; i++) {    
        for(int j = i + 1; j < len; j++) {    
            if(arr[i] == arr[j])    
                count++; 
        }    
    }

	return count;
}

int *getDuplicates(int *arr, int len){

	int n = howManyDuplicates(arr,len);
	int* duplicates = malloc (sizeof (int) * n);
	memset(duplicates, 0, n*sizeof(int));

	int count = 0;
	for(int i = 0; i < len; i++) {    
        for(int j = i + 1; j < len; j++) {    
            if(arr[i] == arr[j]){    
                duplicates[count] = arr[i];
                count++; 
			}
        }    
    }
	return duplicates;
}

int main()    
{    
    int arr[] = {5, 6, 7, 6, 2, 2, 5, 4, 11};   
	int len =  sizeof(arr)/sizeof(arr[0]);

    printf("Array: \n");
	printArr(arr, len);

    printf("\nDuplicates: \n");
	printArr(getDuplicates(arr,len), howManyDuplicates(arr,len));
    printf("\n");

    return 0;    
}  
