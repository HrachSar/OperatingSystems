#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "../my_malloc.h"

void check_block_counts(void);

void test_basic_allocation(void)
{
    void *p = my_malloc(64);
    CU_ASSERT_PTR_NOT_NULL(p);
    
    memset(p, 0xAB, 64);
    unsigned char *bytes = (unsigned char *)p;
    for (int i = 0; i < 64; i++) {
        CU_ASSERT_EQUAL(bytes[i], 0xAB);
    }

    my_free(p);
}

void test_multiple_allocations(void)
{
    void *p1 = my_malloc(32);
    void *p2 = my_malloc(64);
    void *p3 = my_malloc(128);

    CU_ASSERT_PTR_NOT_NULL(p1);
    CU_ASSERT_PTR_NOT_NULL(p2);
    CU_ASSERT_PTR_NOT_NULL(p3);

    CU_ASSERT_TRUE((uintptr_t)p1 + 32 < (uintptr_t)p2);
    CU_ASSERT_TRUE((uintptr_t)p2 + 64 < (uintptr_t)p3);

    my_free(p1);
    my_free(p2);
    my_free(p3);
}

void test_reuse_freed_blocks(void)
{
    void *p1 = my_malloc(48);
    my_free(p1);

    void *p2 = my_malloc(48);
    CU_ASSERT_PTR_NOT_NULL(p2);
    my_free(p2);
}

void test_large_allocation(void)
{
    void *p = my_malloc(200 * 1024);  // > CHUNK_SIZE
    CU_ASSERT_PTR_NOT_NULL(p);

    memset(p, 0, 1024);
    my_free(p);
}

void test_file_allocation(void){
	void *p = my_mmap_file("../data.txt", 200 * 1024, O_CREAT | O_RDWR, 0644);
	CU_ASSERT_PTR_NOT_NULL(p);
	
	printf("%d", getpid());
	memset(p, 0, 200 * 1024);

	while(1);

	my_munmap_file(p);
}

extern size_t alloced_count[];
void test_check_block_counts(void)
{
    for (int i = 0; i < 50; i++) {
        void *p = my_malloc(100);
        CU_ASSERT_PTR_NOT_NULL(p);
    }

    for (int i = 0; i < 12; i++) {
	printf("%d %zu \n", i, alloced_count[i]);
        CU_ASSERT(alloced_count[i] <= 20);
    } 
}

int main()
{
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    CU_pSuite suite = CU_add_suite("MyMalloc Suite", 0, 0);
    if (!suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(suite, "Basic Allocation", test_basic_allocation);
    CU_add_test(suite, "Multiple Allocations", test_multiple_allocations);
    CU_add_test(suite, "Reuse Freed Blocks", test_reuse_freed_blocks);
    CU_add_test(suite, "Large mmap Allocation", test_large_allocation);
    CU_add_test(suite, "Block Count Management", test_check_block_counts);
    CU_add_test(suite, "Large File Mapping", test_file_allocation);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
