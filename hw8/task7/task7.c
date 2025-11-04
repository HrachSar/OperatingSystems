#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){

	char f1[100];
	char f2[100];
	
	printf("Print first file path.\n");
	scanf("%s", f1);
	printf("Print second file path.\n");
	scanf("%s", f2);

	int fd1 = open(f1, O_RDONLY);
	if(fd1 == -1){
		perror("Error on reading the first file.\n");
		return 1;
	}

	int fd2 = open(f2, O_RDONLY);
	if(fd2 == -1){
		perror("Error on reading the second file.\n");
		return 1;
	}

	int size = 100;
	char a[size], b[size];
	for(int i = 0; i < size; i++){
		a[i] = '0';
		b[i] = '0';
	}
	int ret1, ret2;
	int count = 0;
	//Bitwise AND for long circuit check 
	while((ret1 = read(fd1, a, sizeof(a))) != 0 & (ret2 = read(fd2, b, sizeof(b))) != 0){
		for(int i = 0; i < size; i++){
			if(a[i] != b[i]){
				printf("Files differ at byte %d.\n", i + count);
				close(fd1);
				close(fd2);
				exit(1);
			}
		}
		count += size;
	}
	if(ret1 == 0 && ret2 == 0){
		write(1, "Files are identical.\n", 22);	
	}
	close(fd1);
	close(fd2);

	exit(0);
}
