#include <vector>
#include <iostream>
using namespace std;

int main(){
	vector <int> v(2,2);
	
	for(int i =0; i<v.size()-1; i++){ // vector.size() unsigned deðer döndürür. unsigned 0 - 1 = unsingned max olduðu için seg fault
		v.erase(v.begin());
		v.erase(v.begin());
		i = -1;
		cout<<"sdfa";
	}
    return 0;
}
