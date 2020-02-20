#include <vector>
#include <iostream>
using namespace std;

int main(){
	vector <int> v(2,2);
	
	for(int i =0; i<v.size()-1; i++){ // v.size() unsigned int döndürdüðü için 0 - 1 = max unsigned int oluyor ve döngü bitmek bilmiyor :O
		v.erase(v.begin());
		v.erase(v.begin());
		i = -1;
		cout<<"sdfa";
	}
	
    return 0;
}

