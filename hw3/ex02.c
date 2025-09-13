#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(){
    pid_t pid;
    int status;

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
        wait(&status);
        printf("Child's status = %d\n", status); // First child's status
        pid = fork();
        if (pid < 0){
            printf("error\n");
            return -1;
        }
        if (pid == 0){
            //Inside the new child's process
            printf("New child's pid = %d\n", getpid());
            exit(0);
        }
        else{
            //Inside the parent's process
            //pid will hold child's pid
            waitpid(pid, &status, 0);
            printf("New child's exit status = %d\n", status);
        }
        printf("Parent's pid = %d\n", getpid());
    }
    return 0;
}