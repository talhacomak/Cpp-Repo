#include <stdio.h>
#include <stdlib.h>
#include <time.h>


double distance4t (double tim, double spee){

    double distance = 0;
    
    while(tim * spee > 0){
            distance += 200;
            tim = tim - 200/spee;
            spee = spee - spee*((rand() % 6+ 5)/100);
        }
            distance += spee*tim;
            return distance;
}

double time4d (double distance, double speed){
	double time=0;
    while(distance > 0){
            time += 200 / speed;
            distance -= 200;
            speed = speed - speed*(rand()%6 + 5)/100;
        }
            time += distance / speed;
            return time;
}

int main(){

    char type;
    srand(time(NULL));
    double time, distance, speed1, speed2, a, b;

    printf("hiz1, hiz2 : ");
    scanf(" %lf %lf", &speed1, &speed2);

    printf("secim: ");
	scanf(" %c", &type);

	switch (type){
        case 'X':
            return 0;
            break;
        case 'T':
        	printf("enter time (in sec): ");
            scanf(" %lf", &time);
            if (distance4t(time, speed1)> distance4t(time, speed2))
            {
            	a=distance4t(time, speed1);
            	b=distance4t(time, speed2);
            	printf("A beats B by %lf m", (a - b));
			}
            else
			{
				a=distance4t(time, speed1);
            	b=distance4t(time, speed2);
				printf("B beats A by %lf m", (b - a));
			}
			break;
        case 'D':
        	printf("enter distance (in m): ");
            scanf(" %lf", &distance);
             if (time4d(distance, speed1) < time4d(distance, speed2))
            {
            	a=time4d(distance, speed1);
            	b=time4d(distance, speed2);
            	printf("A beats B by %lf sec", (b - a));
			}
            else
			{
				a=time4d(distance, speed1);
            	b=time4d(distance, speed2);
				printf("B beats A by %lf sec", (a - b));
			}
            break;
    }
return 0;
}
