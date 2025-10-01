#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        printf("error on creating child process\n");
        return -1;
    }
    if (pid == 0)
    {
        printf("Inside the child process\n");
    }else{
        printf("Inside the parent\n");
    }
    pid = fork();

    if (pid < 0)
    {
        printf("error on creating child process\n");
        return -1;
    }
    if (pid == 0)
    {
        printf("Inside the child process\n");
    }else{
        printf("Inside the parent\n");
    }
    pid = fork();

    if (pid < 0)
    {
        printf("error on creating child process\n");
        return -1;
    }
    if (pid == 0)
    {
        printf("Inside the child process\n");
    }else{
        printf("Inside the parent\n");
    }
    return 0;
}
