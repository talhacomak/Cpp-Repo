#include <iostream>

using namespace std;

int fact(int n){
	int m;
	if(n==0){
		return 1;
	}
	return fact(n-1)*n;
}
int main(){
	cout<<fact(6);
}
