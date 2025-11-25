#include <stdio.h>
#include <pthread.h>

#define N 4
#define M 1000000

long long counter = 0;
int mode;
pthread_mutex_t mutex;
pthread_spinlock_t spin;

void *increment(void *args){

	int *mode = ((int *)args);
	*mode = 0;

	for(int i = 0; i < M; i++)
		counter += 1;

	return NULL;
}

void *increment_mutex(void *args){

	int *mode = ((int *)args);
	*mode = 1;
	for(int i = 0; i < M; i++){
		pthread_mutex_lock(&mutex);
		counter++;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void *increment_spinlock(void *args){

	int *mode = ((int *)args);
	*mode = 2;
	for(int i = 0; i < M; i++){
		pthread_spin_lock(&spin);
		counter++;
		pthread_spin_unlock(&spin);
	}

	return NULL;
}

int main(){

	pthread_t threads[N];
	pthread_mutex_init(&mutex, NULL);
	pthread_spin_init(&spin, PTHREAD_PROCESS_PRIVATE);
	for(int i = 0; i < N; i++){

		if(pthread_create(&threads[i], NULL, increment_spinlock, &mode) != 0){
			perror("Error on creating a thread");
			return 1;
		}
	}
	
	for(int i = 0; i < N; i++){
                if(pthread_join(threads[i], NULL) != 0){
                        perror("Error on joining to main thread");
                        return 1;
                }
	}
	pthread_mutex_destroy(&mutex);
	pthread_spin_destroy(&spin);
	if(mode == 0)
		printf("No sync.\n");
	else if(mode == 1)
		printf("Mutex.\n");
	else
		printf("Spin.\n");

	printf("Expected value = %d\n", M * N);
	printf("Actual value = %lld\n", counter);

	return 0;
}
