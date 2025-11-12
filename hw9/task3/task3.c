#include <stdio.h>
#include <pthread.h>


void *print_num(void *args){
	pthread_t currID = pthread_self();
	int i = 0;
	printf("executing %lu thread.\n", (unsigned long)currID);
	while(i++ < 5){
		printf("%d\n", i);
	}
	
	return NULL;
}

int main(){
	
	pthread_t thread1, thread2, thread3;

	if(pthread_create(&thread1, NULL, print_num, NULL) != 0){
		perror("Error on creating a thread.\n");
		return 1;
	}
        if(pthread_create(&thread2, NULL, print_num, NULL) != 0){
                perror("Error on creating a thread.\n");
                return 1;
        }
        if(pthread_create(&thread3, NULL, print_num, NULL) != 0){
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

	printf("Exection is complete.\n");
	return 0;
}
