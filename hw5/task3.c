#include <stdio.h>
#include <stdlib.h>

int main(){

	int n = 10;
	int *arr = (int *)malloc(n * sizeof(int));
	if(!arr){
		printf("Error on allocating memory for an array");
		return 1;
	}
	printf("Enter %d integers: ", n);
	for(int i = 0; i < n; i++){
		scanf("%d", (arr + i));
	}		

	int new_size = 5;
	int *new_arr = (int *)realloc(arr, new_size * sizeof(int));
	if(!new_arr){
                printf("Error on reallocating memory for an array");
                return 1;
        }
	printf("Array after resizing: ");
	for(int i = 0; i < new_size; i++)
		printf("%d ", new_arr[i]);
	printf("\n");

	free(new_arr);
	new_arr = NULL;

	return 0;
}
