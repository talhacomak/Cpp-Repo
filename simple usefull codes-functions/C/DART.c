#include <stdio.h>
#include <stdlib.h>

int fpoint(int segment, char ring)
{
	if(ring=='S') return segment;
	else if(ring=='D') return segment * 2;
	else if(ring=='T') return segment * 3;
	else if(ring=='O') return 25;
	else if(ring=='I') return 50;
	else return 0;
}

int remain(int point, int remain_point, char ring, int segment, int target)
{
	if(remain_point - point == 1) return remain_point;
	if(remain_point < point) return remain_point;
	if(remain_point == target && ring != 'D') return remain_point;
	else if(point == remain_point && ring != 'D') return remain_point;
	else remain_point -= point;
	return remain_point;
}

int main()
{
	int target, segment, point, remain_point;
	char ring;
	printf("Target: \n");
	scanf(" %d", &target);
	remain_point = target;
	while(remain_point > 0)
	{
		printf("Throw: ");
		scanf(" %d %c", &segment, &ring);
		point = fpoint(segment, ring);
		remain_point = 	remain(point, remain_point, ring, segment, target);
		printf("Points: %d\n", remain_point);
	}
return EXIT_SUCCESS;
}
