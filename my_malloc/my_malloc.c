#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include "my_malloc.h"

static void *start = NULL;
static void *end = NULL;


static size_t bin_sizes[MAX_BIN] = {24, 32, 40, 48, 56, 64, 72, 128, 256, 512, 1024, 2048};
static size_t bin_count[MAX_BIN] = {30, 31, 30, 30, 30, 30, 30, 31, 31, 31, 31, 30};
size_t alloced_count[MAX_BIN] = {0};
static List *free_list[MAX_BIN + 1] = {NULL};
static List *alloc_list[MAX_BIN + 1] = {NULL};
static List *mmap_list;
static int counter = 0;


void check_block_counts(){
	for(int i = 0; i < MAX_BIN; i++){
		if(alloced_count[i] >= MAX_MEM){
			if(split_blocks(i)){
				printf("splitting\n");
			}else{
				printf("merging\n");
				merge_blocks(i);
			}
		}
	}
}

int split_blocks(int i){
	size_t count_needed = alloced_count[i] - MAX_MEM + 1;

	for(int j = i + 1; j < MAX_BIN; j++){
		if(bin_sizes[j] % bin_sizes[i] == 0){
			size_t block_count = bin_sizes[j] / bin_sizes[i];
			size_t actual_count = (count_needed + block_count - 1) / block_count;

			if(alloced_count[j] + actual_count < MAX_MEM){
				int k = 0;
				while(k < actual_count){
					void *block = remove_block(&free_list[j], free_list[j]);
					if(!block){
						printf("Fatal error!\n");
						continue;
					}
					void *p = block;
					int l = 0;
					while (l < block_count){
						insert_block(&free_list[i], p);
						alloced_count[i]--;
						p += bin_sizes[i];
						l++;	
					}
					alloced_count[j]++;
					k++;
				}
				return 1;
			}
		}	
	}
	return 0;
}

int merge_blocks(int i){
	size_t count_needed = alloced_count[i] - MAX_MEM + 1;

	for(int j = i - 1; j >= 0; j--){
		if(bin_sizes[i] % bin_sizes[j] == 0){
			size_t block_count = bin_sizes[i] / bin_sizes[j];
			size_t actual_count = count_needed * block_count;
			printf("%zu %zu\n", bin_sizes[i], bin_sizes[j]);			
			if(alloced_count[j] + actual_count < MAX_MEM){
				printf("%zu %zu\n", actual_count, block_count);
				int k = 0;
				while(k < count_needed){
					void *start = get_contigous_blocks(&free_list[j], block_count, bin_sizes[j]);
					if(!start){
						printf("No possible merges of memory blocks\n");
						continue;
					}				
	

					for(int l = 0; l < block_count; l++){
						remove_block(&free_list[j], (void *)((char *)start + l * bin_sizes[j]));
					}

					insert_block(&free_list[i], start);
					alloced_count[i]--;
					alloced_count[j] += block_count;
					k++;
				}	
				return 1;
			}
		}
	}			
	return 0;
}

void *get_contigous_blocks(List **list, size_t block_count, size_t block_size){
	if(!list || !*list){
		printf("Invalid list\n");
		return NULL;
	}	
	
	List *curr = *list;
	void *start = (void *)curr;
	size_t count = 1;

	while(curr && curr->next){
		char *curr_address = (char *)curr;
		char *next_address = (char *)curr->next;

		if(next_address == curr_address - block_size){
			printf("%zu\n", count);
			count++;
		}else{
			count = 1;
			start = (void *)curr->next;
		}
		
		if(count == block_count){
			return (void *)next_address;
		}
		curr = curr->next;
	}

	return NULL;
}

//Split 128KB of memory into blocks
void split_mem(){
	char *p = (char *)start;

	for(int i = 0; i < MAX_BIN; i++){
		for(int j = 0; j < bin_count[i]; j++){
			List *b = (List *)p;
			b->next = free_list[i];
			free_list[i] = b;
			if((uintptr_t)(p + bin_sizes[i]) > (uintptr_t)end){
				printf("Exeeded the chunk size.\n");
				break;
			}
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
					void *ptr = (void *)((char*)block + 2 * sizeof(size_t));
					insert_block(&alloc_list[i], block);
					alloced_count[i]++;
					printf("%p, %zu \n", (void *)(block), *((size_t *)block));
					return ptr;
				}
			}
		}
	}else{
		//split to smaller chunks, maybe?
		//for now just sbrk
		List *temp = free_list[MAX_BIN];
		while(temp){
			size_t free_size = temp->size;
			printf("%zu\n", free_size);
			if (size <= free_size){
				void *ptr = remove_block(&free_list[MAX_BIN], temp);
				insert_block(&alloc_list[MAX_BIN], temp);

				return (void *)((char *)ptr + 2 * sizeof(size_t));
			}
			temp = temp->next;
		} 

		void *block = sbrk(size);	
		if(block == (void *)-1){
			printf("Heap alloc error.\n");
			return NULL;
		}
		*((size_t *)block) = size;
		void *ptr =  (void *)((char *)block + 2 * sizeof(size_t));
		insert_block(&alloc_list[MAX_BIN], block);
		return ptr;
	} 
}

