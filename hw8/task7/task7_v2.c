#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

int main(){

	char ff1[100];
	char ff2[100];

	printf("Enter first file path.\n");
	scanf("%s", ff1);
	printf("Enter second file path.\n");
	scanf("%s", ff2);


	int fd1 = open(ff1, O_RDONLY);
	if(fd1 == -1){
		perror("Error on opening first file.\n");
		exit(1);
	}
	int fd2 = open(ff2, O_RDONLY);
	if(fd2 == -1){
		perror("Error on opening second file.\n");
		exit(1);
	}
	int size = 100;
	char buf1[size];
	char buf2[size];

	int count = 0;
	while(1){
		int ret1 = read(fd1, buf1, sizeof(buf1));
		if(ret1 == -1){
			perror("Error on reading first file.\n");
			exit(1);
		}
		int ret2 = read(fd2, buf2, sizeof(buf2));
		if(ret2 == -1){
			perror("Error on reading second file.\n");
			exit(1);
		}

		int min = ret1 < ret2 ? ret1 : ret2;

		for(int i = 0; i < min; i++){
			if(buf1[i] != buf2[i]){
				printf("Files differ at byte %d.\n", i);
				exit(1);
			}
		}

		if(ret1 != ret2){
			printf("Files differ at byte %d.\n", abs(ret1 - ret2));
			exit(1);
		}
		if(ret1 == 0 && ret2 == 0){
			printf("Files are identical.\n");
			exit(0);
		}
	}
	return 0;
}
