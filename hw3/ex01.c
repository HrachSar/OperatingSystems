#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
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
        printf("Child's pid = %d\n", getpid());
        exit(0);
    }
    else{
        //Inside the parent process
        printf("Parent's pid = %d\n", getpid());
    }
    return 0;
}
