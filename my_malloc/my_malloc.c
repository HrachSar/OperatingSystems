#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>

#define CHUNK_SIZE 128*1024
#define DEFAULT_ALIGN 8
#define MAX_CHUNK 128
#define MAX_BIN 8

static void *start = NULL;
static void *end = NULL;

typedef struct{
	char *start;
	size_t size;
} Chunk;

typedef struct{
	Chunk chunks[CHUNK_SIZE];
	size_t list_size;
} ChunkList;

typedef struct FreeList{
	struct FreeList *next;
} FreeList;

static size_t bin_sizes[MAX_BIN] = {16, 32, 64, 128, 256, 512, 1024, 2048};
static size_t bin_count[MAX_BIN] = {1024, 512, 256, 128, 64, 32, 16, 8};
static FreeList *free_list[MAX_BIN] = {NULL};
static ChunkList alloc_list = {.chunks = {{.start = NULL, .size = 0}}, .list_size = 0};

void split_mem();
void *look_up(size_t size);
size_t align_memory(size_t size, size_t alignment);
void request_chunk();
void *my_malloc(size_t size);
void insert_chunk(ChunkList *list, void *ptr, size_t mem_size);

//Split 128KB of memory into blocks
void split_mem(){

	char *p = (char *)start;

	for(int i = 0; i < MAX_BIN; i++){
		for(int j = 0; j < bin_count[i]; j++){
			FreeList *b = (FreeList *)p;
			b->next = free_list[i];
			free_list[i] = b;
			if((uintptr_t *)p + bin_sizes[i] > (uintptr_t *)end)
				break;
			p += bin_sizes[i];
		}
	}
}

//Look up in the list for a spare block and insert the block into alloc_list
void *look_up(size_t size){
	if (size <= bin_sizes[MAX_BIN - 1]){
		for(int i = 0; i < MAX_BIN; i++){
			if(size <= bin_sizes[i]){
				if(free_list[i]){
					void *block = (void *)free_list[i];
					free_list[i] = free_list[i]->next;

					*((size_t *)block) = size;
					insert_chunk(&alloc_list, (void *)((char *)block + sizeof(size_t)), size);
					printf("%p, %zu ", (void *)((char *)block + sizeof(size_t)), *((size_t *)block));
					return (void *)((char*)block + sizeof(size_t));
				}
			}
		}
	}else{
		//split to smaller chunks
		return NULL;
	}
	return NULL;

}

//insert a block into the list for future free() call
void insert_chunk(ChunkList *list, void *ptr, size_t mem_size){

	if(list->list_size >= MAX_CHUNK){
		printf("Filled heap\n");
		return;
	}
	list->chunks[list->list_size].start = ptr;
	list->chunks[list->list_size].size = mem_size;
	list->list_size++;

	printf("%p, %zu \n", list->chunks[list->list_size - 1].start, 
				list->chunks[list->list_size - 1].size);
}

//get the nearest 2's power
size_t align_memory(size_t size, size_t alignment){
	
	while(alignment < size) alignment <<= 1;

	return alignment;
}

//request a chunk
void request_chunk(){
	void *chunk = sbrk(CHUNK_SIZE);
	if(chunk == (void *)-1){
		  printf("Heap alloc error.\n");
		  return;
	}
	start = chunk;
	end = CHUNK_SIZE + chunk;
}

//allocate memory
void *my_malloc(size_t size){
	if(size < CHUNK_SIZE){

		size_t aligned_mem = align_memory(size, DEFAULT_ALIGN);
		void *ptr = look_up(aligned_mem);
		if(!ptr){
			request_chunk();
			split_mem();
			ptr = look_up(aligned_mem);
		}
		return ptr;
	}else{
		//call to mmap()
		return NULL;
	}
} 

int main() {
    	
	void *ptr = my_malloc(5 * sizeof(int));

	return 0;	
}
