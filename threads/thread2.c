#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *thread_function(void *arg){
	printf("Thread executing...\n");

	return NULL;
}


int main(){
	pthread_t thread_1;
	
	if(pthread_create(&thread_1, NULL, thread_function, NULL) != 0){	
		perror("Error on creating a thread.\n");
		return 1;
	}
	
	printf("Thread created.\n");

	if(pthread_join(thread_1, NULL) != 0){
		perror("pthread_join error.\n");
		return 1;
	}
	
	printf("Finishing main thread.\n");

	return 0;
}
