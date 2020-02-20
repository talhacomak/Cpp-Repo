#include <cstdio>
#include <iostream>

using namespace std;

int main() {
    for(int i=0; i<1; i++){
        char string[100];
		printf("Enter whole sentece (yeah, bring spaces too, I can handle it):\n");
		scanf ("%[^\n]%*c", string);
		printf ("You entered: %s\n", string);
    }
    return 0;
}
