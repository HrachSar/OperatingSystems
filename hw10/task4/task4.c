#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 10

sem_t semA, semB, semC;

void *funcA(void *args){
	
	for(int i = 0; i < N - 1; i++){
		sem_wait(&semA);
		printf("Thread %c: %c %d \n", 'A', 'A', i); 
		sem_post(&semB);
	}

	return NULL;
}

void *funcB(void *args){

	for(int i = 0; i < N - 1; i++){
                sem_wait(&semB);
                printf("Thread %c: %c %d \n", 'B', 'B', i);
		sem_post(&semC);
        }

        return NULL;
}

void *funcC(void *args){

        for(int i = 0; i < N - 1; i++){
                sem_wait(&semC);
                printf("Thread %c: %c %d \n", 'C', 'C', i);
		sem_post(&semA);
        }

        return NULL;
}

int main(){

	pthread_t t[3];
	
	sem_init(&semA, 0, 1);
	sem_init(&semB, 0, 0);
	sem_init(&semC, 0, 0);

         if(pthread_create(&t[0], NULL, funcA, NULL) != 0){
                 perror("Error on creating a thread");
                 return 1;
         }
         if(pthread_create(&t[1], NULL, funcB, NULL) != 0){
                 perror("Error on creating a thread");
                 return 1;
         }
         if(pthread_create(&t[2], NULL, funcC, NULL) != 0){
                 perror("Error on creating a thread");
                 return 1;
         }

	for(int i = 0; i < 3; i++){
		if(pthread_join(t[i], NULL) != 0){
			perror("Error on joining a thread to main");
			return 1;
		}
	}
	sem_destroy(&semA);
	sem_destroy(&semB);
	sem_destroy(&semC);

	return 0;
}
