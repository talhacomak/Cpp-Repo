#include <stdio.h>

int main()
{
	int i=0, k=0, flag=0;
	double arr[11];
	char ch; 
	
	for(i=1; i<=10; i++)
	{
		printf("Enter a number: "); 
		scanf("%lf", &arr[i]);
		if(arr[i]==0) 
			break;
	}
	printf("Time to shake!\n");
	for(k=1; k<=10; k++)
	{
		printf("%5d\t", k);	
	}
	printf("\n");
	for(k=1; k<i; k++)
	{
		printf("%5.2lf\t", arr[k]);
	}
	while(1)
	{
		printf("\nEnter the direction: ");
		scanf(" %c", &ch);
		if(ch=='X'){
			break;
		}
		else if(ch=='R')
		{
			arr[i-2]+=arr[i-1];
			for(k=1; k<=10; k++)
			{
				printf("%5d\t", k);	
			}
			printf("\n");
			for(k=1; k<=(12-i); k++)
			{
				printf("\t");
			}
			for(k=1; k<=(i-2); k++)
			{
				printf("%5.2lf", arr[k]);
				if(k!=(i-2))
					printf("\t");
			}
			i--;
			flag++;
		}
		else if(ch=='L')
		{
			arr[2]+=arr[1];
			for(k=1; k<(i+flag-1); k++)
			{
				arr[k]=arr[k+1];
			}
			for(k=1; k<=10; k++)
			{
				printf("%5d\t", k);	
			}
			printf("\n");					
			for(k=1; k<(i-1); k++)
			{
				printf("%5.2lf", arr[k]);
				if(k!=(i-1))
					printf("\t");
			}	
			i--;																							
		}
	}
	return 0;
}
