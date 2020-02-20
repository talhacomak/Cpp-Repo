/*  Talha Çomak
	150160726
*/

#include <iostream>
#include <sstream>

using namespace std;

class Polynom{
	int size; //degree of polynom
	int* array; // coefficients of polynom
public:
	Polynom(int* ar, int size){ // constructor of polynom class
		array = ar;
		this->size = size;
	}
	Polynom operator+(const Polynom& p2){ // + operator overloading that adds two polynom
		int upperbound = size > p2.size ? size : p2.size; // new degree of the addiciton polynom is bigger one
		int* ar = new int[upperbound+1]; // polynom array size is one more of degree of polynom
		int i;
		if(p2.size < size){						// firstly bigger bound is found
			for(i=size; i>=p2.size+1; i--){		// than elements of bigger polynom are assigned to new one 
				ar[i] = array[i];
			}
		}
		else {
			for(i=p2.size; i>=size+1; i--){
				ar[i] = p2.array[i];
			}
		}
		for(; i>=0; i--){						// i is equal to lower degree
			ar[i] = array[i] + p2.array[i];		// addition of elements of two polynoms
		}
		return Polynom(ar, upperbound);
	}
	Polynom operator*(const Polynom& p2){	// * operator overloading that multiplicate two polynom
		int upperbound = size+p2.size;		// new degree of multiplication polynom is sum of degrees of polynoms
		int* ar = new int[upperbound+1];	// polynom array size is one more of degree of polynom
		for(int i=0; i<upperbound+1; i++){	// initilizing of elements of array
			ar[i] = 0;
		}
		for(int i=0; i<=size; i++){ 
			for(int j=0; j<=p2.size; j++){
				ar[i+j] +=  array[i]*p2.array[j];  // multiplication elements of two polynom array one by one then assigning to new array
			}
		}
		return Polynom(ar, upperbound);
	}
	string print(){  // this function return a string that keep the printing format of polynom object
		stringstream ss;
										// size equal to degree of polynom and equal to last indices of polynom array
		for(int i=size; i>=0; i--){  	// fistly we print the coefficient of biggest degree of polynom
			if(i > 1){				// if the degree is bigger than one	
				if(array[i] > 1){	// if the coefficient bigger than one
					ss<< array[i] << "x^"<<i;		// this is in proper format
					if(array[i-1] > 0) ss<< " + ";	// if there is a next value put the " + "
				}
				else if(array[i] == 1){ 	// if the coefficient equal to one
					ss<<"x^"<<i;			// do not put the coefficient
					if(array[i-1] > 0) ss<< " + ";	// if there is a next value put the " + "
				}
			}
			else if(i == 1){ 		// if the degree is equal to one	
				if(array[i] > 1){ 	// if the coefficient bigger than one
					ss<< array[i] << "x";		// this is in proper format
					if(array[i-1] > 0) ss<< " + ";	// if there is a next value put the " + "
				}
				else if(array[i] == 1){	// if the coefficient equal to one
					ss<<"x";			// do not put the coefficient
					if(array[i-1] > 0) ss<< " + ";	// if there is a next value put the " + "
				}
			}
			else{	// if the degree is equal to zero	
				if(array[i] > 0){	// if coefficient bigger than zero
					ss<< array[i];	// put only the coefficient
				}
			}
		}
		
		string s = ss.str(); // s is formatted output
		return s;
	}
	~Polynom(){
		delete [] array;
	}
};
