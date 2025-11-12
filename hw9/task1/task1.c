#include <stdio.h>
#include <pthread.h>

void *thread_msg(void *args){
	pthread_t currID = pthread_self();
	printf("Thread %lu is running.\n", (unsigned long)currID);

	return NULL;
}

int main(){
	pthread_t thread1, thread2, thread3;

	if(pthread_create(&thread1, NULL, thread_msg, NULL) != 0){
		perror("Error on creating a thread.\n");
		return 1;
	}
        if(pthread_create(&thread2, NULL, thread_msg, NULL) != 0){
                perror("Error on creating a thread.\n");
                return 1;
        }
        if(pthread_create(&thread3, NULL, thread_msg, NULL) != 0){
                perror("Error on creating a thread.\n");
                return 1;
        }

	if(pthread_join(thread1, NULL) != 0){
		perror("Error on joining a thread to main thread.\n");
		return 1;
	}
        if(pthread_join(thread2, NULL) != 0){
                perror("Error on joining a thread to main thread.\n");
                return 1;
        }
        if(pthread_join(thread3, NULL) != 0){
                perror("Error on joining a thread to main thread.\n");
                return 1;
        }

	printf("Execution is complete.\n");
	return 0;
}
