#include <stdio.h>

int main(){
    int a = 30;
    int* b;
    b = &a;
    int** c;
    c = &b;

    printf("%d\n", a);
    printf("%d\n", *b);
    printf("%d\n", **c);
    
    return 0;
}