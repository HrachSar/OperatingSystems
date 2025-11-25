#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define K 3
#define N 10

int counter = 0;

sem_t printers;
pthread_mutex_t mutex;

void *do_job(void *args){

	int *i = (int *)args;

	sem_wait(&printers);
	printf("Thread %d is printing.\n", *i);
	sleep(1.2);
	pthread_mutex_lock(&mutex);
	counter++;
	printf("Printing %d threads.\n", counter);
	pthread_mutex_unlock(&mutex);

	pthread_mutex_lock(&mutex);
        counter--;
        pthread_mutex_unlock(&mutex);
	sem_post(&printers);

	return NULL;
}


int main(){

	pthread_t threads[N];

	sem_init(&printers, 0, K);
	pthread_mutex_init(&mutex, NULL);
	int idx[N];

	for(int i = 0; i < N; i++){
		idx[i] = i;
		if(pthread_create(&threads[i], NULL, do_job, &idx[i]) != 0){
			perror("Error on creating a thread");
			return 1;
		}	
	}

	for(int i = 0; i < N; i++){
		if(pthread_join(threads[i], NULL) != 0){
			perror("Error on joining a thread to main");
			return 1;
		}
	}

	pthread_mutex_destroy(&mutex);
	sem_destroy(&printers);
	return 0;
}
