#include <stdio.h>
#include <stdlib.h>


int main(){

	int n;
	printf("Enter the number of elements: ");
	scanf("%d", &n);

	int *arr;
	arr = (int *)malloc(n * sizeof(int));
	if(!arr){
		printf("Error on allocating memory for an array");
		return 1;
	}
	printf("Enter %d integers: ", n);
	for(int i = 0; i < n; i++){
		scanf("%d", (arr + i));
	}
	int sum = 0;
	for(int i = 0; i < n; i++){
		sum += arr[i];
	}
	printf("Sum of the array: %d\n", sum);
	free(arr);
	arr = NULL;
	return 0;
}
