#include <iostream>
#include <locale.h>
#include <cstdio>
	
using namespace std;

int main(){
	setlocale(LC_ALL, "Turkish");  // setlocale(LC_ALL, "tr_TR.UTF-8");
	char* x = new char[100];
	FILE* pt = fopen("turkish-input.txt", "r");
	fgets(x, 98, pt);
	cout << x << endl;
}
