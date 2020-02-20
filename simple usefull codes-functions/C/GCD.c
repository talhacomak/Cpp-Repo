#include <stdio.h>
#include <stdlib.h>
int main()
{
	int num1, num2, little, i, GCD;
	printf("Enter two numbers:");
	scanf("%d %d", &num1, &num2);
	little = num1>num2 ? num2 : num1;
	for(i=1; i<=little; i++)
	{
		if(num1%i==0 && num2%i==0) GCD=i;		
	}
	printf("%d", GCD);
	return EXIT_SUCCESS;
}
