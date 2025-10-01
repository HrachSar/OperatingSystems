#include <stdlib.h>
#include <stdio.h>


int main(){

	int *ptr = (int *)malloc(sizeof(int));
	printf("%p \n", ptr);

	*ptr = 7;
	printf("%p \n", ptr);
	free(ptr);
	*ptr = 42;
	//Always NULL the pointer
	ptr = NULL;

	return 0;
}

