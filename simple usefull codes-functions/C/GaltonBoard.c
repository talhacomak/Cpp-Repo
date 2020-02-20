#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	int i, j, r, run;
	int* counts[10];
	srand(time(NULL));	

	for ( i = 0; i < 10; i++) {
		counts[i] = (int*) malloc(sizeof(int)*(i + 1));
	}
	
	for(i =0; i<10; i++){
		for ( j = 0; j <= 1; j++) {
			counts[i][j] = 0;
		}
	}
	
	for ( run = 0; run < 1000; run++) {
		counts[0][0]++;
		j = 0;
		for ( i = 1; i < 10; i++) {
			r = rand() % 2;
			if (r == 1) {
				j++;
			}
			counts[i][j]++;
		}
	}

	for ( i = 0; i < 10; i++) {
		for (j = 0; j <= i; j++) {
			printf("%5d  ", counts[i][j]);
		}
		printf("\n");
	}
	
		for ( i = 0; i < 11; i++) {
		free(counts[i]);
	}
	
	
	for ( i = 0; i < 11; i++) {
		counts[i] = NULL;
	}
return 0;
}
