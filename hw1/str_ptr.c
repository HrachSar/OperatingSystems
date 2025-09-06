#include <stdio.h>

int main(){
    char str[] = "Hello";
    int count = 0;
    char* first;
    
    first = str;
    while (*first)
    {
        printf("%c", *first);
        first++;
        count++;
    }
    printf("\n%d", count);
    return 0;
    
}