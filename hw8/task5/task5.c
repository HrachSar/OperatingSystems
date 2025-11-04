#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


int main(){

	int fd = open("sparse.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd == -1){
		perror("Error on opening file sparse.bin\n");
		return 1;
	}

	int wd = write(fd, "START", 5);
	if(wd == -1){
		perror("Error on writing into file.\n");;
		close(fd);
		return 1;
	}
	int ls = lseek(fd, 1024*1024, SEEK_CUR);
	if(ls == -1){
		perror("Error on seeking file.\n");
		close(fd);
		return 1;
	}
	wd = write(fd, "END", 3);
        if(wd == -1){
                perror("Error on writing into file.\n");;
                close(fd);
		return 1;
        }
	close(fd);

	fd = open("sparse.bin", O_RDONLY);
	if(fd == -1){
		perror("Error on opening the file.\n");
		return 1;
	}
	ls = lseek(fd, 0, SEEK_END);
	if(ls == -1){
		perror("Error on seeking the file.\n");
		close(fd);
		return 1;
	}
	printf("size = %d\n", ls);

	close(fd);	
}
