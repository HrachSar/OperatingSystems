#include <stdlib.h>
#include <stdio.h>


int main(){

	double *arr = (double *)calloc(5, sizeof(double));
	if(!arr)
		return 1;

	for(int i = 0; i < 5; i++){
		printf("%f ", *(arr + i));
	}
	printf("\n");
	for(int i = 0; i < 5; i++){
		*(arr + i) = i / 2.0;
		printf("%f ", *(arr + i));
	}
	printf("\n");

	free(arr);
	arr = NULL;

	return 0;
}
