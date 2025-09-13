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
        //Inside the new child's process
        printf("Child's pid = %d\n", getpid());
        exit(0);
    }
    else{
        
        //Inside the parent's process
        sleep(5); //This will put the child process in zombie state because 
        //parent doesnt know about the termination status of the child, it is in 
        //sleep mode.
        
        waitpid(pid, &status, 0);
        //Now let's wait for the child process termination

        printf("Child's exit status = %d\n", status);
    }
    return 0;
}