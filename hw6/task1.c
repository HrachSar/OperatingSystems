#include <stdio.h>

typedef struct {
	int i;
	char c;
	double d;
	short s;
} my_struct;

int main(){

	my_struct s = {0, '\0', 0, 0};
	printf("sizeof int = %zu\n", sizeof(s.i));
	printf("sizeof char = %zu\n", sizeof(s.c));
	printf("sizeof double = %zu\n", sizeof(s.d));
	printf("sizeof short = %zu\n", sizeof(s.s));
	
	puts("Printing the addresses of each variable...");
	
	printf("The address of first variable is %p\n", (char *)&s.i); 
	printf("The address of second variable is %p\n", (char *)&s.c);
	printf("The address of the third variable is %p\n", (char *)&s.d);
	printf("The address of the fourth variable is %p\n", (char *)&s.s);

	printf("The offset of each variable\n");
	printf("The offset from the struct of first variable is %zu\n", (size_t)&s.i - (size_t)&s);
	printf("The offset from the struct of second variable is %zu\n", (size_t)&s.c - (size_t)&s.i);
        printf("The offset from the struct of the third variable is %zu\n", (size_t)&s.d- (size_t)&s.c);
        printf("The offset from the struct of the fourth variable is %zu\n", (size_t)&s.s - (size_t)&s.d);
	printf("The size of the struct is %zu\n", sizeof(s));

	return 0;
}
