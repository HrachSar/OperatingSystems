#ifndef MY_MALLOC
#define MY_MALLOC

#define CHUNK_SIZE    128*1024
#define PAGE_SIZE     4096
#define DEFAULT_ALIGN 8
#define MAX_BIN       12
#define MAX_MEM       20

typedef struct List{
        size_t size;
        struct List *next;
} List;

void split_mem();
void *look_up(size_t size);
size_t align_memory(size_t size, size_t alignment);
void request_chunk();
void *my_malloc(size_t size);
void my_free(void *ptr);
void *remove_block(List **head, List *p);
void insert_block(List **list, void *ptr);
void dump_list(List **list);
void check_block_counts();
void *get_contigous_blocks(List **list, size_t block_count, size_t block_size);
int  split_blocks(int i);
int  merge_blocks(int i);
void *my_malloc_mmap_file(const char *path, size_t size, int flags, off_t mode);
void my_free_mmap_file(void *ptr);

#endif
