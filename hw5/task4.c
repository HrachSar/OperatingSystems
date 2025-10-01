#include <stdio.h>
#include <stdlib.h>

int main(){
	
	char **mat;
	int row = 3;
	int col = 50;

	mat = (char **)malloc(row * sizeof(char *));
	if(!mat){
		printf("Error on allocating an array of strings");
		return 1;
	}	
	for(int i = 0; i < row; i++){
		mat[i] = (char *)malloc(col * sizeof(char));
		if(!mat[i]){
			printf("Error on allocating memory for a string");
			return 1;
		}
	}
	printf("Enter %d strings: ", row);
	for(int i = 0; i < row; i++){
		scanf("%s", mat[i]);
		printf("%s ", mat[i]); 
	}
	printf("\n");
	char **new_mat = (char **)realloc
				(mat, (row + 2) * sizeof(char *));
	if(!new_mat){
                printf("Error on reallocating an array of strings");
                return 1;
        }
	for(int i = row; i < row + 2; i++){
		new_mat[i] = (char *)malloc(col * sizeof(char));
		if(!new_mat[i]){
                        printf("Error on allocating memory for a string");
                        return 1;
                }
	}
	printf("Enter 2 more strings: ");
	for(int i = row; i < row + 2; i++){
		scanf("%s", new_mat[i]);
	}
	
	for(int i = 0; i < row + 2; i++){
		printf("%s ", new_mat[i]);
	}
	printf("\n");       	
	for(int i = 0; i < row + 2; i++){
		free(new_mat[i]);
		new_mat[i] = NULL;
	}
	free(new_mat);
	new_mat = NULL;

	return 0;
}	
