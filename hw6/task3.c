#include <stdio.h>

#pragma pack(4)
typedef struct{
	char a;
	int b;
	double c;
} my_struct;

int main(){

	my_struct s = {'\0', 0, 0};
	
	puts("Printing the addresses of each variable...");
	
	printf("The address of first variable is %p\n", (char *)&s.a); 
	printf("The address of second variable is %p\n", (char *)&s.b);
	printf("The address of the third variable is %p\n", (char *)&s.c);

	printf("The offset of each variable\n");
	printf("The offset of first variable is %zu\n", (size_t)&s.a - (size_t)&s);
	printf("The offset of second variable is %zu\n", (size_t)&s.b - (size_t)&s.a);
        printf("The offset of the third variable is %zu\n", (size_t)&s.c - (size_t)&s.b);
	printf("size of the struct %zu\n", sizeof(s));
	return 0;
}

