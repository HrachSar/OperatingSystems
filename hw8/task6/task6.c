#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


int main(){

	int fd = open("numbers.txt", O_CREAT | O_WRONLY | O_TRUNC);
	if(fd == -1){
		perror("Error on opening numbers.txt.\n");
		return 1;
	}
	int i = 1;
	while(i < 10){
		char c = i + '0';
		int wr = write(fd, &c, 1);
		if(wr == -1){
			perror("Error on writing into numbers.txt.\n");
			close(fd);
			return 1;
		}
		wr = write(fd, "\n", 1);
                if(wr == -1){
                        perror("Error on writing into numbers.txt.\n");
                        close(fd);
			return 1;
                }
		i++;
	}
	int wr = write(fd, "10\n", 3);
        if(wr == -1){
              perror("Error on writing into numbers.txt.\n");
              close(fd);
	      return 1;
	}
	close(fd);
	
	int fd2 = open("numbers.txt", O_RDWR);
	if(fd2 == -1){
		perror("Error on opening numbers.txt.\n");
		return 1;
	}
	int n = 0;
	int offset = 0;
	char c;
	int ret;
	while((ret = read(fd2, &c, 1)) == 1){
		offset++;
		if(c == '\n')
			n++;
		if(n == 4)
			break;
	}

	int ls = lseek(fd2, offset, SEEK_SET);
        if(ls == -1){
                perror("Error on seeking the file.\n");
                close(fd2);
		return 1;
        }
	printf("%d", ls);
	
	char buff[100];
	
	int rd = read(fd2, buff, sizeof(buff));
	
	if(rd == -1){
		perror("Error on reading into buffer.\n");
		close(fd2);
		return 1;
	}
	*(buff + rd) = '\0';

	ls = lseek(fd2, offset - 2, SEEK_SET);
	if(ls == -1){
		perror("Error on seeking the file.\n");
		close(fd2);
		return 1;
	}
	wr = write(fd2, "100\n", 4);
        if(wr == -1){
                perror("Error on writing into the file.\n");
                close(fd2);
		return 1;
        }
	wr = write(fd2, buff, rd);
	if(wr == -1){
		perror("Error on writing into the file.\n");
		close(fd2);
		return 1;
	}
	close(fd2); 	

	return 0;
}
