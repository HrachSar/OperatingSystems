#include <stdio.h>
#include <stdlib.h>

int main(){

	int n;
	printf("Enter the number of students: ");
	scanf("%d", &n);
	int *grades = (int *)malloc(n * sizeof(int));
	if(!grades){
		printf("Error on allocating an array of grades");
		return 1;
	}
	printf("Enter the grades: ");	
	for(int i = 0; i < n; i++)
		scanf("%d", (grades + i));
	int max = grades[0];
	int min = grades[0];
	for(int i = 1; i < n; i++){
		if (max < grades[i])
			max = grades[i];
		if (min > grades[i])
			min = grades[i];
	}

	printf("Highest grade: %d\n", max);
	printf("Lowest grade: %d\n", min);

	free(grades);
	grades = NULL;
	return 0;
}
