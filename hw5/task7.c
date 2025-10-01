#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

void *aligned_malloc(size_t size, size_t alignment){

	if(alignment & (alignment - 1))
		return NULL; 

	void *ptr = malloc(size + alignment - 1 + sizeof(void *));
	if(!ptr){
		printf("Error on allocating memory.\n");
		return NULL;
	}
	uintptr_t actual_ptr_address = (uintptr_t)ptr + sizeof(void *);
	uintptr_t aligned_ptr_address = (actual_ptr_address + alignment - 1) 
						& ~(uintptr_t)(alignment - 1);
	void **aligned_ptr = (void **)aligned_ptr_address;
	aligned_ptr[-1] = ptr;

	return (void *)aligned_ptr;
}
void aligned_free(void *ptr){
	if(!ptr){
		return;
	}

	void **actual_ptr = (void **)ptr;

	free(actual_ptr[-1]);
}

int main(){

	printf("Allocate an array for 10 elements\n");
	int *arr = (int *)aligned_malloc(10 * sizeof(int), 32);
	printf("The allocated array's address starts at %p\n", arr);
	aligned_free(arr);

	return 0;
}
