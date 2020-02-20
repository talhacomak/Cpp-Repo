#include <stdio.h>

int main(){
	int size, control;
	printf("dizinin buyuklugu: ");
	scanf(" %d", &size);
	int a[size], b[1], i, j;
	for (i=0; i<size; i++){
		scanf(" %d", &a[i]);
	}
	
	printf("siralama [artan icin 1, azalan icin 0] : ");
	scanf(" %d", &control);
	
	if(control = 1){
		for(j=0; j<size-1; j++){
			for(i=0; i<size-1 ; i++){
				if(a[i] > a[i+1]){
					b[0] = a[i];
					a[i] = a[i + 1];
					a[i + 1] = b[0];
				}
			}
		}
	}
	
	if(control = 0){
		for(j=0; j<size-1; j++){
			for(i=0; i<size-1 ; i++){
				if(a[i] < a[i+1]){
					b[0] = a[i];
					a[i] = a[i + 1];
					a[i + 1] = b[0];
				}
			}
		}
	}

	for (i=0; i<size; i++){
		printf(" %d\n", a[i]);
	}
	return 0;
}