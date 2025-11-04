#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


int main(){

	int fd = open("data.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd == -1){
		perror("Error on opening/creating data.txt.\n");
		return 1;
	}

	int nr = write(fd, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 26);
	if(nr == -1){
		perror("Error on writing into the data.txt.\n");
		close(fd);
		return 1;
	}
	close(fd);
	
	fd = open("data.txt", O_RDWR);
	int ls = lseek(fd, 0, SEEK_END);
	if(ls == -1){
		perror("Error on seeking data.txt.\n");
		close(fd);
		return 1;
	}
	printf("Current size = %d\n", ls);

	int tr = ftruncate(fd, 10);
	if(tr == -1){
		perror("Error on truncating data.txt.\n");
		close(fd);
		return 1;
	}	
	ls = lseek(fd, 0, SEEK_END);
	if(ls == -1){
		perror("Error on seeking data.txt.\n");
		close(fd);
		return 1;
	}
	printf("New size = %d\n", ls);
	
	ls = lseek(fd, 0, SEEK_SET);
        if(ls == -1){
                perror("Error on seeking data.txt.\n");
                close(fd);
		return 1;
        }
	int ret;
	char buffer[11];
	ret = read(fd, buffer, 10);
	if(ret == -1){
		perror("Error on reading data.txt.\n");
		close(fd);
		return 1;
	}
	buffer[10] = '\0';
	nr = write(1, buffer, 10);
	if(nr == -1){
		perror("Error on writing to stdout.\n");
		close(fd);
		return 1;
	}
	write(1, "\n", 1);
	close(fd);
	return 0;
}
