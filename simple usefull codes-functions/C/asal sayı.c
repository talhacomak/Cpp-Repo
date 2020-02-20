#include <stdio.h>
int main()
{
	int x,y,z,t, u=0;
	scanf("%d", &x);
	for(y=2; y<=x; y++)
	{
		for(z=2; z<=y;)
		{
			t = (y % z);
			if(y==z) printf("%d ", y);
			if(t==0) break;
			z++;
		}
	}
return 0;
}
