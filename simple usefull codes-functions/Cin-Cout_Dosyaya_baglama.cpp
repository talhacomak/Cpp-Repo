#include <iostream>
#include <locale.h>
#include <cstdio>
	
using namespace std;

int main(){
	setlocale(LC_ALL, "Turkish");
	freopen("input.txt", "r",  stdin);
	string x;
	getline(cin, x);
	cout << x << endl;
}
