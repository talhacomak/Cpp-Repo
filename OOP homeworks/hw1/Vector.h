/*  Talha Çomak
	150160726
*/

#include <iostream>
#include <sstream>

using namespace std;

class Vector{
	int size;	// size of vector
	int* array;		// pointer of array which store elements of vector 
	public:	
	Vector(int* ar, int size){	// constructor of Vector 
		array = ar;
		this->size = size;
	}
	Vector operator+(const Vector& v2){		// + operator overloading that adds two vector 
		int* ar = new int[size];					// this function adds to vector's elements
		for(int i=0; i<size; i++){					// and return a new vector
			ar[i] = v2.array[i] + this->array[i];
		}
		Vector v3(ar, size);
		return v3;
	}
	int operator*(Vector& v2){		// * operator overloading that multiplicate two vector. (dot product)
		int res=0;	
		for(int i=0; i<size; i++){
			res += v2.array[i] * this->array[i];
		}
		return res;
	}
	Vector operator*(int x){	// * operator overloading that multiplicate a vector by an integer
		int* ar = new int[size];
		for(int i=0; i<size; i++){
			ar[i] = x*this->array[i];
		}
		return Vector(ar, size);
	}
	int getter_size(){		// that function return size of a vector object
		return size;
	}
	string print(){		 // this function return a string that keep the printing format of vector object
		stringstream ss;
		ss<<"(";
		for(int i=0; i<size; i++){
			ss<< array[i];
			if(i != size-1) ss<<", ";
			else ss<<")";
		}
		string s = ss.str();
		return s;
	}
	~Vector(){
		delete [] array;
	}
};
