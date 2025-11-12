#include <stdio.h>
#include <pthread.h>

int sum1 = 0;
int sum2 = 0;

void *arr_sum1(void *args){

	int *arr = (int *)args;
	for(int i = 0; i < 3; i++){
		sum1 += arr[i];
	}

	return NULL;
}
void *arr_sum2(void *args){
	int *arr = (int *)args;
	for(int i = 0; i < 3; i++){
		sum2 += arr[i];
	}

	return NULL;
}

int main(){
	int arr[] = {1, 4, 6, 7, 2, 8};

	pthread_t thread1, thread2;

	void *buff;
	buff = arr;

	if(pthread_create(&thread1, NULL, arr_sum1, buff) != 0){
		perror("Error on creating a thread.\n");
		return 1;
	}
	if(pthread_create(&thread2, NULL, arr_sum2, (void *)(buff + 3 * sizeof(int))) != 0){
		perror("Error on creating a thread.\n");
		return 1;
	}

	
	if(pthread_join(thread1, NULL) != 0){
		perror("Error on joining a thread with main thread.\n");
		return 1;
	}
	if(pthread_join(thread2, NULL) != 0){
		perror("Error on joining a thread with main thread.\n");
		return 1;
	}
	printf("The sum of the first half of arr = %d.\n", sum1);
	printf("The sum of the second half of arr = %d.\n", sum2);
	printf("Execution is complete.\n");
	return 0;
}
