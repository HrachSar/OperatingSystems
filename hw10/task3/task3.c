#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define BUFFER_SIZE 8
#define N 2
int buffer[BUFFER_SIZE];
int in_pos = 0;
int out_pos = 0;
int produced = 0;
int consumed = 0;

sem_t empty_slots;
sem_t full_slots;
pthread_mutex_t buffer_mutex;

void *produce_items(void *args){

	while(1){
		sem_wait(&empty_slots);
		pthread_mutex_lock(&buffer_mutex);
		buffer[in_pos] = 1;
		in_pos = (in_pos + 1) % BUFFER_SIZE;
		produced++;
		pthread_mutex_unlock(&buffer_mutex);
		sem_post(&full_slots);

		if(produced * consumed > 10){
			pthread_mutex_unlock(&buffer_mutex);
		 	break;	
		}
	}
	return NULL;
}

void *consume_items(void *args){
	
	while(1){
		sem_wait(&full_slots);	
		pthread_mutex_lock(&buffer_mutex);
		int i = buffer[out_pos];
		out_pos = (out_pos + 1) % BUFFER_SIZE;
		consumed++;
		pthread_mutex_unlock(&buffer_mutex);
		sem_post(&empty_slots);
                
		if(produced * consumed > 10){
                        pthread_mutex_unlock(&buffer_mutex);
                        break;      
                }

	}

	return NULL;
}
int main(){
	
	pthread_t p[N];
	pthread_t c[N];
	sem_init(&empty_slots, 0, BUFFER_SIZE);
	sem_init(&full_slots, 0, 0);
	pthread_mutex_init(&buffer_mutex, NULL);

	for(int i = 0; i < N; i++){
		if(pthread_create(&p[i], NULL, produce_items, NULL) != 0){
			perror("Error on creating a thread");
			return 1;
		}	
		if(pthread_create(&c[i], NULL, consume_items, NULL) != 0){
			perror("Error on creating a thread");
			return 1;
		}
	}

	for(int i = 0; i < N; i++){
		if(pthread_join(p[i], NULL) != 0){
			perror("Error on joining a thread to main");
			return 1;
		}
		if(pthread_join(c[i], NULL) != 0){
			perror("Error on joining a thread to main");
			return 1;
		}
	}

	pthread_mutex_destroy(&buffer_mutex);
	sem_destroy(&empty_slots);
	sem_destroy(&full_slots);
	return 0;
}
