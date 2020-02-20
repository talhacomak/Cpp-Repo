#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *p1, int *p2){
	int temp;
	temp=*p1;
	*p1=*p2;
	*p2=temp;
}
void dizi_bul(int dizi[], int size){
	int i, a, j, say;
	dizi[0] = rand()%size;
	for(i=1; i<size; i++){
		do {
			say=0;
			a=rand()%size;
			for(j=0; j<i; j++){
				if(dizi[j]==a){
					say++;	
				}
			}
		} while(say != 0);
		dizi[i] = a;
	}
}

int main(){
	srand(time(NULL));
	int size, i;
	scanf("%d", &size);
	int dizi[size];
	dizi_bul(dizi, size);
	for(i=0; i<size; i++){
		printf("%d ", dizi[i]);
	}
	printf("\n");
	for(i=0; i<size/2; i++){
		swap(&dizi[i], &dizi[size-1-i]);
	}
	for(i=0; i<size; i++){
		printf("%d ", dizi[i]);
	}
return EXIT_SUCCESS;
}

