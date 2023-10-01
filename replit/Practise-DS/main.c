#include <stdio.h>
#include <stdlib.h>
int main(void) {
	int *A = NULL;
	A = (int *)malloc(sizeof(int));
	A[0] = 5;
	A++;
	int b[100] = {};
	b[0] = 6;
	b[1] = 7;
	// A=(int*)malloc(sizeof(int));
	// A[1]=8;
	// A=(int*)malloc(sizeof(int));
	*A = 8;
	A[2] = 90;
	A[0] = A[0] + 1;
	printf("\n%ld\n", sizeof(A) / sizeof(A[0]));
	for (int i = 0 /*sizeof(A)/sizeof(int)*/; i < 3; i++) {
		printf("%d ", A[i]);
	}
	printf("\n%ld\n", sizeof(b) / sizeof(int));

	// printf("\n%c ",33);
}