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
        exit(0);
    }
    else{
        //Inside the parent process
        waitpid(pid, &status, 0);
        printf("Child's exit status = %d\n", status); // First child's status

        if(WIFEXITED(status)){
            printf("Child exited normally with status %d\n", WEXITSTATUS(status));
        }else if (WIFSIGNALED(status)) {
            printf("Child terminated by signal %d\n", WTERMSIG(status));
        } else {
            printf("Child terminated abnormally\n");
        }

        pid = fork();
        if (pid < 0){
            printf("error\n");
            return -1;
        }
        if (pid == 0){
            //Inside the new child's process
            exit(1);
        }
        else{
            //Inside the parent's process
            waitpid(pid, &status, 0);
            if(WIFEXITED(status)){
                printf("Child exited normally with status %d\n", WEXITSTATUS(status));
            }else if (WIFSIGNALED(status)) {
                printf("Child terminated by signal %d\n", WTERMSIG(status));
            } else {
                printf("Child terminated abnormally\n");
            }
            printf("New child's exit status = %d\n", status);
        }
    }
    return 0;
}