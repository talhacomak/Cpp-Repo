#include <cstdio>

int getRightMostIndex(float ar[]){
    for(int i=9; i>=0; i--){
        if(ar[i] != 0){
            return i;
        }
    }
    return 0;
}

int getLeftMostIndex(float ar[]){
    for(int i=0; i<10; i++){
        if(ar[i] != 0){
            return i;
        }
    }
    return 0;
}

void shake(float ar[], char d){
    int index;
    if(d == 'R'){
        index = getRightMostIndex(ar);

        ar[9] = ar[index];
        if(index-1 >= 0) ar[9] += ar[index-1];

        if(index-1 >= 0) ar[index-1] = 0;
        int j=8;
        for(int i=index-2; i>=0; i--, j--){
            ar[j] = ar[i];
        }
        for(int i=0; i<j; i++){
            ar[i] = 0;
        }
    }
    if(d == 'L'){
        index = getLeftMostIndex(ar);
    }
}

void print(float ar[]){
    for(int i=0; i<10; i++){
        printf("%7d", i+1);
    }
    putchar('\n');
    for(int i=0; i<10; i++){
        printf("%7.2f", ar[i]);
    }
    putchar('\n');
    putchar('\n');
};

int main(){
    float array[10] = {0};
    char dir;
    for (int i=0; i<10; i++){
        scanf("%f", &array[i]);
        if(array[i] == 0) break;
    }
    while(true){
        scanf("%c ", &dir);
        if(dir == 'X') break;
        shake(array, dir);
        print(array);
    }

    return 0;
}