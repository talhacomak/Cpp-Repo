#include <iostream>

using namespace std;
int y = 0;
int x = 1;
void f(){
	int x = 5;
	::x++;
	x++;
	y++;
	cout<<x<<::x<<y<<endl;
}
	namespace one{
		int k = 31;
		void fu(int x){
			x++;
			cout<<x
			;
		}
	}
	namespace two{
		float k;
	}
int main(){
	f;
	cout<<one::k;
	one::fu(one::k);
}
