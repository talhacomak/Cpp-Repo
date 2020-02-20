#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int** func(int** dizi1, int satir1, int kolon1, int** dizi2, int kolon2){
	int i, j, k, m;
	int** carpim = (int**)malloc(satir1*sizeof(int));
	for(i=0; i<satir1; i++){
		carpim[i] = (int*)malloc(kolon2*sizeof(int));
		for(j=0; j<kolon2; j++){
			carpim[i][j] = 0;
		}
	}
	for(k=0; k<satir1; k++){
		for(m=0; m<kolon2; m++){
			for(j=0; j<kolon1; j++){
				carpim[k][m] += dizi1[k][j] * dizi2[j][m];
			}
		}
	}
	return carpim;
}

int main() 
{
	setlocale(LC_ALL, "Turkish");
	int** carpim;
    int** matris1;
    int** matris2;
    int satir1, satir2, kolon1, kolon2;
    int s, k;
    int i;
	printf("***MATRÝS ÇARPIMI***\n\n");	
	//1.
    printf("1. Matrisin satýr sayýsý: ");
    scanf("%d", &satir1);

    printf("1. Matrisin sütun sayýsý: ");
    scanf("%d", &kolon1);

    matris1 = (int **) calloc(satir1, sizeof(int));

    for(i = 0; i < satir1; i++)
	matris1[i] = (int *) calloc(kolon1, sizeof(int));

    for(s = 0; s < satir1; s++)
	for(k = 0; k < kolon1; k++) {
	    printf("Matrisin elemanýný girin: matris[%d][%d] = ", s, k);
	    scanf("%d", &(matris1[s][k]));
        }
	
	//2.
	satir2 = kolon1;
	printf("2. Matrisin satýr sayýsý: %d (1.'nin sütun sayýsýna eþit olmalý)\n", satir2);

    printf("2. Matrisin sütun sayýsý: ");
    scanf("%d", &kolon2);

    matris2 = (int **) calloc(satir2, sizeof(int));

    for(i = 0; i < satir2; i++)
	matris2[i] = (int *) calloc(kolon2, sizeof(int));

    for(s = 0; s < satir2; s++)
	for(k = 0; k < kolon2; k++) {
	    printf("Matrisin elemanýný girin: matris[%d][%d] = ", s, k);
	    scanf("%d", &(matris2[s][k]));
	}

	int** carpimm = func(matris1, satir1, kolon1, matris2, kolon2);
	
	int j;
	for(i=0; i<satir1; i++){
		for(j=0; j<kolon2; j++){
			printf("%3d ", carpimm[i][j]);
		}
		printf("\n");
	}

    return(0);
}
