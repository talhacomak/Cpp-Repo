#include <stdio.h>

int main()
{
	int a, b, c, d, input;
	scanf("%d", &input);
	a=c=0;
	b=d=1;
	while(a<=input)
	{
		if(d%2==1)
		{
			printf("%d ", a);
			a=a+b;
			b=a;
		}
		else
		{
			printf("%d ", a);
			a=a+c;
			c=a;
		}
	d++;
	}
}
