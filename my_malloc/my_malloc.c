#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>

#define CHUNK_SIZE    128*1024
#define PAGE_SIZE     4096
#define DEFAULT_ALIGN 8
#define MAX_CHUNK     128
#define MAX_BIN       12

static void *start = NULL;
static void *end = NULL;

typedef struct List{
	size_t size;
	struct List *next;
} List;

static size_t bin_sizes[MAX_BIN] = {24, 32, 40, 48, 56, 64, 72, 128, 256, 512, 1024, 2048};
static size_t bin_count[MAX_BIN] = {1024, 774, 517, 321, 128, 63, 41, 22, 16, 8, 8, 6};
static List *free_list[MAX_BIN + 1] = {NULL};
static List *alloc_list[MAX_BIN + 1] = {NULL};
static List *mmap_list;

void split_mem();
void *look_up(size_t size);
size_t align_memory(size_t size, size_t alignment);
void request_chunk();
void *my_malloc(size_t size);
void my_free(void *ptr);
void *remove_block(List **head, List *p);
void insert_block(List **list, void *ptr);
void dump_list(List **list);

//Split 128KB of memory into blocks
void split_mem(){
	char *p = (char *)start;

	for(int i = 0; i < MAX_BIN; i++){
		for(int j = 0; j < bin_count[i]; j++){
			List *b = (List *)p;
			b->next = free_list[i];
			free_list[i] = b;
			if((uintptr_t)(p + bin_sizes[i]) > (uintptr_t)end){
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
		if(bin_sizes[i] == mem_size){
			List *p = alloc_list[i];
			while(p){
				if(block == (void *)p){
					void *freed = remove_block(&alloc_list[i], p);			
					insert_block(&free_list[i], freed);
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

int main() {
    	
	//dump_list(&free_list[1]);
	//dump_list(&alloc_list[1]);
	void *ptr = my_malloc(5 * sizeof(int));
	void *ptr2 = my_malloc(130 *1024);
	dump_list(&mmap_list);	
	my_free(ptr);
	dump_list(&mmap_list);
	
	return 0;
}
