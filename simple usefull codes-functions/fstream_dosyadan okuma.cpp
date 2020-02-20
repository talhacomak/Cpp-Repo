#include <iostream>
#include <locale.h>
#include <fstream>
	
using namespace std;

int main(){
	setlocale(LC_ALL, "Turkish");
	string x;
	ifstream pt;
	pt.open("input.txt");
	while(pt){
		pt>>x;
		cout<<x<<endl;
	}
}
