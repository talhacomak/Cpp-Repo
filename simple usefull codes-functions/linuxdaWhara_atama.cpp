#include <iostream>
#include <cwchar>
#include <clocale>
#include <sstream>
#include <fstream>

using namespace std;

int main(){
	
	setlocale(LC_ALL, "tr_TR.UTF-8");
	locale utf8("tr_TR.UTF-8");
	wifstream pt("input.txt");
	pt.imbue(utf8);
	wstringstream ss;
	ss << pt.rdbuf();
	wstring line;
	line = ss.str();
	wcout<<line <<endl<< (int)line[0]<<" "<< (int)line[1]<<" "<< (int)line[2]<<" "<< (int)line[3]<<" "<< (int)line[4]<<" "<< (int)line[5]<<endl;
	wcout<<endl<< (int)line[7]<<" "<< (int)line[8]<<" "<< (int)line[9]<<" "<< (int)line[10]<<" "<< (int)line[11]<<" "<< (int)line[12]<<endl;

}
