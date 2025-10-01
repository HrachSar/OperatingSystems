#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>

void *my_realloc(void *ptr, size_t size){
	
	//If pointer is NULL then return
	if(!ptr){
		return malloc(size);
	}
	//If size == 0 free the pointer and return
	if(size == 0){
		free(ptr);
		return NULL;
	}
	size_t actual_size = malloc_usable_size(ptr);
	void *dest = malloc(size);
	if(!dest){
		printf("Error on memory allocation\n");
		return NULL;
	}
	memcpy(dest, ptr, (actual_size < size) ? actual_size : size);
	free(ptr);

	return dest;
}
