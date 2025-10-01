#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

void cleanup1(void);
void cleanup2(void);


int main()
{
    atexit(cleanup1);
    atexit(cleanup2);
    
    exit(0);
}

void cleanup1(void){
    printf("This is the first cleanup\n");
}
void cleanup2(void){
    printf("This is the second cleanup\n");
}
