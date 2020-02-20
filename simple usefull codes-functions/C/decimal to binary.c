#include <stdio.h>
#include <math.h>
int main()
{
	int num, bin=0, n, x;
	scanf("%d", &num);

	while(num>0)
	{
		n=0;
		while(num>pow(2,n))
			{
				n++;
			}
		n--;
		bin += pow(10,n) +0.5;
		x = pow(2,n) + 0.5;
		num = (num % x);
		if(num==1)
		{
			bin+=1;
			break;
		}
	}
	printf("%d", bin);

	return 0;
}
