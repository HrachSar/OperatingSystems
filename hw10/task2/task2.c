#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#define N 4

long long balance = 0;
pthread_mutex_t mutex;
pthread_spinlock_t spin;

void *increment_balance(void *args){
        char **mode = (char **)(args);
        if(strcmp(mode[1], "mutex") == 0){
                pthread_mutex_lock(&mutex);
                balance++;
                if(strcmp(mode[2], "long") == 0)
                        sleep(1);

		pthread_mutex_unlock(&mutex);
        }else if(strcmp(mode[1], "spin") == 0){
                pthread_spin_lock(&spin);
                balance++;
                if(strcmp(mode[2], "long") == 0)
                        sleep(1);

		pthread_spin_unlock(&spin);
        }
        return NULL;
}

void *decrement_balance(void *args){
	char **mode = (char **)(args);
	if(strcmp(mode[1], "mutex") == 0){
		pthread_mutex_lock(&mutex);
		balance--;
		if(strcmp(mode[2], "long") == 0)
                        sleep(1);
		
		pthread_mutex_unlock(&mutex);
	}else if(strcmp(mode[1], "spin") == 0){
		pthread_spin_lock(&spin);
		balance--;
                if(strcmp(mode[2], "long") == 0)
                        sleep(1);

		pthread_spin_unlock(&spin);
	}
	return NULL;
}

int main(int argc, char **argv){
	
	pthread_t deposit_threads[N];
	pthread_t withdraw_threads[N];
	pthread_mutex_init(&mutex, NULL);
	pthread_spin_init(&spin, PTHREAD_PROCESS_PRIVATE);
	struct timeval start, end;

	if(argc == 3){
		gettimeofday(&start, NULL);
		for(int i = 0; i < N; i++){
			if(pthread_create(&deposit_threads[i], NULL, increment_balance,(void *)argv) != 0){
				perror("Error on creating a thread");
				return 1;
			}	
			if(pthread_create(&withdraw_threads[i], NULL, decrement_balance, (void *)argv)!= 0){
				perror("Error on creating a thread");
				return 1;
			}
		}
		for(int i = 0; i < N; i++){
                        if(pthread_join(deposit_threads[i], NULL) != 0){
                                perror("Error on joining to main thread");
                                return 1;
                        }
                        if(pthread_join(withdraw_threads[i], NULL) != 0){
                                perror("Error on joining to main thread");
                                return 1;
                        }

		}
		gettimeofday(&end, NULL);
	}

	pthread_mutex_destroy(&mutex);
	pthread_spin_destroy(&spin);
	double ms = (end.tv_sec - start.tv_sec) * 1000
        + (end.tv_usec - start.tv_usec) / 1000;
	printf("Execution time of %s using %s = %f.\n", argv[1], argv[2], ms);
	printf("The final balance = %lld.\n", balance);

	return 0;
}
