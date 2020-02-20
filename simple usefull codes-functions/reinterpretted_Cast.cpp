#include <iostream>

using namespace std;

struct S{ // A structure
int i1, i2; // made of two integers
};
int main(){
	S x; // x is of type S
	x.i1=1; // fields of x are filled
	x.i2=2;
	unsigned char *xp; // A pointer to unsigned chars
	xp = reinterpret_cast<unsigned char *> (&x); // reinterpretation
	for (int j=0; j<8; j++) // bytes of x on the screen
		std::cout << static_cast<int>(*xp++)<<endl;
	return 0;
}
