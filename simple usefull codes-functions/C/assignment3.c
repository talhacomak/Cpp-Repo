#include <stdio.h>

/* this program will calculate the furthest parkinig slot from cars in the parking area */ 

int main()
{
	int i, j, k, m, cars, size; // i j k m for loops, cars = number of cars, size = size of parking area
	printf("Size: ");
	scanf(" %d", &size);
	
	int slot[50][50], distance[50][50], compare[50][50];
	
	for(i=0; i<size; i++){ // initializing for slot and distance arrays 
		for(j=0; j<size; j++){
			slot[i][j] = 0;
			distance[i][j] = 0;
		}
	} 
	
	printf("Cars: ");  // number of cars
	scanf(" %d", &cars);
	
	if(cars == size*size){
		printf("Best Slot Found In: 0 0\n");
	}
	
	for(i=0; i<cars; i++){ // assigning 1 for filled slots in slot array
		printf("Slots: ");
		scanf(" %d %d", &k, &m);
		slot[k-1][m-1] = 1;  // arrays starts zero so substract 1 for each slot
	} 
	
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			if (slot[i][j] == 0) 
				distance[i][j] = 2*49; // maximum value of distance of any empty slot. i must do that process becouse there must be a bigger value before comparing distances 
		}
	}
	
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			if(slot[i][j] == 0){  // for each empty slot in slot array;
				for(k=0; k<size; k++){   
					for(m=0; m<size; m++){ 
						if(slot[k][m] == 1){  // if there exist a car in slot array we must calculare the manhattan distance
							if((k - i > 0 ? k - i : i - k) + (m - j > 0 ? m - j : j - m) < distance[i][j])  // and if new distance is smaller than old one, () ? () : () instead of abs function
								distance[i][j] = (k - i > 0 ? k - i : i - k) + (m - j > 0 ? m - j : j - m); // change the distance from new distance
						}
					}
				}
			}
		}
	}
	
	for(k=0; k<size; k++){   // copying the distance array to another array in order to find furthest distance 
		for(m=0; m<size; m++){
			compare[k][m] = distance[k][m];  
		}
	} 
		
	i = j = 0;  // to start to compare we can start the any element of compared array
	
	for(k=0; k<size; k++){
		for(m=0; m<size; m++){
			if(distance[k][m] > compare[i][j]){  // if an element of distance array bigger than the compared element
				i = k;                           // change the compared element with current distance element
				j = m;
			}
		}
	}
	
	printf("Best Slot Found In: %d %d", i+1, j+1);  // arrays starts 0 but slots does not
	
return 0;
}
