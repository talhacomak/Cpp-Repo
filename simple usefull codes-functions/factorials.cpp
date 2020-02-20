#include <iostream>
#include <limits.h>

using namespace std;

long long int factorial(int n){
	long long int result;
	if(n>2) result = n*factorial(n-1);
	else result = n;
	return result;
}



int main(){
	//cout<<LLONG_MAX<<" "<<ULLONG_MAX;
	int x;
	cin>>x;
	if(x<21) cout<<factorial(x)<<endl;s
}
