#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

int main(){
	int n;
	int *arr;

	scanf("%d", &n);
	arr = (int *)malloc(n * sizeof(int));

	size_t actual_size = malloc_usable_size(arr);
		
	printf("%zu: \n", actual_size);
	for(int i = 0; i < n; i++)
		arr[i] = i;

	if(arr == NULL)
	{
		printf("error on allocating the array");
		return 1;
	}
	free(arr);
	return 0;
}
