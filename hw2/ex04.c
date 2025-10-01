#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>

int main(){

    pid_t pid;

    pid = fork();

    if (pid < 0){
        printf("error\n");
        return -1;
    }
    if (pid == 0){
        //Inside the child process
        execl("/usr/bin/grep", "grep", "main", "test.txt", NULL);

        perror("execl failed");
        exit(1);
    }
    else{
        wait(NULL);
        printf("Parent process done\n");
    }
}
