#include <stdio.h>

int main(){
    int a = 13;
    int *b; //declared a pointer
    b = &a; //pointer points to a

    printf("The address of a %p\n", &a); //print the address of 'a' using the address of a 
    printf("The address of a %p\n", b); //print the address of 'a' using b
    //Change the value of a 
    *b =  23;
    printf("The new val of a = %d", a);
    return 0;
}