#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>

int main(){
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        printf("error\n");
        return -1;
    }
    if (pid == 0){
        //Inside child process
        execl("/usr/bin/echo", "echo", "Hello from the child process", NULL);

        perror("execl failed");
        exit(1);
    }
    else{
        wait(NULL);
        printf("Parent process done\n");
    }
    return 0;
}