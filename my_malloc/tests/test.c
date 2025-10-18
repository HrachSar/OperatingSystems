#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../my_malloc.h"


void *alloc_24(){
	return my_malloc(8);
}
void *alloc_32(){
	return my_malloc(16);
}
void *alloc_40(){
	return my_malloc(24);
}
void *alloc_48(){
	return my_malloc(32);
}
void *alloc_56(){
	return my_malloc(40);
}
void *alloc_64(){
	return my_malloc(48);
}
void *alloc_72(){
	return my_malloc(56);
}
void *alloc_128(){
	return my_malloc(100);
}
void *alloc_256(){
	return my_malloc(200);
}
void *alloc_512(){
	return my_malloc(459);
}
void *alloc_1024(){
	return my_malloc(940);
}
void *alloc_2048(){
	return my_malloc(1562);
}

void test_malloc(){
	CU_ASSERT_EQUAL(*(size_t *)((char *)alloc_24() - 2 * sizeof(size_t)), 24);
	CU_ASSERT_EQUAL(*(size_t *)((char *)alloc_32() - 2 * sizeof(size_t)), 32);
	CU_ASSERT_EQUAL(*(size_t *)((char *)alloc_40() - 2 * sizeof(size_t)), 40);
	CU_ASSERT_EQUAL(*(size_t *)((char *)alloc_48() - 2 * sizeof(size_t)), 48);
	CU_ASSERT_EQUAL(*(size_t *)((char *)alloc_56() - 2 * sizeof(size_t)), 56);
	CU_ASSERT_EQUAL(*(size_t *)((char *)alloc_64() - 2 * sizeof(size_t)), 64);
	CU_ASSERT_EQUAL(*(size_t *)((char *)alloc_72() - 2 * sizeof(size_t)), 72);
	//Fail test cases because size is aligned to 8 bytes
	CU_ASSERT_EQUAL(*(size_t *)((char *)alloc_128() - 2 * sizeof(size_t)), 100);
	CU_ASSERT_EQUAL(*(size_t *)((char *)alloc_256() - 2 * sizeof(size_t)), 200);
        CU_ASSERT_EQUAL(*(size_t *)((char *)alloc_512() - 2 * sizeof(size_t)), 459);
        CU_ASSERT_EQUAL(*(size_t *)((char *)alloc_1024() - 2 * sizeof(size_t)), 940);
        CU_ASSERT_EQUAL(*(size_t *)((char *)alloc_2048() - 2 * sizeof(size_t)), 1562);
}



int main(){

	if (CUE_SUCCESS != CU_initialize_registry())
	        return CU_get_error();
    
	CU_pSuite suite = CU_add_suite("MyMallocTests", 0, 0);
    
	if (!suite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(!CU_add_test(suite, "test", test_malloc)){
		CU_cleanup_registry();
        	return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
   	CU_basic_run_tests();

    	CU_cleanup_registry();
    	return CU_get_error();
}
