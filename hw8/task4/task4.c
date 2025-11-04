#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void write_fd(unsigned int pid, int fd);

int main(){

	int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);

	if(fd == -1){
		perror("Error on reading log.txt.\n");
		return 1;
	}

	char buf[256];
	printf("Enter a text.\n");
	int rd = read(0, buf, sizeof(buf) - 1); 
	if(rd == -1){
		perror("Error on reading from stdin.\n");
		close(fd);
		return 1;
	}
	*(buf + rd) = '\0';	

	int wr = write(fd, "PID=", 4);
        if(wr == -1){
                perror("Error on writing into log.txt.\n");
                close(fd);
		return 1;
        }
	unsigned int pid = getpid();
        write_fd(pid, fd);
	wr = write(fd, ":", 1);
        if(wr == -1){
                perror("Error on writing into log.txt.\n");
                close(fd);
		return 1;
        }
	wr = write(fd, buf, rd);
	if(wr == -1){
		perror("Error on writing into log.txt.\n");
		close(fd);
		return 1;
	}
	wr = write(fd, "\n", 1);
        if(wr == -1){
		perror("Error on writing into log.txt.\n");
		close(fd);
		return 1;
	}
	int ls = lseek(fd, 0, SEEK_CUR);
	if(ls == -1){
		perror("Error on seeking log.txt.\n");
		close(fd);
		return 1;
	}
	write_fd(ls, 1);	
	close(fd);
}

void write_fd(unsigned int n, int fd){
	
	if (n > 9){
		write_fd(n / 10, fd);
	}
	char c = n % 10 + '0';
	int wr = write(fd, &c, 1);
	if(wr == -1){
		perror("Error on writing into log.txt.\n");
		close(fd);
		return;
	}
}

