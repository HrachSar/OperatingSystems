#include <stdio.h>
#include <stdlib.h>

int main(){

	int n;
	printf("Enter the number of elements: ");
	scanf("%d", &n);
	int *arr;
	arr = (int *)calloc(n, sizeof(int));
	if(!arr){
                printf("Error on allocating memory for an array");
                return 1;
        }
	printf("Array after calloc: ");
	for(int i = 0; i < n; i++)
		printf("%d ", arr[i]);
        printf("\n");
	printf("Enter %d integers: ", n);
	for(int i = 0; i < n; i++){
		scanf("%d", (arr + i));
	}	
	printf("Updated array: ");
	for(int i = 0; i < n; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
	int sum = 0;
	for(int i = 0; i < n; i++){
		sum += arr[i];
	}
	printf("Average of the array: %.2f\n", (float)sum / n);
	free(arr);
	arr = NULL;

	return 0;
}
