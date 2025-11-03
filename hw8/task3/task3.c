#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


int main(){

	printf("Enter an existing file path.\n");
	char path[100];
	scanf("%s", path);

	int fd = open(path, O_RDONLY);
	if(fd == -1){
		perror("Error on opening a file.\n");
		return 1;
	}
	int ls = lseek(fd, 0, SEEK_END);
	if(ls == -1){
		perror("Error on seeking a file.\n");
		return 1;
	}
	int ret = 0;	
	int nr = 0;
	char c;
	int i = 0;
	while(-i < ls + 1){
		if(lseek(fd, i--, SEEK_END) == -1){
			perror("Error\n");
			return 1;
		}
		ret = read(fd, &c, 1);
		if(ret == -1){
			perror("Error on reading the file.\n");
			return 1;
		}
		nr = write(1, &c, 1);
		if(nr == -1){
			perror("Error on writing the file.\n");
			return 1;
		}
	}
	write(1, "\n", 1);
	close(fd);
	return 0;
}
