#include <stdio.h>

int main(){
    char array[100], c;
    int i=0, j, numberOfZeros = 0;
    int combination = 1;
    int katsayi[10] = {1,1,3,3,3,3,3,4,3,4};
    while(1){
        scanf("%c", &c);
        if( c == '\n'){
            for( j=0; j<i-2; j++){
                if(array[j] == '0' && array[j+1] == '0' && array[j+2] == '0'){
                    printf("Terminated\n");
                    return 0;
                }
            }
            for(j=0; j<i; j++){
                combination *= katsayi[array[j] - '0'];
            }
            printf("The number of combinations: %d\n", combination);
            i = 0;
        }
		else if(c == '1'){
            printf("Number should not include 0 or 1\n");
            i = 0;
        }
		else if((c < '2' || c > '9') && c != '0'){
            continue;
        }
		else{
            array[i] = c;
            i++;
        }
    }
}
