#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	int a, b, i, j, k, m, cars, x;
	printf("Size: ");
	scanf(" %d", &x);
	int slot[x][x], distance[x][x], compare[x][x];
	
	for(i=0; i<x; i++){
		for(j=0; j<x; j++){
			slot[i][j] = distance[i][j] = 0;
		}
	}
	
	printf("Cars: ");
	scanf(" %d", &cars);
	for(i=0; i<cars; i++){
		printf("Slots: ");
		scanf(" %d %d", &a, &b);
		slot[a-1][b-1] = 1;
	}
	
	for(i=0; i<x; i++){
		for(j=0; j<x; j++){
			if(slot[i][j] == 0){
				for(k=0; k<x; k++){
					for(m=0; m<x; m++){
						if(slot[k][m] == 1){
							distance[i][j]+=abs(k - i) +abs(m - j);
						}
					}
				}
			}
		}
	}
	
	for(k=0; k<x; k++){
		for(m=0; m<x; m++){
			compare[k][m] = distance[k][m];  
		}
	}

	
	a=0;
	b=0;
	
	for(k=0; k<x; k++){
		for(m=0; m<x; m++){
			if(distance[k][m] > compare[a][b]){
				a = k;
				b = m;
			}
		}
	}
	
	printf("Best Slot Found In: %d %d", a+1, b+1);
	
return EXIT_SUCCESS;
}
