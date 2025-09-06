#include <stdio.h>

int main(){
    int arr[5] = {2, 3, 6, 1, 0};

    int i = 0;
    while(i < 5){
        if(i < 4)
            printf("%d, ", *(arr + i));
        else
            printf("%d ", *(arr + i));
        i++;
    } //traverse through the array

    printf("\n");
    i = 0;
    while(i < 2){
        int temp = *(arr + i);
        *(arr + i) = *(arr + 4 - i);
        *(arr + 4 - i) = temp;
        i++;
    } //swap each i-th element with (size - 1 - i)-th element

    i = 0;
    while(i < 5){
        if(i < 4)
            printf("%d, ", *(arr + i));
        else
            printf("%d ", *(arr + i));
        i++;
    } // traverse and print

    printf("\n");
    for(int j = 0; j < 5; j++){
        if(j < 4)
            printf("%d, ", arr[j]);
        else
            printf("%d ", arr[j]);
    }//print using array name
    
    printf("\n");
    return 0;
}
