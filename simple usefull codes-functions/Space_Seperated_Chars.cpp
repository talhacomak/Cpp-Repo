#include <cstdio>
#include <iostream>

using namespace std;

int main() {
    for(int i=0; i<1; i++){
        char string[100];
		scanf ("%[^\n]%*c", string);
		printf ("You entered: %s\n", string);
		char c;
		int k;
		scanf ("%d %[^\n]%c", &k ,&c);
		printf("%d %c", k, c);
    }
    return 0;
}
