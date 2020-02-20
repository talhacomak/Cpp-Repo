#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int pi_bul(){
	double x, y;
	int count=0, i;
	for(i=0; i<50000000; i++){
	x = (double)rand()/RAND_MAX;
	y = (double)rand()/RAND_MAX;
        if ((x*x) + (y*y)<=1) count++;
	}
	return count;
}

int main(){
	long double a;
	srand(time(NULL));
	a = 4*((1.0*pi_bul())/50000000);
        printf("pi = %Lf", a);
return 0;
}
