#include <stdio.h>

/* THIS PROGRAM CALCULATE EXTRA LONG FACTORIALS */

void extraLongFactorials(int n) {
    int fac1[10000], fac2[10000];
    int i;
    for(i=0; i<10000; i++){
    	fac1[i] = fac2[i] = '\0';
	}
    int m = n-1;
    i=0;
    while(n>10){
        fac1[i] = (n%10);
        i++;
        n/=10;
    }
    fac1[i] = n;

    int elde = 0;
    int k; 
	int sel;
	
	
    while(m>1){
    	i=0;
        while(fac1[i]!='\0'){
            k = m*fac1[i] + elde;
            fac2[i] = (k%10);
            elde = k/10;
            i++;
        }
        while(elde>10){
            fac2[i] = (elde%10);
            elde/=10;
        }
        if(elde!=0) fac2[i] = elde;
        
        for(i=10000; i>=0; i--){
            if(fac2[i] != '\0') printf("%d ", fac2[i]);
        }
        
        i=0;
        m--;
        sel=2;
        elde = 0;
        for(i=0; i<10000; i++){
    		fac1[i] = '\0';
		}
        
		if(m==1){
            break;
        }
        
        
        while(fac2[i]!='\0'){
            k = m*fac2[i] + elde;
            fac1[i] = (k%10);
            elde = k/10;
            i++;
        }
        while(elde>10){
            fac1[i] = (elde%10);
            elde/=10;
        }
        if(elde!=0) fac1[i] = elde;
        
        m--;
        sel=1;
        elde = 0;
        for(i=0; i<10000; i++){
    		fac2[i] = '\0';
		}
    }
	
    if(sel == 1){
        for(i=10000; i>=0; i--){
            if(fac1[i] != '\0') printf("%d", fac1[i]);
        }
    }
    else{
        for(i=10000; i>=0; i--){
            if(fac2[i] != '\0') printf("%d", fac2[i]);
        }
    }
    
}

int main()
{
    int n;
    scanf("%d", &n);
   
    extraLongFactorials(n);

    return 0;
}

