#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	
	printf("Print source file path.\n");
	char source_path[100];
	char dest_path[100];

	scanf("%s", source_path);
	printf("Print destination file path.\n");
	scanf("%s", dest_path);	
	
	int fd = open(source_path, O_RDONLY);

	if(fd == -1){
		perror("Error on opening source file.\n");
		return 1;
	}
	
	int fd2 = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd2 == -1){
		perror("Error on opening/creating destination file.\n");
		return 1;
	}
	char c;
	int count = 0;
	int ret;
	while((ret = read(fd, &c, sizeof(char))) != '\0'){
		if(ret == -1){
			perror("Error on reading from the source file.\n");
			close(fd);
			return 1;
		}
		int nr = write(fd2, &c, sizeof(char));
		if(nr == -1){
			perror("Error on writing into the destination file.\n");
			close(fd2);
			return 1;
		}
		count += nr;
	}

	printf("%d bytes read from the source file.\n", count);

	close(fd);
	close(fd2);

	return 0;

}
