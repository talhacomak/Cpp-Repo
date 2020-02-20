#include <iostream>
using namespace std;

class vector{
	public:
	int size;
	int* array;
	vector(int* ar, int size){
		array = ar;
		this->size = size;
	}
	vector operator+(const vector& v2){
		int* ar = new int[size];
		for(int i=0; i<size; i++){
			ar[i] = v2.array[i] + this->array[i];
		}
		vector v3(ar, size);
		return v3;
	}
	int operator*(vector& v2){
		int res=0;
		for(int i=0; i<size; i++){
			res += v2.array[i] * this->array[i];
		}
		return res;
	}
	vector operator*(int x){
		int* ar = new int[size];
		for(int i=0; i<size; i++){
			ar[i] = x*this->array[i];
		}
		return vector(ar, size);
	}
};

int main(){
	int ar[4] = {1,2,3,4};
	vector v1(ar, 4);
	vector v2(ar, 4);
	cout << v1*v2;
	return 0;
}