//insert the pointer into free_list or alloc_list
void insert_block(List **list, void *ptr){
	
	size_t mem_size = *(size_t *)ptr;
	List *p = (List *)ptr;
	List *b = p;
	b->size = mem_size;
	b->next = *list;
	*list = b;
}

//8 byte alignment
size_t align_memory(size_t size, size_t alignment){

	if(size % alignment == 0)
		return size;

	return (size + alignment - 1) & ~(alignment - 1);
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

void *my_malloc_mmap_file(const char* path, size_t size, int flags, off_t mode){

	int fd = open(path, flags, mode);
	if(fd == -1){
		perror("Error on opening a file for mapping.\n");
		close(fd);
		return NULL;
	}
	
	ssize_t ssize = lseek(fd, 0, SEEK_END);
	if(ssize == -1){
		perror("Error on seeking the file.\n");
		close(fd);
		return NULL;
	}

	size_t aligned_mem = align_memory(size + 2 * sizeof(size_t), PAGE_SIZE);
	
	if(ssize < aligned_mem){
		if(ftruncate(fd, aligned_mem) == -1){
			perror("Error on resizing the file.\n");
			close(fd);
			return NULL;
		}
	}

	int prot = 0;
	if(flags & O_RDONLY) prot = PROT_READ;
        else if(flags & O_RDWR)	prot = PROT_READ | PROT_WRITE;

	void *block = mmap(NULL, aligned_mem, prot, MAP_SHARED, fd, 0);
	close(fd);

	void *ptr = (void *)((char *)block + 2 * sizeof(size_t));
	*(size_t *)block = aligned_mem;
	insert_block(&mmap_list, block);

	return ptr;
}

//allocate memory
void *my_malloc(size_t size){
	if(size < CHUNK_SIZE){

		size_t aligned_mem = align_memory(size + 2 * sizeof(size_t), DEFAULT_ALIGN);
		void *ptr = look_up(aligned_mem);
		if(!ptr){
			request_chunk();
			split_mem();
			ptr = look_up(aligned_mem);
		}
		counter++;
		if(counter >= MAX_MEM)
			check_block_counts();

		return ptr;
	}else{
		size_t aligned_mem = align_memory(size + 2 * sizeof(size_t), PAGE_SIZE);
		printf("%zu\n", aligned_mem);
		void *block = mmap(NULL, aligned_mem, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		if(block == MAP_FAILED){
			printf("Heap alloc error.\n");
			return NULL;
		}
		void *ptr = (void *)((char *)block + 2 * sizeof(size_t));
		*(size_t *)block = aligned_mem;
		insert_block(&mmap_list, block);	
		return ptr;
	}
}

void my_free(void *ptr){
	
	if(!ptr)
		return;

	void *block = (void *)((char *)ptr - 2 * sizeof(size_t));
	size_t mem_size = *(size_t *)block;
		
	//For medium allocations > 2048 bytes
	if(mem_size > bin_sizes[MAX_BIN - 1] && mem_size < CHUNK_SIZE){
		List *p = alloc_list[MAX_BIN];
		while(p){
			if(block == (void *)p){
				void *freed = remove_block(&alloc_list[MAX_BIN], p);
				insert_block(&free_list[MAX_BIN], freed);
				return;
			}
			p = p->next;
		}		
	}else if(mem_size > CHUNK_SIZE){ //Large allocations > 128KB
		List *p = mmap_list;
		while(p){
			if(block == (void *)p){
				void *freed = remove_block(&mmap_list, p);
				if(munmap(block, mem_size) == -1){
					printf("mmap free error\n");
					return;
				}
				return;
			}
			p = p->next;
		}
	}
	//Small allocations <= 2048 bytes
	for(int i = 0; i < MAX_BIN; i++){
		if(bin_sizes[i] >= mem_size){
			List *p = alloc_list[i];
			while(p){
				if(block == (void *)p){
					void *freed = remove_block(&alloc_list[i], p);			
					insert_block(&free_list[i], freed);
					alloced_count[i]--;
					return;	
				}
				p = p->next;
			}
		}
	}
	printf("Invalid pointer!\n");
	return;
}

void *remove_block(List **head, List *p){

	if(!p)
		return NULL;

	List *prev;
	List *curr = *head;

	if(curr != NULL && curr == p){
		*head = curr->next;	
		return (void *)curr;
	}

	while(curr != p){
		prev = curr;
		curr = curr->next;
	}

	if(!curr)
		return NULL;

	prev->next = curr->next;
	return (void *)curr;
}

void dump_list(List **list){
	List *curr = *list;

	while(curr != NULL){
		printf("%p ", (void *)curr);
		curr = curr->next;
	}	
	printf("End of the list\n");
}
/*
int main() {

	void *ptr1 = my_malloc(32);
	void *ptr2 = my_malloc(64);
	void *ptr3 = my_malloc(128);
	my_free(ptr1);
	my_free(ptr2);
	my_free(ptr3);
	return 0;	
} */
