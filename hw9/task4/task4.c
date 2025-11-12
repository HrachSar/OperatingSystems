#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

void *print_square(void *args){

	int i = *((int *)args);

	printf("square of %d = %d\n", i, i*i);
	return NULL;
}


int main(){

	int arr[] = {1, 2, 3, 4, 5};
	pthread_t threads[NUM_THREADS];	

	for(int i = 0; i < NUM_THREADS; i++){
		if(pthread_create(&threads[i], NULL, print_square, (void *)(&arr[i])) != 0){
			perror("Error on creating a thread.\n");
			return 1;
		}	
		if(pthread_join(threads[i], NULL) != 0){
			perror("Error on joinging a thread to main thread.\n");
			return 1;
		}
	}

	printf("Execution is complete.\n");
	return 0;
}
