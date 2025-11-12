#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *worker(void *arg){
	printf("working.\n");
	sleep(2);
	printf("Working 2.\n");

	return NULL;
}

int main(){

	pthread_t t;
	pthread_create(&t, NULL, worker, NULL);
	printf("Main thread exiting...\n");

	return 0;
}
